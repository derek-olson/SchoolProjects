package com.company;

import java.io.*;
import java.net.Socket;
import java.util.Date;

public class HTTP_Response {
    HTTP_Response(){};

    // create server output stream
    public PrintWriter printWriter(Socket socket) throws IOException {
        // get the output stream to client (for headers)
        PrintWriter outP = new PrintWriter(socket.getOutputStream());
        return outP;
    }

    // get output stream for requested file
    public BufferedOutputStream outStream(Socket socket) throws IOException {
        BufferedOutputStream dataOut = new BufferedOutputStream(socket.getOutputStream());
        return dataOut;
    }

    public void sendHeaderResponse(PrintWriter out, File file) {
        out.println("HTTP/1.1 200 OK");
        out.println("Server: Java HTTP Server : 1.0");
        out.println("Date: " + new Date());
        out.println("Content-type: " + "text/html");
        out.println("Content-length: " + file.length());
        out.println("");
        out.flush();
    }

    public void sendData(BufferedOutputStream out, File file, Socket socket) throws IOException {
        out.write(new FileInputStream(file).read());
        out.flush();
        FileInputStream fs = new FileInputStream(file);
        fs.transferTo(socket.getOutputStream());
        socket.getOutputStream().flush();
//        out.close();
    }




}
