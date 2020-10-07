package com.company;

import java.io.*;
import java.net.*;
import java.util.*;

public class HTTP_Request {

    public HTTP_Request(){};

    private String method;
    private String request;
    ArrayList parsedHTML = new ArrayList();
    public String key;
    public  boolean websocket = false;

    public Socket socket(ServerSocket serverSocket) throws IOException {
        //The server invokes the accept() method of the ServerSocket class.
        // This method waits until a client connects to the server on the given port.
        return serverSocket.accept();
    }

    public BufferedReader readRequest(Socket socket) throws IOException {
        // read from the client using input stream on the socket
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        return in;
    }

    public void parseHTML(BufferedReader in) throws IOException {
        String clientInput;
        while (!(clientInput = in.readLine()).equals("")) {
            parsedHTML.add(clientInput);
            if(clientInput.contains("Sec-WebSocket-Key")){
                websocket = true;
                key = clientInput.split(": ", 2)[1];
            }
        }
        System.out.println(parsedHTML);
    }

//    public void createMap(){
//        for(int i = 0; i < parsedHTML.size(); i++){
//            String temp = (String) parsedHTML.get(i);
//            System.out.println("temp "+temp);
//            String[] str = temp.split(": ", 2);
//            System.out.println("split "+str[0]);
//            //httpDict.put(str[0], str[1]);
//        }
//        //System.out.println(httpDict);
//    }

    public String getMethod(){
        String line1 = (String) parsedHTML.get(0);
        String arr[] = line1.split(" ", 3);
        method = arr[0].toUpperCase();
        //System.out.println("METHOD: " + method);
        return method;
    }

    public File getRequestedFile(){
        String line1 = (String) parsedHTML.get(0);
        String arr[] = line1.split(" ", 3);
        request = arr[1];
        if(request.equals("/")){
            request = "resources/index.html";
        }else{
            request = "resources"+request;
        }
        //System.out.println("REQUEST: " + request);
        File file = new File(request);
        return file;
    }


    public static void checkFile(File file, PrintWriter out) {
        if (!file.exists()) {
            out.println("HTTP/1.1 404 File Not Found");
            out.println("Server: Java HTTP Server : 1.0");
            out.println("Date: " + new Date());
            out.println("Content-type: " + "text/html");
            out.println("Content-length: " + file.length());
            out.println("");
            out.flush();
        }
    }

    public static void checkMethod(String method, File file, PrintWriter out) {
        if (!method.equals("GET")) {
            out.println("HTTP/1.1 400 Bad Request");
            out.println("Server: Java HTTP Server : 1.0");
            out.println("Date: " + new Date());
            out.println("Content-type: " + "text/html");
            out.println("Content-length: " + file.length());
            out.println("");
            out.flush();
        }
    }



}
