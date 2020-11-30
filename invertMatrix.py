import numpy as np
input = []
with open('./diffusion-matrix.txt') as f:
    for line in f:
        input.append(line)
f.close()

for i in range(len(input)):
    newLine=[]
    for j in range(len(input[i])-1):
            newLine.append(int(input[i][j]))
    input[i]=newLine

input=np.array(input)
inverted=np.linalg.inv(input)
inverted[abs(inverted)>.5]=1
inverted[abs(inverted)<=.5]=0
for row in inverted:
    print(row)
with open("./invertedMatrix.txt", "w") as f:
    for row in range(len(inverted)):
        for col in range(len(inverted[row])):
            f.write(str(inverted[row, col].astype(int)))

        f.write(str("\n"))
f.close()