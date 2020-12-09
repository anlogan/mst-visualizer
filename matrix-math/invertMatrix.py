import numpy as np
import LinearAlgebraPurePython as la
input = []

filename = "./test-matrix.txt"
with open(filename) as f:
    for line in f:
        input.append(line)
f.close()

for i in range(len(input)):
    newLine=[]
    for j in range(len(input[i])-1):
        newLine.append(int(input[i][j]))
    input[i]=newLine

# Copy matrix for future use
input2 = input
input=np.array(input)
print("Input np.array")
print(np.array(input).tolist())
print()

# Invert the matrix
inverted=np.linalg.inv(input)

# Convert the inverted np.array matrix to have abs values, 
# because at some point I saw -1's in a matrix I think
for row in range(len(inverted)):
    for col in range(len(inverted[row])):
        inverted[row, col] = abs(inverted[row, col])%2
"""
for row in range(len(inverted)):
    for col in range(len(inverted[row])):
        temp = abs(inverted[row,col])
        if ((temp > .5) and (temp <= 1.5)):
            inverted[row, col] = 1 
        else:
            inverted[row, col] = 0
"""

inverted2 = np.array(inverted).tolist()
for row in range(len(inverted2)):
    for col in range(len(inverted2[row])):
        inverted[row, col] = int(inverted[row, col])

print("Input Matrix")
la.print_matrix(input2)
print("Inverted Matrix")
la.print_matrix(inverted2)
I = la.identity_matrix(32)

print("Product of input and inverse, should be I")
la.print_matrix(la.matrix_multiply(inverted2, input2))

with open("./invertedMatrix.txt", "w") as f:
    for row in range(len(inverted)):
        for col in range(len(inverted[row])):
            f.write(str(inverted[row, col].astype(int)))

        f.write(str("\n"))
f.close()
