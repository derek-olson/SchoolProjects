package com.chatserver.chatServer;

import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.http.WebSocket;
import java.util.HashMap;
import java.util.Map;

public class Handler extends TextWebSocketHandler {
    public static String room;
    private String user;
    public static Map<String, WebSocketSession> roomSessionMap = new HashMap<>();
    public static Map<String, Room> roomStringMap = new HashMap<>();

    @Override
    protected void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception {
        if (message.getPayload().startsWith("join")){
            user = message.getPayload().split(" ", 3)[1];
            room = message.getPayload().split(" ", 3)[2];
            System.out.println("Room1: "+room);
            System.out.println("join request");
            if(roomStringMap.containsKey(room)){
                System.out.println("room exists");
                Room chatRoom = roomStringMap.get(room);
                chatRoom.joinRoom(user, session);
            }else{
                System.out.println("creating new room");
                Room chatRoom = new Room();
                roomStringMap.put(room, chatRoom);
                roomSessionMap.put(room, session);
            }
        }else{
            user = message.getPayload().split(" ", 3)[0];
            System.out.println("User2: "+user);
            room = message.getPayload().split(" ", 3)[1];
            System.out.println("Room2: "+room);
            Room chatRoom = roomStringMap.get(room);
            System.out.println("chatRoom:"+chatRoom);
            chatRoom.storeMessages(user, message.getPayload());
        }
    }



}
