package com.company;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;
import java.math.BigInteger;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.util.Arrays;

public class TLSHandshake {


    static Certificate getCertificate(String  certificate) throws CertificateException, FileNotFoundException {
        CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
        InputStream certificateInputStream = new FileInputStream(certificate);
        Certificate cert = certificateFactory.generateCertificate(certificateInputStream);
        return cert;
    }


    static PrivateKey getPrivateKey(String  certificate) throws IOException, InvalidKeySpecException, NoSuchAlgorithmException {
        InputStream clientPrivateKeyIS = new FileInputStream(certificate);
        byte[] spk = clientPrivateKeyIS.readAllBytes();
        PKCS8EncodedKeySpec pkcs8EncodedKeySpecClient = new PKCS8EncodedKeySpec(spk);
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        return keyFactory.generatePrivate(pkcs8EncodedKeySpecClient);
    }

    static Signature getSignature() throws NoSuchAlgorithmException {
        return Signature.getInstance("SHA256withRSA");
    }

    static byte[] sign(BigInteger KSDH, Signature signature, PrivateKey privateKey) throws SignatureException, InvalidKeyException {
        byte[] clientToSign = KSDH.toByteArray();
        signature.initSign(privateKey);
        signature.update(clientToSign);
        return signature.sign();
    }

    //the big integer may need to be a byte array
    static boolean verify(PublicKey serverPublicKey, BigInteger serverKSDH, byte[] serverSignature, Signature signature) throws InvalidKeyException, SignatureException {
        signature.initVerify(serverPublicKey);
        signature.update(serverKSDH.toByteArray());
        return signature.verify(serverSignature);
    }

    static boolean verifyMac(byte[] serverMACMessage, byte[] secretKeySpec, ByteArrayOutputStream messageHistoryBytes) throws InvalidKeyException, NoSuchAlgorithmException {
        return Arrays.equals(serverMACMessage, KeyGeneration.hmac(secretKeySpec, messageHistoryBytes.toByteArray()));
    }

}
