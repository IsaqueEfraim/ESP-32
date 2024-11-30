import numpy as np
def criar_matriz():
   x=0
   matriz= []
   for i in range(8):
        linha = []
        for j in range(8):
            x=x+0.1
            linha += [1+x]
        matriz += [linha]
   return matriz
def criar_matriz2():
   matriz= []
   x=6.4
   for i in range(8):
        linha = []
        for j in range(8):
            x=x+0.1
            linha += [5+x]
        matriz += [linha]
   return matriz
matrizA=criar_matriz()
matrizB=criar_matriz2()
print(matrizA)
print(matrizB)    
matrizC=np.matmul(matrizA,matrizB)
print(matrizC)

