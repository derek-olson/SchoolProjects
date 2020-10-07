package com.company;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Objects;

public class DNSQuestion {
    byte[] qName; // the domain name being queried
    short qType; // the resource records being requested
    short qClass; // The class of resource records being requested


    static DNSQuestion decodeQuestion(ByteArrayInputStream inputStream, DNSMessage dnsMessage) throws IOException {
        DNSQuestion dnsQuestion = new DNSQuestion();
        DataInputStream din = new DataInputStream(inputStream);

        int recLen = 0;
        while ((recLen = din.readByte()) > 0) {
            byte[] record = new byte[recLen];

            for (int i = 0; i < recLen; i++) {
                record[i] = din.readByte();
            }

            dnsQuestion.qName = record;
        }

        dnsQuestion.qType = din.readShort();
        dnsQuestion.qClass = din.readShort();

        return dnsQuestion;
    }
    //
    void writeBytes(ByteArrayOutputStream byteArrayOutputStream, HashMap<String,Integer> domainNameLocations) throws IOException {
        String qNameString = new String(qName); // this is for the hash
        //; this is for the hash - the index
        domainNameLocations.put(qNameString, byteArrayOutputStream.size());
        byteArrayOutputStream.write(qName);
        byteArrayOutputStream.write(qType);
        byteArrayOutputStream.write(qClass);

    }

    @Override
    public String toString() {
        return "DNSQuestion{" +
                "qName=" + Arrays.toString(qName) +
                ", qType=" + qType +
                ", qClass=" + qClass +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        DNSQuestion that = (DNSQuestion) o;
        return qType == that.qType &&
                qClass == that.qClass &&
                Arrays.equals(qName, that.qName);
    }

    @Override
    public int hashCode() {
        int result = Objects.hash(qType, qClass);
        result = 31 * result + Arrays.hashCode(qName);
        return result;
    }
}
