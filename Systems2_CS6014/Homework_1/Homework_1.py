#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jan 11 12:14:33 2020

@author: derekolson
"""
import matplotlib.pyplot as plt
import numpy as np

#Question 1:

ts_500 = [10.0, 2.8, 2.4, 4.0, 5.5]
dif_500 = []
for t in ts_500:
    dif_500.append(t - 2.4)
    
avg_dif_500 = np .average(dif_500)   
    
#The average delay for 500 byte packets is 2.54 ms

ts_1000 = [11.0, 10.0, 2.8, 3.0, 5.5]
dif_1000 = []
for t in ts_1000:
    dif_1000.append(t - 2.8)
    
avg_dif_1000 = np .average(dif_1000)
#The average queing delay for 1000 byte packets is 3.66 ms

temp = (avg_dif_1000-avg_dif_500)/500

tAvg_600 = 100*temp+avg_dif_500
#The average queing delay for 600 byte packets is 2.76 ms

#2.4 = 500/TR + P
#2.8 = 1000/TR + P

# TR = 1250 & P = 2



#Question 2:
#a

def parseRoute(file):
    d = {}
    with open(file) as f:
        lines = f.readlines()
        for line in lines:
            items = line.split(" ")
            key1 = ""
            key2 = ""
            vals = []
            for item in items:
                if item.isnumeric():
                    key1 = item
                    d[key1] = {}
                if item.startswith("("):
                    key2 = item
                    d[key1] = {key2:[]}
                try:
                    float(item)
                    if len(item) > 2:
                        vals.append(item)
                except:
                    print()
                if key2 == '':
                    print("empty key")
                else:
                    d[key1][key2] = vals
    avgs = {}
    xkeys = []
    yvals = []
    for key in d.keys():
        k = list(d[key].keys())[0]
        xkeys.append(k)
        d[key][k] = np.array(d[key][k]).astype(np.float)
        avgs[key]={k: np.average(d[key][k])}
        yvals.append(np.average(d[key][k]))
    return avgs
            
file1 = "/Users/derekolson/DerekOlson/CS6014/traceroute_noaa_gov3.txt"
file2 = "/Users/derekolson/DerekOlson/CS6014/traceroute_noaa_gov_next2.txt"

tr1 = parseRoute(file1)
tr2 = parseRoute(file2)

xvals1 = list(tr1.keys())
yvals1 = []
labels1 = []
for k, v in tr1.items():
    for k1, v1 in v.items():
        labels1.append(k1)
        yvals1.append(v1)
        
xvals2 = list(tr2.keys())
yvals2 = []
labels2 = []
for k, v in tr2.items():
    for k1, v1 in v.items():
        labels2.append(k1)
        yvals2.append(v1)

f = plt.figure()
plt.plot(xvals1, yvals1)
plt.plot(xvals2, yvals2)
#plt.xticks(rotation=90)
plt.xlabel('Node')
plt.ylabel('milliseconds')
f.savefig("traceroute.pdf", bbox_inches='tight')

#b:
#Queing delay and transmission delay


#Question 3

ping_times = []
with open("/Users/derekolson/DerekOlson/CS6014/ping_space_uk_2.txt") as f2:
    lines2 = f2.readlines()
    for line in lines2:
        items2 = line.split(" ")
        for item2 in items2:
            if item2.startswith('time'):
                ping_times.append(item2[-7:])
                
ping_times = np.array(ping_times).astype(np.float)
minVal = ping_times[ping_times.argmin()]
ping_times = np.delete(ping_times, ping_times.argmin())
delays = [x - minVal for x in ping_times]
average_delay = np.average(delays)

#the average delay is 6.432440170940182 ms