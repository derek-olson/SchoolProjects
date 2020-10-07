package com.company;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class Main {

    public static void main(String[] args) throws IOException {

        DatagramSocket datagramSocket = new DatagramSocket(8053);
        DNSCache dnsCache = new DNSCache();

        InetAddress googleAddress = InetAddress.getByName("8.8.8.8");

        while(true){
            byte [] byteArray = new byte [512];

            DatagramPacket datagramPacket = new DatagramPacket(byteArray, 512);

            datagramSocket.receive(datagramPacket);

            InetAddress address = datagramPacket.getAddress();
            int port = datagramPacket.getPort();

            DNSMessage dnsMessage = DNSMessage.decodeMessage(datagramPacket.getData());

            //check if the packet is a query or a response
            if(dnsMessage.dnsHeader.isQuery()){
                //if query then check if in cache
                System.out.println("Message is a Query \n");
                if(dnsCache.cache.containsKey(dnsMessage.dnsQuestion)){
                    System.out.println("Message Key is in the Cache \n");
                    //if in the cache check the ttl
                    if(dnsMessage.dnsRecord.timestampValid()){
                        //timestamp is valid, send response to client
                        System.out.println("Message timestamp is valid, sending response from cache \n");

                        DNSRecord dnsRecord = dnsCache.cache.get(dnsMessage.dnsQuestion);
                        ByteArrayOutputStream baos = new ByteArrayOutputStream();
                        dnsRecord.writeBytes(baos);
                        DNSMessage responseMessage = DNSMessage.buildResponse(dnsMessage, baos.toByteArray());

                        DatagramPacket packetToSend = new DatagramPacket(responseMessage.toBytes(), responseMessage.toBytes().length, address, port);
                        datagramSocket.send(packetToSend);

                    }
                    else{
                        //timestamp is invalid, remove from cache and send query to google
                        System.out.println("Message timestamp is invalid, forwarding query to Google \n");
                        datagramPacket = new DatagramPacket(byteArray, byteArray.length, googleAddress, 53);
                        datagramSocket.send(datagramPacket);

                        System.out.println("Removing Question from Cache \n");
                        dnsCache.cache.remove(dnsMessage.dnsQuestion);

                        System.out.println("Receiving response from Google \n");
                        byte[] bytesRec = new byte[512];
                        DatagramPacket packetRec = new DatagramPacket(bytesRec, 512);
                        datagramSocket.receive(packetRec);

                        System.out.println("Sending response to client \n");
                        DatagramPacket packetSend = new DatagramPacket(packetRec.getData(), 512, address, port);
                        datagramSocket.send(packetSend);

                        System.out.println("Adding response to Cache \n");
                        DNSMessage dnsm = DNSMessage.decodeMessage(packetSend.getData());
                        dnsCache.cache.put(dnsm.dnsQuestion, dnsm.dnsRecord);
                    }
                }
                else{
                    //not in the cache, send query to google and add to cache
                    System.out.println("Message key is not in the Cache \n");
                    //initialize a new packet with bytes from the client, but with Google's address and port
                    DatagramPacket packetFromClient = new DatagramPacket(byteArray, byteArray.length, googleAddress, 53);
                    //Send the packet to Google
                    System.out.println("Sending message to Google \n");
                    datagramSocket.send(packetFromClient);
                    //create a new byte array to receive bytes from Google
                    byte[] recBytes = new byte[512];
                    //Construct a new packet for receiving, and put the byte array into a new packet to return to the client
                    DatagramPacket packetFromGoogle = new DatagramPacket(recBytes, 512);
                    datagramSocket.receive(packetFromGoogle);
                    System.out.println("Received packet from Google \n");
                    //Construct a new packet for sending, and add the byte array from google along with the clients address and port
                    DatagramPacket packetForClient = new DatagramPacket(packetFromGoogle.getData(), 512, address, port);
                    System.out.println("Sending message to client \n");
                    datagramSocket.send(packetForClient);

                    DNSMessage dnsm = DNSMessage.decodeMessage(packetForClient.getData());
                    dnsCache.cache.put(dnsm.dnsQuestion, dnsm.dnsRecord);
                }
            }
            else{
                // it is an unhandled response, throw error
                System.out.println("Error: Unhandled response \n");
            }
        }
    }
}
