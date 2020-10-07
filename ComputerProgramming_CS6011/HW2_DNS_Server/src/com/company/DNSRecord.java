package com.company;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;

public class DNSRecord {
    byte[] rName;
    short rType;
    short rClass;
    int ttl;
    short length;
    byte[] address;
    String[] rAddress;
    Timestamp ttd;

    static DNSRecord decodeRecord(ByteArrayInputStream inputStream, DNSMessage dnsMessage) throws IOException {
        DNSRecord dnsRecord = new DNSRecord();
        DataInputStream din = new DataInputStream(inputStream);
        byte marker = (byte)inputStream.read();

        //if the message is compressed
        if(marker < 0){
            dnsRecord.rName = new byte[2];
            dnsRecord.rName[0] = (byte) (marker & 0x3f);
            int index = 0;
            index = (dnsRecord.rName[0] << 8) | (dnsRecord.rName[1] & 0xff);
            dnsRecord.rAddress = dnsMessage.readDomainName(index);
        }
        else {
            //may need to start at the beginning of input stream here
            dnsRecord.rName = din.readNBytes(2);
        }

        dnsRecord.rType = din.readShort();
        dnsRecord.rClass = din.readShort();
        dnsRecord.ttl = din.readInt();
        dnsRecord.length = din.readShort();
        //figure out how to use rAddress here
        dnsRecord.address = din.readAllBytes();

        Calendar now = Calendar.getInstance();
        now.add(Calendar.SECOND, dnsRecord.ttl);
        dnsRecord.ttd = new Timestamp(now.getTimeInMillis() + (dnsRecord.ttl * 1000));

        return dnsRecord;
    }

    //
    void writeBytes(ByteArrayOutputStream byteArrayOutputStream, HashMap<String, Integer> hashMap) throws IOException {
        hashMap.put(new String(rName), byteArrayOutputStream.size());
        byteArrayOutputStream.write(rName);
        byteArrayOutputStream.write(rType);
        byteArrayOutputStream.write(ttl);
        byteArrayOutputStream.write(length);
        byteArrayOutputStream.write(address);
    }


    @Override
    public String toString() {
        return "DNSRecord{" +
                "rName=" + rName +
                ", rType=" + rType +
                ", rClass=" + rClass +
                ", ttl=" + ttl +
                ", length=" + length +
                ", address='" + address + '\'' +
                ", ttd=" + ttd +
                '}';
    }

    boolean timestampValid(){
        Date date = new Date();
        long time = date.getTime();
        Timestamp ts = new Timestamp(time);

        if(ts.after(this.ttd)){
            return false;
        }
        else{
            return true;
        }
    }
}
