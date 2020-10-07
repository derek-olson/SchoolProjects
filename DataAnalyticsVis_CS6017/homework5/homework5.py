#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 30 11:37:20 2020

@author: derekolson
"""

import pandas as pd
import numpy as np
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import GridSearchCV
from sklearn import tree, svm, metrics
from sklearn.neighbors import KNeighborsClassifier
from sklearn.neighbors import NeighborhoodComponentsAnalysis
from sklearn.pipeline import Pipeline
from sklearn.model_selection import train_test_split, cross_val_predict, cross_val_score, KFold
from sklearn.datasets import load_digits
from sklearn.preprocessing import scale
from sklearn.model_selection import ShuffleSplit
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
%matplotlib inline
plt.rcParams['figure.figsize'] = (10, 6)
plt.style.use('ggplot')

digits = load_digits()
X = scale(digits.data)
y = digits.target
print(type(X))

n_samples, n_features = X.shape
n_digits = len(np.unique(digits.target))
print("n_digits: %d, n_samples %d, n_features %d" % (n_digits, n_samples, n_features))

print("===\nThe raw data")
print(digits.images[0])
print("===\nThe scaled data")
print(X[0])
print("===\nThe digit")
print(digits.target[0])


plt.figure(figsize= (10, 10))    
for ii in np.arange(25):
    plt.subplot(5, 5, ii+1)
    plt.imshow(np.reshape(X[ii,:],(8,8)), cmap='Greys',interpolation='nearest')
    plt.axis('off')
plt.show()

##############################################################################
## 1 Test/Train Split
##############################################################################
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=1, test_size=0.8)

#2
svc = svm.SVC(kernel='rbf', C=100, gamma='auto')

svc.fit(X_train,y_train)
pred = svc.predict(X_test)

print('Accuracy = ', metrics.accuracy_score(y_true = y_test, y_pred = pred))

#3
conf_mat1 = confusion_matrix(y_test, pred)
print(conf_mat1)

##My biggest mistakes are 8 and 0.

##############################################################################
## 4 Print
##############################################################################
pred_all = svc.predict(X)

for i in range(len(y)):
    if y[i] != pred_all[i]:
        plt.figure()
        plt.imshow(digits.images[i], cmap=plt.cm.gray_r, interpolation='nearest')
        plt.show()
        print(i)

##############################################################################
## 5 Cross Val
##############################################################################
predicted = cross_val_predict(estimator=svc, X=X, y=y)
y_pred = pd.Series(predicted)

print('Accuracy = ', metrics.accuracy_score(y_true = y, y_pred = y_pred))

conf_mat = confusion_matrix(y, y_pred)
print(conf_mat)
     
cv = ShuffleSplit(n_splits=5, test_size=0.3, random_state=0)        
scores = cross_val_score(svc, X, y, cv=cv)
print(scores)     

##############################################################################
##Test Cost
##############################################################################
s = []
for i in range(1,501,5):
    svc = svm.SVC(kernel='rbf', C=i, gamma='auto')
    scores = cross_val_score(svc, X, y, cv=cv)
    s.append(np.mean(scores))
    print(scores)     

print(s)

# 5 was my best average score
##############################################################################
## 6 Unscaled Data
##############################################################################
x_unscaled = digits.data
X_train, X_test, y_train, y_test = train_test_split(x_unscaled, y, random_state=1, test_size=0.8)


svc = svm.SVC(kernel='rbf', C=100, gamma='auto')

svc.fit(X_train,y_train)
pred = svc.predict(X_test)

print('Accuracy = ', metrics.accuracy_score(y_true = y_test, y_pred = pred))

print(confusion_matrix(y_test, pred))     

#My accuracy was 11.8

##############################################################################
##KNN
##############################################################################        
#1&2
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=1, test_size=0.8)
nca = NeighborhoodComponentsAnalysis(random_state=1)
knn = KNeighborsClassifier(n_neighbors=10)
nca_pipe = Pipeline([('nca', nca), ('knn', knn)])
nca_pipe.fit(X_train, y_train)
print(nca_pipe.score(X_test, y_test))        
knn.fit(X_train, y_train)

#3
knn_pred = nca_pipe.predict(X_test)
print('Accuracy = ', metrics.accuracy_score(y_true = y_test, y_pred = knn_pred))

conf_mat = confusion_matrix(y_test, knn_pred)
print(conf_mat)

##My biggest mistakes are 8 and 9.

#4
pred_all_knn = knn.predict(X)

for i in range(len(y)):
    if y[i] != pred_all_knn[i]:
        plt.figure()
        plt.imshow(digits.images[i], cmap=plt.cm.gray_r, interpolation='nearest')
        plt.show()
        print(i)
        
        
#5  - find the best value of k
        
for i in range(1,50,1):
    knn = KNeighborsClassifier(n_neighbors=i)
    knn.fit(X_train, y_train)
    pred = knn.predict(X_test)
    print('Accuracy = ', metrics.accuracy_score(y_true = y_test, y_pred = pred))    

# 1 was my best average score    
        
        
#6       
x_unscaled = digits.data
X_train, X_test, y_train, y_test = train_test_split(x_unscaled, y, random_state=1, test_size=0.8)       
knn_unscaled = KNeighborsClassifier(n_neighbors=10)
knn_unscaled.fit(X_train, y_train)   
knn_pred_unscaled = knn_unscaled.predict(X_test)
print('Accuracy = ', metrics.accuracy_score(y_true = y_test, y_pred = knn_pred_unscaled))        

##############################################################################
##Part 2
##############################################################################  

def report(results, n_top=3):
    for i in range(1, n_top + 1):
        candidates = np.flatnonzero(results['rank_test_score'] == i)
        for candidate in candidates:
            print("Model with rank: {0}".format(i))
            print("Mean validation score: {0:.3f} (std: {1:.3f})"
                  .format(results['mean_test_score'][candidate],
                          results['std_test_score'][candidate]))
            print("Parameters: {0}".format(results['params'][candidate]))
            print("")

#2.1
data = pd.read_csv('/Users/derekolson/DerekOlson/CS6017/homework5/OnlineNewsPopularity/OnlineNewsPopularity.csv')
data.columns = data.columns.str.replace(' ', '')

df = data.drop(['shares', 'url', 'timedelta'], axis=1)

X = pd.DataFrame(df).to_numpy()

d = pd.DataFrame(data['shares']).to_numpy()
shares = pd.DataFrame(data['shares']).to_numpy()
median_shares = np.median(shares)
shares[shares <= median_shares] = 0
shares[shares > median_shares] = 1

#2.2
print(np.min(d)) 
print(np.max(d)) 


#min is 1, median is 1400, max is 843300

#2.3
X_train, X_test, y_train, y_test = train_test_split(X, shares.ravel(), random_state=1, test_size=0.3)
knn = KNeighborsClassifier()
params = {'n_neighbors': range(1,20)}
search = GridSearchCV(knn, params)
search.fit(X_train, y_train)
report(search.cv_results_)

#2.4
X_train, X_test, y_train, y_test = train_test_split(X, shares.ravel(), random_state=1, test_size=0.9)
svc = svm.SVC()
params = {'C': range(1,10)}
search = GridSearchCV(svc, params)
search.fit(X_train, y_train)
report(search.cv_results_)

#2.5
X_train, X_test, y_train, y_test = train_test_split(X, shares.ravel(), random_state=1, test_size=0.9)
decisionTree = DecisionTreeClassifier()
params = {'max_depth': range(1,101, 10),'min_samples_split': range(10,1001,100)}
search = GridSearchCV(decisionTree, params)
search.fit(X_train, y_train)
report(search.cv_results_)













       