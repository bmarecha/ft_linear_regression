import os
import matplotlib.pyplot as plt
import numpy as np


if not os.path.isfile("data.csv") :
	print("Please put data in 'data.csv'")
	exit(1)
file = open("data.csv", "r")
line = file.readline().split(",")
if (len(line) != 2) :
	print("The data needs two columns for a proper graph")
	exit(1)
xpoints = []
ypoints = []
#Need to test if first line really is axis name or first data
labels = line
line = file.readline()
while (line) :
	coord = line.split(",")
	xpoints.append(int(coord[0]))
	ypoints.append(int(coord[1]))
	line = file.readline()



th1 = 0
th2 = 0
if os.path.isfile(".thetas.txt") :
	file = open(".thetas.txt", "r")
	line = file.readline().split()
	file.close()
	if (len(line) > 1) :
		th1 = float(line[0])
		th2 = float(line[1])

x = np.arange(2, 250000, 4)
y = th1 + (th2 * x)
print(x)
print(y)
plt.plot(x, y)

plt.xlabel(labels[0])
plt.ylabel(labels[1])
plt.plot(xpoints, ypoints, 'o')
plt.show()