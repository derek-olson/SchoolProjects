#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 19 09:28:59 2020

@author: derekolson
"""
import math
import pandas as pd
import seaborn as sb
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm

##############################################################################
#Part 1
##############################################################################
def mean(data):
    n = len(data)
    total = sum(data)
    return total/n

def sd(data):
    n = len(data)
    
    if n <=1:
        return 0.0
    
    m = mean(data)
    sd = 0.0
    
    for d in data:
        sd += (float(d) - m)**2
        
    sd = math.sqrt(sd/float(n-1))
    return sd

r = norm.rvs(size=1000)

my_mean = mean(r)
my_sd = sd(r)

np_mean = np.mean(r)
np_sd = np.std(r)

plt.hist(r)

##############################################################################
#Part 2
##############################################################################
path = "/Users/derekolson/DerekOlson/CS6017/homework1/2019-PM2.5.csv"
data = pd.read_csv(path)

series = data[['Unnamed: 0', 'SM.2']]
series.columns = ['Date', 'SM.2']
series = series.dropna()

#sb.scatterplot(x='Date', y='SM.2', Data=series)

df = series.astype({'Date':'datetime64[ns]', 'SM.2':'float64'})
df.index = df['Date']

monthly = df.resample('M').mean()
monthly['Date'] = monthly.index
monthly['Month'] = monthly['Date'].dt.month
sb.barplot(x='Month', y='SM.2', data=monthly)

hourly = df.groupby(df.index.hour).mean()
hourly['Hour'] = hourly.index
sb.barplot(x='Hour', y='SM.2', data=hourly)

df['hour'] = df['Date'].dt.hour
sb.boxplot(x='hour', y='SM.2', data=df)