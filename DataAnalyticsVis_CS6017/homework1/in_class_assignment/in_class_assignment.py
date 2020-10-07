#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jun 11 10:39:00 2020

@author: derekolson
"""

import pandas as pd
import seaborn as sns
import sklearn.feature_selection as fs
colname = ['variance', 'skewness', 'kurtosis', 'entropy', 'class']
data = pd.read_csv('/Users/derekolson/Downloads/data_banknote_authentication.csv', names =colname)
sns.pairplot(data, hue='class')

X = data[['variance', 'skewness', 'kurtosis', 'entropy']]
y = data['class']


fs.f_classif(X, y)




from sklearn.ensemble import RandomForestClassifier
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn import metrics
from sklearn.metrics import confusion_matrix

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3)
clf=RandomForestClassifier(n_estimators=100)
clf.fit(X_train,y_train)
y_pred=clf.predict(X_test)
print("Random Forest Accuracy:",metrics.accuracy_score(y_test, y_pred))

from sklearn.model_selection import cross_val_score, cross_val_predict, cross_val_score, KFold
from sklearn import svm
from sklearn.model_selection import ShuffleSplit

n_samples = X.shape[0]
cv = ShuffleSplit(n_splits=5, test_size=0.3, random_state=0)
svc = svm.SVC(kernel='rbf')
scores = cross_val_score(svc, X, y, cv=cv)
scores
svc.fit(X,y)

predicted = cross_val_predict(estimator=svc, X=X, y=y)

y_pred = svc.predict(X)

test = pd.Series(predicted)

print('Accuracy = ', metrics.accuracy_score(y_true = y, y_pred = y_pred))
