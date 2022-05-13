import csv
import numpy as np
import pandas as pd
url = "https://raw.githubusercontent.com/husthorng/hello-world/horng_1/N_Q.csv"
# https://www.symbolab.com/solver/step-by-step/%5Cfrac%7B1%7D%7B1%2Be%5E%7B-x%7D%7D?or=input
# N_Q1 (自動儲存).csv
def nonlin(x,deriv=False):
    A=1/(1+np.exp(-x))
    if(deriv==True):
        return (A*(1-A))
    return A

SSE_Goal=10  
maxcycles=1
numTag=2   #
hidden_node=6 
lr=0.001
records = pd.read_csv(url,encoding='utf-8')
# print(records.shape)
inputD=records.iloc[0:records.shape[0],0:records.shape[1]-numTag].values 
#print(inputD)              # [234.0 0.34 115 0.37]
#print(inputD.shape[1])
targetD=records.iloc[:,list(records.shape[1]-np.arange(numTag,0,-1))].values 
#print(targetD)             # [47.4  943.35]
#print(targetD.shape[1])
max_min_l=np.array([list(np.max(inputD,axis=0)),list(np.min(inputD,axis=0))]) 
#print(list(np.max(inputD,axis=0)))       #[360.0,  0.5, 128.0,  0.55]
#print(list(np.min(inputD,axis=0)))       #[180.0,  0.3,  64.0,  0.35]
#print(max_min_l[0]-max_min_l[1])         #[180.    0.2   64.    0.2]
#print(max_min_l[0]*1.1-max_min_l[1]*0.9) #[234.    0.28  83.2   0.29]
#max_min_l=np.array(list(max_min_l[0]*1.1),list(max_min_l[1]*0.9))
max_min_l=np.array([max_min_l[0]*1.1,max_min_l[1]*0.9])
inputD1=np.insert(inputD,0,max_min_l,axis=0)
ptp_inputD1=np.ptp(inputD1,axis=0)
inputD2=(inputD1 - np.min(inputD1,axis=0))/ptp_inputD1
inputD3=inputD2[2:,:]
#print("inputD3=\n",inputD3)
#df = pd.DataFrame(inputD3)   
#df.to_csv("inputD3.csv")
#----------------------------------------------------------------------

max_min_T=np.array([list(np.max(targetD,axis=0)),list(np.min(targetD,axis=0))]) 
max_min_T=np.array([max_min_T[0]*1.1,max_min_T[1]*0.9])
#print(max_min_T)
targetD1=np.insert(targetD,0,max_min_T,axis=0)

ptp_targetD1=np.ptp(targetD1,axis=0)
targetD2=(targetD1 - np.min(targetD1,axis=0))/ptp_targetD1
targetD3=targetD2[2:,:]
#print("targetD3=\n",targetD3)
#df = pd.DataFrame(targetD3)  
#df.to_csv("targetD3.csv")

#print(max_min_T) #[55.4631   1095.56381 ] [28.609416  628.39251]]
#print(targetD-np.min(targetD,axis=0))
#Normalize_targetD=(targetD-max_min_T[1])/(max_min_T[0]-max_min_T[1])
#print(Normalize_targetD) #[[0.69958759 0.67419037]
#----------------------------------------------------------------------

W1=np.random.rand(hidden_node,inputD3.shape[1]+1)
W2=np.random.rand(targetD3.shape[1],hidden_node+1)
W1=np.array([[0.374787391,0.691357659,0.399163206,0.990448565,0.068752554],[0.514618454,0.686754758,0.006648895,0.537935165,0.855330561],[0.823627609,0.855415819,0.749353856,0.424677561,0.776407309],[0.05984558,0.332534196,0.072289026,0.990402407,0.683451114],[0.258627196,0.017661597,0.429075513,0.540333555,0.016104431],[0.080995571,0.871514494,0.592766433,0.418287037,0.741965155]])
W2=np.array([[0.434234336,0.201743691,0.565200915,0.708346399,0.385665891,0.815954239,0.687525437],[0.823950579,0.096605633,0.793742975,0.257843771,0.607604573,0.938180111,0.459160503]])
onex=np.ones(inputD3.shape[0],dtype=int)
#print(W2)
#print(W1.shape)
#print(W2.shape)
inputD3_1=np.insert(inputD3, 0, 1, axis=1)
#print(inputD3_1[0:5,:]) # [[1.         0.30769231 0.25       0.68990385 0.18965517]
#print(W1)
net_h=inputD3_1@W1.T
#print(net_h.shape)
out_h=nonlin(net_h,deriv=False)
#print(out_h)
out_H1=np.insert(out_h, 0, 1, axis=1)
#print(out_H1.shape)
net_o=out_H1@W2.T
print("W2.shape=",W2.shape)
print("net_o.shape=",net_o.shape)
out_o=nonlin(net_o,deriv=False)
er=targetD3-out_o
ersum=np.sum(er**2)
#print(er)
#print(ersum)

#df = pd.DataFrame(inputD1)   
#df.to_csv("inputD1.csv")

#df = pd.DataFrame(W1)   
#df.to_csv("W1.csv")
#df = pd.DataFrame(W2)   
#df.to_csv("W2.csv")
df = pd.DataFrame(er)   
df.to_csv("er.csv")
#df = pd.DataFrame(out_H1)   
#df.to_csv("out_H1.csv")
#df = pd.DataFrame(out_o)   
#df.to_csv("out_o.csv")
#df = pd.DataFrame(net_o)   
#df.to_csv("net_o.csv")
df = pd.DataFrame(targetD3)   
df.to_csv("targetD3.csv")

delta_o=out_o*(1-out_o)*er


df = pd.DataFrame(delta_o)   
df.to_csv("delta_o.csv")

ckdao=delta_o.T@out_H1

df = pd.DataFrame(ckdao)   
df.to_csv("ckdao.csv")

delta_W2=lr*delta_o.T@out_H1
#print(delta_W2.shape)
W2 = W2+delta_W2



if ersum < SSE_Goal :
    print("SSE_Goal > ersum")
#    break
else:
    print("ersum > SSE_Goal")



#print("delta2*er= \n",net_o*er)

#h2=np.insert(h1, 0, 1, axis=1)
#result2=h2@W2.T
#h2=nonlin(result2,deriv=False)

#print(h2)


#df = pd.DataFrame(Normalize_inputD)   
#df.to_csv("Normalize_inputD.csv")
#df = pd.DataFrame(Normalize_targetD)   
#df.to_csv("Normalize_targetD.csv")

