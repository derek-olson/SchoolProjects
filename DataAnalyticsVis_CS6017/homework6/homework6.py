#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jul 11 16:55:49 2020

@author: derekolson
"""

import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split
import torchvision
import torch
import torchvision.transforms as transforms
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

arial = pd.read_csv('/Users/derekolson/DerekOlson/CS6017/homework6/fonts/Arial.csv')
times = pd.read_csv('/Users/derekolson/DerekOlson/CS6017/homework6/fonts/TIMES.csv')
df = arial.drop(['font', 'fontVariant', 'strength', 'italic', 'orientation', 'm_top', 'm_left', 'originalH', 'originalW', 'h', 'w'], axis=1)
d = df.loc[:, df.columns != 'm_label']
reshaped = d.to_numpy().reshape(-1,20,20)
plt.imshow(reshaped[2,:,:])

reshaped = reshaped.astype('float64')
reshaped *= (1.0/reshaped.max())

y = df.loc[:, df.columns == 'm_label'].to_numpy()

y_unq = np.unique(y)

labels = {}
for i in range(len(y_unq)):
    labels[i] = y_unq[i]

def get_key(val, d): 
    for key, value in d.items(): 
         if val == value: 
             return key 
         
y_labels = []            
for i in range(0, len(y), 1):
    y_labels.append(get_key(y[i], labels))
    
X_train, X_test, y_train, y_test = train_test_split(reshaped, y_labels, random_state=1, test_size=0.8)    


class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        c1Out = 32 # convoluation layer 1 will output 6 "images": one for each filter it trains
        c2Out = 32 # similarly for the 2nd convolution layer
        self.conv1 = nn.Conv2d(1, c1Out, 5) #1-D input, c1Out outputs, filter size 3x3 pixels
        
        # (28-2)*(28 -2)*c1Out outputs
        
        self.pool = nn.MaxPool2d(2, 2) #downsample 2x2 blocks to 1 value
        
        # 13*13*c1Out
        
        self.conv2 = nn.Conv2d(c1Out, c2Out, 5) #inputs comes from conv1 , specify our #outputs, use 3x3 blocks again
        
        # (8-4)*(8-4)*c2Out
        # pool again
        # (11/2)*(11/2)*c2Out = 5*5*c2Out
        
        #this is tricky.  The convolutions each shave 1 pixel off around the border, and then the
        #max pools reduce the number of pixels by 4
        self.pooledOutputSize = c2Out*2*2 # 16 outputs per image whose size has been reduced
        self.fc1 = nn.Linear(self.pooledOutputSize, 3200)
        self.fc2 = nn.Linear(3200, len(y_unq))
        #self.fc3 = nn.Linear(84, 10)


    def forward(self, x): # "batch" of images
        #x is 4D tensor:  (batch size, width, height, #channels (1, grayscale image))
        #after conv1:  (batch size, width adjusted, height adjusted, conv1 # outputs)
        #after max pool: (batch size, width/2, height/2, conv1 # outputs)
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        #split into 2 lines above
        #x = self.pool(F.relu(self.conv1(x)))  #apply convolution filter, then run it through relu activation function
        #x = self.pool(F.relu(self.conv2(x))) #ditto
        #print(x.shape) #uncomment to see the size of this layer.  It helped me figure out what pooledOutputSize shoudl be

        #turn the 5x5xc2Out array into a single 1xN array.  The dense layers expect a 1D thing
        x = x.view(-1, self.num_flat_features(x))
        # x.view(batch_size( x.shape[0]) , -1)
        x = F.relu(self.fc1(x)) #apply dense layer 1
        #x = F.relu(self.fc2(x)) #and dense layer 2, using ReLU activation
        x = self.fc2(x) #final dense layer.  No activation function on this
        return x
    
    #compute the output size after our convolution layers
    def num_flat_features(self, x):
        size = x.size()[1:]  # all dimensions except the batch dimension
        num_features = 1
        for s in size:
            num_features *= s
        return num_features


net = Net()

xy_train = []
for i in range(0, len(X_train), 1):
    xy_train.append((X_train[i], y_train[i]))
    
xy_test = []
for i in range(0, len(X_test), 1):
    xy_test.append((X_test[i], y_test[i]))

def train(model, epochs):
    criterion = nn.CrossEntropyLoss() #this is a way of measuring error for classification that takes the
    #"confidence" of a prediction into account.  High confidence, correct predictions are low cost, 
    #high confidence, wrong predictions are high cost, medium confidence predictions have cost

    #use the ADAM optimizer to find the best weights
    optimizer = optim.Adam(model.parameters(), lr= 1e-4) 
    
    #this loads data and gets it in the right format for us
    trainloader = torch.utils.data.DataLoader(xy_train, batch_size=8,
                                              shuffle=True, num_workers=0)

    for epoch in range(epochs):  # loop over the dataset multiple times

        running_loss = 0.0
        for i, data in enumerate(trainloader, 0):
            # get the inputs; data is a list of [inputs, labels]

            inputs, labels = data
            inputs = inputs.reshape((-1,1,20,20))
            # zero the parameter gradients
            optimizer.zero_grad()

            # forward + backward + optimize
            outputs = model(inputs.float()) #predict the output with some training data
            loss = criterion(outputs, labels) #see how well we did
            loss.backward() #see how to change the weights to do better
            optimizer.step() #and actually change the weights

            # print statistics
            running_loss += loss.item()
            if i % 2000 == 1999:    # print every 2000 mini-batches
                print('[%d, %5d] loss: %.3f' %
                      (epoch + 1, i + 1, running_loss / 2000))
                running_loss = 0.0

    print('Finished Training')

def evaluate(model):  
    #load some test data
    testloader = torch.utils.data.DataLoader(xy_test, batch_size=8,
                                                shuffle=True, num_workers=0)
    correct = 0
    total = 0
    to_return = []
    with torch.no_grad():
        for data in testloader:
            images, labels = data
            images = images.reshape((-1,1,20,20))
            outputs = model(images.float())
            _, predicted = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
            bools = predicted == labels
            for i in range(len(bools)):
                if bools[i] == False:
                    print(predicted[i])
                    to_return.append(predicted[i].item())

    #just do a coarse evaluation... how many did we predict correcly?
    print('Accuracy of the network on the 10000 test images: %d %%' % (
        100 * correct / total))
    return to_return
    
train(net, 4)
test = evaluate(net)
