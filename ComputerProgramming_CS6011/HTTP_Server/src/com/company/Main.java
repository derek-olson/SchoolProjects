package com.company;

import java.io.*;
import java.net.*;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.Map;


public class Main {

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8080);
        Map<String, Room> roomMap = new HashMap<String, Room>();

        while(true){
            try{
                HTTP_Request http_request = new HTTP_Request();

                Socket socket = http_request.socket(serverSocket);

                Thread thread = new Thread(()->{

                    try {
                        System.out.println("Step 0");
                        BufferedReader readRequest = http_request.readRequest(socket);
                        System.out.println("Step 1");
                        http_request.parseHTML(readRequest);
                        System.out.println("Step 2");
                        if(http_request.websocket){

                            Websocket websocket = new Websocket();
                            websocket.handShake(socket, http_request.key);

                            while (true) {
                                String decoded = websocket.decode(socket);
                                System.out.println("WS MESSAGE: " + decoded);
                                if (websocket.getJoin()){
                                    System.out.println("join request");
                                    if (roomMap.containsKey(websocket.getRoom())){
                                        System.out.println("room exists");
                                        Room current_room = roomMap.get(websocket.getRoom());
                                        current_room.joinRoom(websocket.getUser(), socket, websocket);
                                        websocket.setJoin(false);
                                    }else{
                                        System.out.println("created new room");
                                        Room room = new Room();
                                        room.joinRoom(websocket.getUser(), socket, websocket);
                                        roomMap.put(websocket.getRoom(), room);
                                        websocket.setJoin(false);
                                    }
                                }else{
                                    System.out.println("message");
                                    Room current_room = roomMap.get(decoded.split(" ", 3)[0]);
                                    String username = websocket.getUser();
                                    System.out.println("Decoded: " + decoded);
                                    String message = decoded.split(" ", 3)[2];
                                    System.out.println(message);
                                    String outMessage = username+": "+message;
                                    current_room.storeMessages(username, message);
                                    //write to all websockets in the room
//                                    websocket.sendNewMessage(socket, outMessage);
                                }
                            }
                        }

                        else {
                            System.out.println("Step 3");
                            File file = http_request.getRequestedFile();

                            //String method = http_request.getMethod();

                            HTTP_Response http_response = new HTTP_Response();

                            PrintWriter printWriter = http_response.printWriter(socket);

                            //http_request.checkFile(file, printWriter);

                            // http_request.checkMethod(method, file, printWriter);

                            BufferedOutputStream outStream = http_response.outStream(socket);

                            http_response.sendHeaderResponse(printWriter, file);
                            System.out.println("Step 4");
                            http_response.sendData(outStream, file, socket);
                            System.out.println("Step 5");
//                            printWriter.close();
                            socket.close();
                        }

                    } catch (IOException | NoSuchAlgorithmException e) {
                        e.printStackTrace();
                    }
                });
                thread.start();
            }
            catch(IOException e) {
                e.printStackTrace();
                break;
            }
        }
    }
}


