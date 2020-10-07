package com.company;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;
import java.math.BigInteger;
import java.net.Socket;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;
import java.util.Arrays;

public class Client {
    static BigInteger KS;
    static BigInteger KSDH;
    static BigInteger DH;
    static Certificate certificate;
    static java.security.PrivateKey PrivateKey;
    static Signature signature;
    static String plainText = "Message was received";
    static String caCert = "CAcertificate.pem";

    static byte[] nonce(){
        SecureRandom random = new SecureRandom();
        byte[] clientNonce = new byte[32];
        random.nextBytes(clientNonce);
        return clientNonce;
    }

    public static void main(String[] args) throws CertificateException, IOException, InvalidKeySpecException, NoSuchAlgorithmException, ClassNotFoundException, SignatureException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException, InvalidAlgorithmParameterException, NoSuchPaddingException, NoSuchProviderException {
        ByteArrayOutputStream messageHistoryBytes = new ByteArrayOutputStream();
        ObjectOutputStream messageHistory = new ObjectOutputStream(messageHistoryBytes);

        KS = DiffieHellman.computeKS();
        KSDH = DiffieHellman.computeKSDH(KS);

        signature = TLSHandshake.getSignature();

        certificate = TLSHandshake.getCertificate("CASignedClientCertificate.pem");
        PrivateKey = TLSHandshake.getPrivateKey("clientPrivateKey.der");

        Socket socket = new Socket("localhost", 7777);
        OutputStream outputStream = socket.getOutputStream();
        ObjectOutputStream objectOutputStream = new ObjectOutputStream(outputStream);
        objectOutputStream.flush();
        InputStream inputStream = socket.getInputStream();
        ObjectInputStream objectInputStream = new ObjectInputStream(inputStream);

        byte[] nonce = nonce();
        objectOutputStream.writeObject(nonce);
        objectOutputStream.flush();
        messageHistory.writeObject(nonce);

        Certificate serverCertificate = (Certificate) objectInputStream.readObject();
        BigInteger serverKSDH = (BigInteger) objectInputStream.readObject();
        byte[] serverSignedKSDH = (byte[]) objectInputStream.readObject();

        Certificate cert = TLSHandshake.getCertificate(caCert);
        serverCertificate.verify(cert.getPublicKey());
        cert.verify(cert.getPublicKey());

        boolean verified = TLSHandshake.verify(serverCertificate.getPublicKey(), serverKSDH, serverSignedKSDH, signature);
        System.out.println("Client verified: "+verified);

        if(!verified){
            socket.close();
            return;
        }

        objectOutputStream.writeObject(certificate);
        objectOutputStream.flush();
        messageHistory.writeObject(certificate);
        objectOutputStream.writeObject(KSDH);
        objectOutputStream.flush();
        messageHistory.writeObject(KSDH);
        objectOutputStream.writeObject(TLSHandshake.sign(KSDH, signature, PrivateKey));
        objectOutputStream.flush();
        messageHistory.writeObject(TLSHandshake.sign(KSDH, signature, PrivateKey));

        byte[] serverMACMessage = (byte[]) objectInputStream.readObject();

        DH = DiffieHellman.computeDH(serverKSDH, KS);
        KeyGeneration.makeSecretKeys(nonce, DH);

        boolean macVerify = TLSHandshake.verifyMac(serverMACMessage, KeyGeneration.getServerMAC(), messageHistoryBytes);
        System.out.println("Client MAC verified: "+macVerify);

        if(!macVerify){
            socket.close();
            return;
        }

        messageHistory.writeObject(serverMACMessage);

        objectOutputStream.writeObject(KeyGeneration.hmac(KeyGeneration.getClientMAC(), messageHistoryBytes.toByteArray()));
        objectOutputStream.flush();


        TLSEncryption.read(objectInputStream, KeyGeneration.getServerMAC(), socket, KeyGeneration.getServerEncrypt(), KeyGeneration.getServerIV(), "huck-finn_new.txt");

        ByteArrayOutputStream makdBytes = new ByteArrayOutputStream();
        TLSEncryption.write("", makdBytes, objectOutputStream, KeyGeneration.getClientMAC(), KeyGeneration.getClientEncrypt(), KeyGeneration.getClientIV());

    }
}
