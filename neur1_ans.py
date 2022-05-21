# neural1.py
import csv
import numpy as np
import pandas as pd
import numpy as np

url = "https://raw.githubusercontent.com/husthorng/hello-world/neural/trainingdata.csv"

def nonlin(x,deriv=False):
    A=1/(1+np.exp(-x))
    if(deriv==True):
        return (A*(1-A))
    return A

#print(nonlin(0,False))
#print(nonlin(0,True))

numTag=1   
hidden_node=3 
records = pd.read_csv(url,encoding='utf-8')
#print(records.shape) 

inputD=records.iloc[0:records.shape[0],0:records.shape[1]-numTag].values
#print(inputD.shape) 

targetD=records.iloc[:,list(records.shape[1]-np.arange(numTag,0,-1))].values
#print(targetD.shape) 

print(inputD)

#print(targetD)

print(records.values)

print(records.values[1]) #[0 1 1 0]

print(records.values[1][2]) #1

print(inputD.shape[1])
i=1
while i <= inputD.shape[0]:
    print(inputD[i-1,:])
    i +=1
print(inputD.shape)

TranD=np.zeros((3,4))
for y in range (inputD.shape[1]):
    for x in range(inputD.shape[0]):
        TranD[y,x]=inputD[x,y]

# print(TranD)

i=1
while i <= inputD.shape[1]:
    print(inputD[:,i-1])
    i+=1

print(inputD.T)