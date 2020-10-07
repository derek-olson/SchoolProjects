package com.company;

import java.io.*;
import java.math.BigInteger;
import java.security.*;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;

public class Main {

    public static void main(String[] args) throws IOException, CertificateException, NoSuchAlgorithmException, InvalidKeySpecException, InvalidKeyException, SignatureException {
        SecureRandom random = new SecureRandom();
        byte[] clientNonce = new byte[32];
        random.nextBytes(clientNonce);

        Server server = new Server();
        PublicKey serverPublicKey = server.PublicKey;
        BigInteger serverKSDH = server.KSDH;
        byte[] serverSigned = server.getServerToSign();

        Client client = new Client();
        boolean clientVerified = client.verifyServer(serverPublicKey, serverKSDH, serverSigned);

        PublicKey clientPublicKey = client.PublicKey;
        BigInteger clientKSDH = client.KSDH;
        byte[] clientSigned = client.getClientToSign();

        boolean serverVerified = server.verifyClient(clientPublicKey, clientKSDH, clientSigned);

        client.computeDH(serverKSDH);
        server.computeDH(clientKSDH);

        GenKeys serverGenKeys = new GenKeys(clientNonce, server.DH);
        GenKeys clientGenKeys = new GenKeys(clientNonce, client.DH);

//        InputStream clientCertificateInputStream = new FileInputStream("CASignedClientCertificate.pem");
//        Certificate clientCertificate = certificateFactory.generateCertificate(clientCertificateInputStream);


    }
}
