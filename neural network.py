import csv
import numpy as np
import pandas as pd
url = "https://raw.githubusercontent.com/husthorng/hello-world/neural/trainingdata.csv"
import numpy as np
def nonlin(x,deriv=False):
    A=1/(1+np.exp(-x))
    if(deriv==True):
        return (A*(1-A))
    return A
# print(nonlin(0,1))

numTag=1   #
hidden_node=3 

records = pd.read_csv(url,encoding='utf-8')
#print(records.shape)
inputD=records.iloc[0:records.shape[0],0:records.shape[1]-numTag].values
#print(inputD.shape)
tagetD=records.iloc[:,list(records.shape[1]-np.arange(numTag,0,-1))].values
print(inputD)
print(tagetD)
np.random.seed(1)
syn0=2*np.random.random((inputD.shape[1],hidden_node))-1
syn1=2*np.random.random((hidden_node,numTag))-1
# print(syn0)
# print(syn1)
for j in range(1200):
    X=inputD
    L0=nonlin(np.dot(inputD,syn0))
    L1=nonlin(np.dot(L0,syn1))
    #print(L1)
    L1_error=tagetD-L1
    if(j % 10)==0:
        print("Error"+str(np.mean(np.abs(L1_error))))    
    #print(L1_error)
    L1_delta=L1_error*nonlin(L1,deriv=True)
    #print(L1_delta)
    L0_error=L1_delta.dot(syn1.T)
    L0_delta=L0_error*nonlin(L0,deriv=True)
    syn1 += L0.T.dot(L1_delta)
    syn0 += inputD.T.dot(L0_delta)
print("output after Training:")
# np.savetxt("syn0.csv", syn0, delimiter=",")
# np.savetxt("syn1.csv", syn1, delimiter=",")
#print(syn0)
df = pd.DataFrame(syn0)   
df.to_csv("syn0.csv")
df = pd.DataFrame(syn1)   
df.to_csv("syn1.csv")
print(L1)
print(syn0)
print(syn1)
