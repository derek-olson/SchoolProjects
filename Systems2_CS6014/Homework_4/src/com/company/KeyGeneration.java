package com.company;

import javax.crypto.Mac;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.math.BigInteger;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;

public class KeyGeneration {
    static byte[] serverEncrypt;
    static byte[] clientEncrypt;
    static byte[] serverMAC;
    static byte[] clientMAC;
    static byte[] serverIV;
    static byte[] clientIV;

    static byte[] hmac(byte[] secretKeySpec, byte[] data) throws NoSuchAlgorithmException, InvalidKeyException {
        Mac sha256_HMAC = null;
        final String HMAC_SHA256 = "HmacSHA256";
        sha256_HMAC = Mac.getInstance(HMAC_SHA256);
        SecretKeySpec keySpec = new SecretKeySpec(secretKeySpec, HMAC_SHA256);
        sha256_HMAC.init(keySpec);
        return sha256_HMAC.doFinal(data);
    }

    static byte[] hkdfExpand(byte[] secretKeySpec, String data) throws NoSuchAlgorithmException, InvalidKeyException {
        byte[] tag = new byte[data.length() + 1];
        for(int i = 0; i < data.length(); i++){
            tag[i] = data.getBytes()[i];
        }
        tag[data.length()] = 0b00000001;

        byte[] mac = hmac(secretKeySpec, tag);

        byte[] okm = new byte[16];
        for(int i = 0; i < 16; i++){
            okm[i] = mac[i];
        }
        return okm;
    }

    static void makeSecretKeys(byte[] clientNonce, BigInteger sharedSecretFromDiffieHellman) throws InvalidKeyException, NoSuchAlgorithmException {
        byte[] prk = hmac(clientNonce, sharedSecretFromDiffieHellman.toByteArray());
        serverEncrypt = hkdfExpand(prk, "server encrypt");
        clientEncrypt = hkdfExpand(serverEncrypt, "client encrypt");
        serverMAC = hkdfExpand(clientEncrypt, "server MAC");
        clientMAC = hkdfExpand(serverMAC, "client MAC");
        serverIV = hkdfExpand(clientMAC, "server IV");
        clientIV = hkdfExpand(serverIV, "client IV");
    }

    static SecretKeySpec makeSecretKeySpec(byte[] keyBytes){
        final String HMAC_SHA256 = "HmacSHA256";
        return new SecretKeySpec(keyBytes, HMAC_SHA256);
    }

    static IvParameterSpec makeIvParameterSpec(byte[] keyBytes){
        return new IvParameterSpec(keyBytes);
    }

    public static byte[] getServerEncrypt() {
        return serverEncrypt;
    }

    public static byte[] getClientEncrypt() {
        return clientEncrypt;
    }

    public static byte[] getServerMAC() {
        return serverMAC;
    }

    public static byte[] getClientMAC() {
        return clientMAC;
    }

    public static byte[] getServerIV() {
        return serverIV;
    }

    public static byte[] getClientIV() {
        return clientIV;
    }

}
