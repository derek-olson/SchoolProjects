package com.chatserver.chatServer;

import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import java.io.IOException;
import java.util.ArrayList;

public class Room {
    public static ArrayList<String> users = new ArrayList<>();
    public static ArrayList<WebSocketSession> sockets = new ArrayList<>();
    public static ArrayList<String> messages = new ArrayList<String>();

    public static void joinRoom(String user, WebSocketSession webSocketSession) throws IOException {
        users.add(user);
        sockets.add(webSocketSession);
        Handler.roomSessionMap.put(Handler.room, webSocketSession);
        for (int i = 0; i < messages.size(); i = i+2) {
            String username = messages.get(i);
            String message = messages.get(i+1);
            TextMessage textMessage = new TextMessage(username +": "+ message);
            webSocketSession.sendMessage(textMessage);
        }
    }

    public void storeMessages(String username, String message) throws IOException {
        messages.add(username);
        message = message.split(" ", 3)[2];
        messages.add(message);
        sendMessages(message, username);
    }

    public void sendMessages(String message, String username) throws IOException {
        message = username+": "+message+"\n";
        System.out.println("out message here: "+message);
        for (WebSocketSession webSocketSession : Handler.roomSessionMap.values()) {
            System.out.println("websocket session: "+webSocketSession);
            TextMessage textMessage = new TextMessage(message);
            webSocketSession.sendMessage(textMessage);
        }
    }
}
