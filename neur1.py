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


numTag=1   
hidden_node=3 
records = pd.read_csv(url,encoding='utf-8')
print(records.shape) # (4, 4)

inputD=records.iloc[0:records.shape[0],0:records.shape[1]-numTag].values
print(inputD.shape) # (4, 3)

targetD=records.iloc[:,list(records.shape[1]-np.arange(numTag,0,-1))].values
print(targetD.shape) # (4, 3)
print(inputD)
print(targetD)