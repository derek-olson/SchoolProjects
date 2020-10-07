package com.company;

import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Room {
    private ArrayList<String> users = new ArrayList<>();
    private ArrayList<Socket> sockets = new ArrayList<>();
    private ArrayList<String> messages = new ArrayList<String>();

    public Room(){}

    public void joinRoom(String user, Socket socket, Websocket websocket) throws IOException {
        users.add(user);
        sockets.add(socket);
        for (int i = 0; i < messages.size(); i = i+2) {
            String username = messages.get(i);
            String message = messages.get(i+1);
            Websocket.sendNewMessage(socket, username + ": " + message + "\n");
        }
    }

    public void storeMessages(String username, String message) throws IOException {
        messages.add(username);
        messages.add(message);
        sendMessages(message, username);
    }


    public void sendMessages(String message, String username) throws IOException {
        message = username+": "+message+"\n";
        for (Socket _socket : sockets) {
            Websocket.sendNewMessage(_socket, message);
        }
    }
}
