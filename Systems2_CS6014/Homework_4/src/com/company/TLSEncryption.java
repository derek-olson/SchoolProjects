package com.company;

import javax.crypto.*;
import java.io.*;
import java.net.Socket;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

public class TLSEncryption {

    static void read(ObjectInputStream objectInputStream, byte[] macKey, Socket socket, byte[] keySpec, byte[] ivSpec, String outFileName) throws IOException, InvalidKeyException, NoSuchAlgorithmException, ClassNotFoundException, IllegalBlockSizeException, BadPaddingException, InvalidAlgorithmParameterException, NoSuchPaddingException {
        FileOutputStream fileOutputStream = null;
        if(!outFileName.equals("")){
            fileOutputStream = new FileOutputStream(outFileName);
        }
        int bytesToRead = objectInputStream.readInt();

        while(bytesToRead > 0){
            byte[] cipherText = (byte[]) objectInputStream.readObject();
            byte[] decrypted = TLSEncryption.decrypt(cipherText, KeyGeneration.makeSecretKeySpec(keySpec), KeyGeneration.makeIvParameterSpec(ivSpec));
            ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(decrypted);
            byte[] message = byteArrayInputStream.readNBytes(decrypted.length - 32);
            byte[] makdMessage = byteArrayInputStream.readAllBytes();
            if(!Arrays.equals(KeyGeneration.hmac(macKey, message), makdMessage)){
                System.out.println("Error: Message MAC Failure!");
                socket.close();
                return;
            }
            if(outFileName.equals("")){
                System.out.println(new String(message));
            }else{
                fileOutputStream.write(decrypted);
            }
            bytesToRead--;
        }

    }

    static void write(String fileName, ByteArrayOutputStream makdBytes, ObjectOutputStream objectOutputStream, byte[] mac, byte[] key, byte[] iv) throws IOException, InvalidKeyException, NoSuchAlgorithmException, IllegalBlockSizeException, BadPaddingException, InvalidAlgorithmParameterException, NoSuchPaddingException {
        FileInputStream fileInputStream;
        if(fileName == ""){
            String message = "File was received";
            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
            byte[] mkd = KeyGeneration.hmac(mac, message.getBytes());
            byteArrayOutputStream.write(message.getBytes());
            byteArrayOutputStream.write(mkd);
            byte[] enc = TLSEncryption.encrypt(KeyGeneration.makeSecretKeySpec(key), byteArrayOutputStream.toByteArray(), KeyGeneration.makeIvParameterSpec(iv));
            objectOutputStream.writeInt(1);

            objectOutputStream.writeObject(enc);
            objectOutputStream.flush();
        }else {
            fileInputStream = new FileInputStream(fileName);

            byte[] toSend;
            int bytesToSend = fileInputStream.available();
            int packetSize = 262144;
            int packetsToSend = (bytesToSend / (packetSize - 32)) + 1;
            objectOutputStream.writeInt(packetsToSend);
            while (fileInputStream.available() > 0) {

                if (fileInputStream.available() > packetSize - 32) {
                    toSend = fileInputStream.readNBytes(packetSize - 32);
                } else {
                    toSend = fileInputStream.readAllBytes();
                }
                byte[] makd = KeyGeneration.hmac(mac, toSend);

                makdBytes.write(toSend);
                makdBytes.write(makd);
                byte[] encrypted = TLSEncryption.encrypt(KeyGeneration.makeSecretKeySpec(key), makdBytes.toByteArray(), KeyGeneration.makeIvParameterSpec(iv));
                objectOutputStream.writeObject(encrypted);
                objectOutputStream.flush();
                makdBytes.reset();
            }
        }
    }

    public static byte[] encrypt(SecretKeySpec key, byte[] message, IvParameterSpec IV ) throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidAlgorithmParameterException, InvalidKeyException, BadPaddingException, IllegalBlockSizeException {
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");

        SecretKeySpec keySpec = new SecretKeySpec(key.getEncoded(), "AES");

        cipher.init(Cipher.ENCRYPT_MODE, keySpec, IV);

        byte[] cipherText = cipher.doFinal(message);

        return cipherText;
    }

    public static byte[] decrypt(byte[] cipherText, SecretKeySpec key, IvParameterSpec IV) throws NoSuchPaddingException, NoSuchAlgorithmException, InvalidAlgorithmParameterException, InvalidKeyException, BadPaddingException, IllegalBlockSizeException {
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");

        SecretKeySpec keySpec = new SecretKeySpec(key.getEncoded(), "AES");

        cipher.init(Cipher.DECRYPT_MODE, keySpec, IV);

        return cipher.doFinal(cipherText);
    }
}
