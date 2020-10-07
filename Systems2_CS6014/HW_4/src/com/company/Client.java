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
import java.util.Random;

public class Client {
    static String nString = "32317006071311007300338913926423828248817941241140239112842009751400741706634354222619689417363569347117901737909704191754605873209195028853758986185622153212175412514901774520270235796078236248884246189477587641105928646099411723245426622522193230540919037680524235519125679715870117001058055877651038861847280257976054903569732561526167081339361799541336476559160368317896729073178384589680639671900977202194168647225871031411336429319536193471636533209717077448227988588565369208645296636077250268955505928362751121174096972998068410554359584866583291642136218231078990999448652468262416972035911852507045361090559";
    static BigInteger p = new BigInteger(nString);
    static BigInteger g = new BigInteger("2");
    BigInteger KS;
    BigInteger KSDH;
    PublicKey PublicKey;
    PrivateKey PrivateKey;
    Signature signature;
    BigInteger DH;
    ObjectOutputStream objectOutputStream;
    ObjectInputStream objectInputStream;

    public Client() throws NoSuchAlgorithmException, CertificateException, IOException, InvalidKeySpecException {
        computeKS();
        computeKSDH();
        getPublicKey();
        getPrivateKey();
        getSignature();
    }

    void computeKS(){
        this.KS = new BigInteger(256, new Random());
    }

    void computeKSDH(){
        this.KSDH = g.modPow(KS, p);
    }

    void getPublicKey() throws CertificateException, FileNotFoundException {
        CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
        InputStream clientCertificateInputStream = new FileInputStream("CASignedClientCertificate.pem");
        Certificate clientCertificate = certificateFactory.generateCertificate(clientCertificateInputStream);
        this.PublicKey = clientCertificate.getPublicKey();
    }

    void getPrivateKey() throws IOException, InvalidKeySpecException, NoSuchAlgorithmException {
        InputStream clientPrivateKeyIS = new FileInputStream("clientPrivateKey.der");
        byte[] spk = clientPrivateKeyIS.readAllBytes();
        PKCS8EncodedKeySpec pkcs8EncodedKeySpecClient = new PKCS8EncodedKeySpec(spk);
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        this.PrivateKey = keyFactory.generatePrivate(pkcs8EncodedKeySpecClient);
    }

    void getSignature() throws NoSuchAlgorithmException {
        this.signature = Signature.getInstance("SHA256withRSA");
    }

    byte[] getClientToSign() throws SignatureException, InvalidKeyException {
        byte[] clientToSign = KSDH.toByteArray();
        signature.initSign(PrivateKey);
        signature.update(clientToSign);
        return  signature.sign();
    }

    //the big integer may need to be a byte array
    boolean verifyServer(PublicKey serverPublicKey, BigInteger serverKSDH, byte[] serverSignature) throws InvalidKeyException, SignatureException {
        signature.initVerify(serverPublicKey);
        signature.update(serverKSDH.toByteArray());
        boolean verify = signature.verify(serverSignature);
        System.out.println(verify);
        return verify;
    }

    void computeDH(BigInteger serverKSDH){
        this.DH = serverKSDH.modPow(KS, p);
        System.out.println(DH);
    }

//    void writeToOutputSteam(ByteArrayInputStream byteArrayInputStream){
//        byte[] bytes = byteArrayInputStream.readAllBytes();
//        byteArrayOutputStream.writeBytes(bytes);
//    }

    void hmac(byte[] secretKeySpec) throws NoSuchAlgorithmException, InvalidKeyException, IOException, ClassNotFoundException, CertificateEncodingException {
        Certificate certificate = (Certificate) objectInputStream.readObject();
        BigInteger dhpk = (BigInteger) objectInputStream.readObject();
        BigInteger sdhpk = (BigInteger) objectInputStream.readObject();
        //byte[] test =  certificate.getEncoded();
        Mac sha256_HMAC = null;
        final String HMAC_SHA256 = "HmacSHA256";
        sha256_HMAC = Mac.getInstance(HMAC_SHA256);
        SecretKeySpec keySpec = new SecretKeySpec(secretKeySpec, HMAC_SHA256);
        sha256_HMAC.init(keySpec);
        byte[] mac = sha256_HMAC.doFinal();
        objectOutputStream.write(mac);
    }

}
