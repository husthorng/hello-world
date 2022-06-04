import csv
import numpy as np
import pandas as pd

import numpy as np
def nonlin(x,deriv=False):
    A=1/(1+np.exp(-x))
    if(deriv==True):
        return (A*(1-A))
    return A
# print(nonlin(0,1))

url = "https://raw.githubusercontent.com/husthorng/hello-world/neural/syn0.csv"
syn0t=pd.read_csv(url,encoding='utf-8')
syn0=syn0t.values[0:,1:]
url = "https://raw.githubusercontent.com/husthorng/hello-world/neural/syn1.csv"
syn1t=pd.read_csv(url,encoding='utf-8')
syn1=syn1t.values[0:,1:]

numTag=syn1.shape[1]   #
hidden_node=syn0.shape[0]
url = "https://raw.githubusercontent.com/husthorng/hello-world/neural/trainingdata.csv"
records = pd.read_csv(url,encoding='utf-8')
inputD=records.iloc[0:records.shape[0],0:records.shape[1]-numTag].values
tagetD=records.iloc[:,list(records.shape[1]-np.arange(numTag,0,-1))].values
print("\n ============input data:=========== ")
print(inputD)
print("\n ============layer 0 weight:=======")
print(syn0)
print("\n=============layer 1 weight:=======")
print(syn1)
L0OT=nonlin(inputD.dot(syn0),False)
L1OT=nonlin(L0OT.dot(syn1),False)
df = pd.DataFrame(L1OT)
#df[df>0.5]=1
#df[df<0.5]=0
print("\n=======output value:=======")
print(df.values)