package com.company;

import java.io.*;
import java.util.Arrays;

public class DNSHeader {
    private byte[] dnsResponseHeader;
    byte [] ID = new byte[2]; //doesn't change between query and response
    int QR; // 0 for query and 1 for response
    byte OpCode; // 0, 1, or 2 (0 for standard query)
    byte z; // always 0
    byte rCode; //set for response. 0 for no error and 3 for domain name doesn't exist (for errors use 1, 2, or 3)
    byte[] qdCount = new byte[2]; // number of entries in the Question Section
    byte[] anCount = new byte[2]; // number of resource records in the Answer Section
    byte[] nsCount = new byte[2]; // number of name server resource records in the Authority Section
    byte[] arCount = new byte[2]; // number of resource records in the Additional Section

    DNSHeader(){}

    boolean isQuery(){
        if(this.QR == 0){
            return true;
        }
        return false;
    }

    static DNSHeader decodeHeader(ByteArrayInputStream inputStream) throws IOException {
        //construct new DNS header class
        DNSHeader dnsHeader = new DNSHeader();

        dnsHeader.ID = inputStream.readNBytes(2);

        byte[] temp;
        temp = inputStream.readNBytes(2);

        if(temp[0] >= 0){
            dnsHeader.QR = 0;
        }else{
            dnsHeader.QR = 1;
        }

        dnsHeader.OpCode = (byte)(temp[0] & 0b01111000);

        dnsHeader.z = 0b0000000;

        dnsHeader.rCode = temp[1];

        dnsHeader.qdCount = inputStream.readNBytes(2);
        dnsHeader.anCount = inputStream.readNBytes(2);
        dnsHeader.nsCount = inputStream.readNBytes(2);
        dnsHeader.arCount = inputStream.readNBytes(2);

        return dnsHeader;
    }

    static DNSHeader buildResponseHeader(DNSMessage request, DNSMessage response) throws IOException {
        DNSHeader dnsHeaderResponse = new DNSHeader();

        dnsHeaderResponse.ID = request.dnsHeader.ID;
        dnsHeaderResponse.QR = 1;
        dnsHeaderResponse.OpCode = request.dnsHeader.OpCode;
        dnsHeaderResponse.z = request.dnsHeader.z;
        dnsHeaderResponse.rCode = request.dnsHeader.rCode;
        dnsHeaderResponse.qdCount = request.dnsHeader.qdCount;
        dnsHeaderResponse.anCount = request.dnsHeader.anCount;
        dnsHeaderResponse.nsCount = request.dnsHeader.nsCount;
        dnsHeaderResponse.arCount = request.dnsHeader.arCount;

        return dnsHeaderResponse;
    }

    void writeBytes(ByteArrayOutputStream byteOutputStream) throws IOException {
        byteOutputStream.write(ID);
        byte qrByte = (byte) QR;
        byte qrOpCode = (byte) ((byte)(qrByte << 7) | (OpCode << 3));
        byteOutputStream.write(qrOpCode);
        byteOutputStream.write(rCode);
        byteOutputStream.write(qdCount);
        byteOutputStream.write(anCount);
        byteOutputStream.write(nsCount);
        byteOutputStream.write(arCount);

        dnsResponseHeader = byteOutputStream.toByteArray();

        //if this method requires an outputstream than below can be used
        //outputStream.write(dnsResponseHeader);
    }

    @Override
    public String toString() {
        return "DNSHeader{" +
                "dnsResponseHeader=" + Arrays.toString(dnsResponseHeader) +
                ", ID=" + Arrays.toString(ID) +
                ", QR=" + QR +
                ", OpCode=" + OpCode +
                ", z=" + z +
                ", rCode=" + rCode +
                ", qdCount=" + Arrays.toString(qdCount) +
                ", anCount=" + Arrays.toString(anCount) +
                ", nsCount=" + Arrays.toString(nsCount) +
                ", arCount=" + Arrays.toString(arCount) +
                '}';
    }
}
