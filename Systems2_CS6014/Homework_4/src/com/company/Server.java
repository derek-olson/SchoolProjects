package com.company;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import java.io.*;
import java.math.BigInteger;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;

public class Server {
    static BigInteger KS;
    static BigInteger KSDH;
    static BigInteger DH;
    static java.security.PrivateKey PrivateKey;
    static Signature signature;
    static Certificate certificate;
    static String plainText = "A simple plain text message to encrypt and send.";
    static String caCert = "CAcertificate.pem";


    public static void main(String[] args) throws IOException, InvalidKeySpecException, NoSuchAlgorithmException, CertificateException, ClassNotFoundException, SignatureException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException, InvalidAlgorithmParameterException, NoSuchPaddingException, NoSuchProviderException {

        byte[] fileBytes = Files.readAllBytes(Paths.get("Huck_Finn.txt"));

        ByteArrayOutputStream messageHistoryBytes = new ByteArrayOutputStream();
        ObjectOutputStream messageHistory = new ObjectOutputStream(messageHistoryBytes);

        KS = DiffieHellman.computeKS();
        KSDH = DiffieHellman.computeKSDH(KS);

        signature = TLSHandshake.getSignature();

        certificate = TLSHandshake.getCertificate("CASignedServerCertificate.pem");
        PrivateKey = TLSHandshake.getPrivateKey("serverPrivateKey.der");

        ServerSocket serverSocket = new ServerSocket( 7777);
        Socket socket = serverSocket.accept();
        OutputStream outputStream = socket.getOutputStream();
        ObjectOutputStream objectOutputStream = new ObjectOutputStream(outputStream);
        objectOutputStream.flush();
        InputStream inputStream = socket.getInputStream();
        ObjectInputStream objectInputStream = new ObjectInputStream(inputStream);

        byte[] clientNonce = (byte[])objectInputStream.readObject();
        messageHistory.writeObject(clientNonce);

        objectOutputStream.writeObject(certificate);
        objectOutputStream.flush();
        objectOutputStream.writeObject(KSDH);
        objectOutputStream.flush();
        objectOutputStream.writeObject(TLSHandshake.sign(KSDH, signature, PrivateKey));
        objectOutputStream.flush();

        Certificate clientCertificate = (Certificate) objectInputStream.readObject();
        messageHistory.writeObject(clientCertificate);
        BigInteger clientKSDH = (BigInteger) objectInputStream.readObject();
        messageHistory.writeObject(clientKSDH);
        byte[] clientSignedKSDH = (byte[]) objectInputStream.readObject();
        messageHistory.writeObject(clientSignedKSDH);

        Certificate cert = TLSHandshake.getCertificate(caCert);
        clientCertificate.verify(cert.getPublicKey());
        cert.verify(cert.getPublicKey());

        boolean verified = TLSHandshake.verify(clientCertificate.getPublicKey(), clientKSDH, clientSignedKSDH, signature);
        System.out.println("Server verified: "+verified);

        if(!verified){
            socket.close();
            return;
        }

        DH = DiffieHellman.computeDH(clientKSDH, KS);
        KeyGeneration.makeSecretKeys(clientNonce, DH);

        objectOutputStream.writeObject(KeyGeneration.hmac(KeyGeneration.getServerMAC(), messageHistoryBytes.toByteArray()));
        objectOutputStream.flush();
        messageHistory.writeObject(KeyGeneration.hmac(KeyGeneration.getServerMAC(), messageHistoryBytes.toByteArray()));

        byte[] clientMACMessage = (byte[]) objectInputStream.readObject();

        boolean macVerify = TLSHandshake.verifyMac(clientMACMessage, KeyGeneration.getClientMAC(), messageHistoryBytes);
        System.out.println("Server MAC verified: "+macVerify);

        if(!macVerify){
            socket.close();
            return;
        }

        ByteArrayOutputStream makdBytes = new ByteArrayOutputStream();

        TLSEncryption.write("Huck_Finn.txt", makdBytes, objectOutputStream, KeyGeneration.getServerMAC(), KeyGeneration.getServerEncrypt(), KeyGeneration.getServerIV());

        TLSEncryption.read(objectInputStream, KeyGeneration.getClientMAC(), socket, KeyGeneration.getClientEncrypt(), KeyGeneration.getClientIV(), "");
    }
}
