package com.company;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

public class DNSMessage {
    DNSHeader dnsHeader;
    DNSQuestion dnsQuestion;
    DNSRecord dnsRecord;
    byte[] dns_Question;
    byte[] dns_Header;
    byte[] questions;
    byte[] answers;
    byte[] authorityRecords;
    byte[] additionalRecords;
    static byte[] dns_Message;

    static DNSMessage decodeMessage(byte[] bytes) throws IOException {
        DNSMessage dnsMessage = new DNSMessage();

        InputStream is = new ByteArrayInputStream(bytes);

        dnsMessage.dns_Message = bytes;
        dnsMessage.dns_Header = Arrays.copyOfRange(bytes, 0, 13);

        is.readNBytes(4);
        dnsMessage.questions = is.readNBytes(2);
        dnsMessage.answers = is.readNBytes(2);
        dnsMessage.authorityRecords = is.readNBytes(2);
        dnsMessage.additionalRecords = is.readNBytes(2);

        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(dns_Message);
        dnsMessage.dnsHeader = DNSHeader.decodeHeader(byteArrayInputStream);
        dnsMessage.dnsQuestion = DNSQuestion.decodeQuestion(byteArrayInputStream, dnsMessage);
        dnsMessage.dnsRecord = DNSRecord.decodeRecord(byteArrayInputStream, dnsMessage);

        return dnsMessage;
    }

    String[] readDomainName(ByteArrayInputStream inputStream){
        ArrayList<Byte> al = new ArrayList<Byte>();

        while(inputStream.read() != 0){
            al.add((byte)inputStream.read());
        }

        String[] sa = new String[al.size()];

        for(int i = 0; i < al.size(); i++){
            sa[i] = al.get(i).toString();
        }

        return sa;
    }

    String[] readDomainName(int firstByte){
        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(dns_Message, firstByte, 507);
        return readDomainName(byteArrayInputStream);
    }


    static DNSMessage buildResponse(DNSMessage request, byte[] answers) throws IOException {
        DNSMessage dnsMessage = new DNSMessage();

        //build header
        dnsMessage.dnsHeader = DNSHeader.buildResponseHeader(request, dnsMessage);

        //build question
        dnsMessage.dnsQuestion = request.dnsQuestion;

        //build record
        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(answers);
        dnsMessage.dnsRecord = DNSRecord.decodeRecord(byteArrayInputStream, dnsMessage);

        return dnsMessage;
    }

    byte[] toBytes() throws IOException {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        HashMap<String, Integer> domainLocations = new HashMap<>();
        this.dnsHeader.writeBytes(bos);
        this.dnsQuestion.writeBytes(bos, domainLocations);
        this.dnsRecord.writeBytes(bos, domainLocations);
        byte [] data = bos.toByteArray();
        return data;
    }

//    static void writeDomainName(ByteArrayOutputStream byteArrayOutputStream, HashMap<String,Integer> domainLocations, String[] domainPieces){
//
//        writeBytes(byteArrayOutputStream, domainLocations);
//    }

//    String octetsToString(String[] octets){
//
//    }


    @Override
    public String toString() {
        return "DNSMessage{" +
                "dnsHeader=" + dnsHeader +
                ", dnsQuestion=" + dnsQuestion +
                ", dnsRecord=" + dnsRecord +
                ", dns_Question=" + Arrays.toString(dns_Question) +
                ", dns_Header=" + Arrays.toString(dns_Header) +
                ", questions=" + Arrays.toString(questions) +
                ", answers=" + Arrays.toString(answers) +
                ", authorityRecords=" + Arrays.toString(authorityRecords) +
                ", additionalRecords=" + Arrays.toString(additionalRecords) +
                '}';
    }
}
