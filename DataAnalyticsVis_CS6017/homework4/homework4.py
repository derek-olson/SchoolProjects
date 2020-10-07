#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jun 17 18:50:10 2020

@author: derekolson
"""

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import statsmodels.formula.api as smf
import statsmodels.api as sm

data = pd.read_csv("/Users/derekolson/DerekOlson/CS6017/homework4/spatialDatastructuresStarterCode/output.csv")
data['n'] = data['n']*10
sns.boxplot(x='type', y='time', hue='dim', data=data)
sns.boxplot(x='type', y='time', hue='k', data=data)
sns.boxplot(x='type', y='time', hue='n', data=data)

bucket = data[data['type']== 'bucket'] 
kdtree = data[data['type'] == 'kdtree'] 
quadtree = data[data['type'] == 'quadtree']
dumb = data[data['type'] == 'dumb']

#Here we evaluate structures with 2 dimensions inorder to compare quadtree against other structures
df2 = data[data['dim'] == 2]
sns.boxplot(x='type', y='time', hue='dim', data=df2)
#bucket appears to perform the best with 2 dimensions. 
sns.boxplot(x='type', y='time', hue='k', data=df2)
#quadtree and kdtree appear to be the most affected by a changing value of K.
sns.boxplot(x='type', y='time', hue='n', data=df2)
#Time increases with an increasing N for all structures. Time increases most rapidly for dumbknn. 

#Ploting part of my data to make sense of it
#subset the dimension data where there are more than two dimensions
#does dimension have any impact on time?
df = data[data['dim'] > 2]
sns.boxplot(x='type', y='time', hue='dim', data=df).set_title('Dimension')
#It appears that time increases for each structure as the number of dimensions increases.
#WHICH INCREASES THE MOST 
sns.boxplot(x='type', y='time', hue='n', data=df).set_title('N')
#Intuitively time also increases as the number of training points increases for all structures.
#WHICH INCREASES THE MOST 
sns.boxplot(x='type', y='time', hue='k', data=df).set_title('K')
#The value of K seems to impact kdtree the most while both dumbknn and bucket are relatively flat in response to an increasing K. 

#In the plots above each variable is not isolated so it is impossible to isolate the effect of an individual variable
#In the loops below we plot each interval of N, K, and D inorder to better understand the effects of each variable
for i in range(1,8,1):
    print(i)
    dim = data[(data['dim'] == i) & (data['dim'] > 2)]
    plt.figure()
    sns.boxplot(x='type', y='time', hue='n', data=dim).set_title('Dimension = '+str(i))

#Does N increase time?
#subset the training data
for i in range(1000,11000,1000):
    print(i)
    n = data[(data['n'] == i) & (data['dim'] > 2)]
    plt.figure()
    sns.boxplot(x='type', y='time', hue='dim', data=n).set_title('N = '+str(i))
    
#Does K increase time?
#subset the k data
for i in range(10,60,10):
    print(i)
    k = data[(data['k'] == i) & (data['dim'] > 2)]
    plt.figure()
    sns.boxplot(x='type', y='time', hue='n', data=k).set_title('K = '+str(i))
  



#what impact to K, N, D, and the data structure have?
#Bucket time is not strongly affected by k
#First two dimensions removed to account for non-linear trends with kdtree
dummies = pd.get_dummies(df)
x = dummies.drop('time', axis=1)
x = sm.add_constant(x)
y=df['time']
model = sm.OLS(y,x).fit()
model.summary()

model1 = smf.ols(formula='time ~ k', data=df)
res1 = model1.fit()
print(res1.summary())
fig1= plt.figure(figsize=(12,8))
fig1 = sm.graphics.plot_partregress_grid(res1, fig=fig1)


model2 = smf.ols(formula='time ~ dim', data=df)
res2 = model2.fit()
print(res2.summary())
fig2= plt.figure(figsize=(12,8))
fig2 = sm.graphics.plot_partregress_grid(res2, fig=fig2)


model3 = smf.ols(formula='time ~ n', data=df)
res3 = model3.fit()
print(res3.summary())
fig3= plt.figure(figsize=(12,8))
fig3 = sm.graphics.plot_partregress_grid(res3, fig=fig3)

#Do tests confirm or disprove our expectations? What running times do you expect to see based on simple big-O analysis?



#Anything unusual

