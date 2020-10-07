package com.company;

import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;


public class Websocket {
    private String room;
    private String user;
    private boolean join = false;
    byte[] decoded;
    int bytesToRead;

    Websocket(){};

    public void handShake(Socket client, String key) throws IOException, NoSuchAlgorithmException {
        OutputStream out = client.getOutputStream();
        byte[] response;
        response = ("HTTP/1.1 101 Switching Protocols\r\n"
                + "Connection: Upgrade\r\n"
                + "Upgrade: websocket\r\n"
                + "Sec-WebSocket-Accept: "
                + Base64.getEncoder().encodeToString(MessageDigest.getInstance("SHA-1").digest((key
                + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11").getBytes(StandardCharsets.UTF_8)))
                + "\r\n\r\n").getBytes(StandardCharsets.UTF_8);
        out.write(response);
        out.flush();
    }

    public String decode(Socket client) throws IOException {
        DataInputStream in = new DataInputStream(client.getInputStream());

        byte firstByte = in.readByte();
        System.out.println("first byte: " + (firstByte & 0x0f)); // prints the opcode

        byte secondByte = in.readByte();
        bytesToRead = secondByte & 0x7f; // get the payload
        if (bytesToRead < 125){
            bytesToRead = bytesToRead;
        }else if(bytesToRead == 126){
            //read the next 16 bits
            int bytes = in.readShort();
            bytesToRead = bytes;
        }else if(bytesToRead == 127){
            //read the next 64 bits
            bytesToRead = in.readInt();
        }

        byte[] key = new byte[4];
        in.readFully(key, 0, 4); //get the mask, it is always 4 bytes

        byte[] encoded = new byte[bytesToRead];
        in.readFully(encoded, 0, bytesToRead);// get the encoded bytes

        decoded = new byte[bytesToRead]; // set the length of the out message
        for (int i = 0; i < encoded.length; i++) {
            decoded[i] = (byte) (encoded[i] ^ key[i & 0x3]);
        }

        String decodedString = new String(decoded);
        joinRoom(decodedString);
        return decodedString;
    }

    public void writeMessage(Socket client, String decodedString) throws IOException {
        DataOutputStream out = new DataOutputStream(client.getOutputStream());
        out.write(0x81);
        out.write((byte) bytesToRead);
        out.write(decodedString.getBytes());
    }

    public static void sendNewMessage(Socket socket, String string) throws IOException {
        DataOutputStream out = new DataOutputStream(socket.getOutputStream());
        out.write(0x81);
        out.write((byte) string.length());
        out.write(string.getBytes());
    }

    public void joinRoom(String decodedString){
        if (decodedString.startsWith("join")){
            user = decodedString.split(" ", 3)[1];
            System.out.println("user: "+user);
            room = decodedString.split(" ", 3)[2];
            System.out.println("room: "+room);
            join = true;
        }
    }

    public String getUser(){
        return user;
    }

    public String getRoom(){
        return room;
    }

    public boolean getJoin(){
        return join;
    }

    public void setJoin(boolean join){
        this.join = join;
    }
}

