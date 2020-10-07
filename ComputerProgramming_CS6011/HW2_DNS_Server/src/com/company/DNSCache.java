package com.company;

import java.sql.Timestamp;
import java.util.Date;
import java.util.HashMap;

public class DNSCache {
    HashMap<DNSQuestion, DNSRecord> cache = new HashMap<DNSQuestion, DNSRecord>();

    boolean ttl(DNSRecord dnsRecord){
        Date date = new Date();
        long time = date.getTime();
        Timestamp ts = new Timestamp(time);

        if(dnsRecord.ttd.after(ts)){
            return false;
        }
        return true;
    }

    void add(DNSQuestion dnsQuestion, DNSRecord dnsRecord){
        if(this.cache.containsKey(dnsQuestion)){
            if(this.ttl(dnsRecord) == false){
                System.out.println("Cache contains key and is still valid \n");
            }
        }
        else{
            cache.put(dnsQuestion, dnsRecord);
            System.out.println("Added Question and Record to Cache \n");
        }
    }

}
