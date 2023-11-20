import os
import matplotlib.pyplot as plt
import numpy as np
from estimate import readThetas

def readData (filename: str) -> tuple:
	if not os.path.isfile(filename) :
		print("Missing file :" + filename)
		exit(1)
	file = open(filename, "r")
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
	return (labels, xpoints, ypoints)

def main () :
	labels, xpoints, ypoints = readData("data.csv")
	th1, th2 = readThetas(".thetas.txt")

	x = np.arange(500, 250000, 4)
	y = th1 + (th2 * x)
	print(xpoints)
	print(ypoints)
	plt.plot(x, y)
	plt.ylim(0, max(ypoints) * 1.1)

	plt.xlabel(labels[0])
	plt.ylabel(labels[1])
	plt.plot(xpoints, ypoints, 'o')
	plt.show()

if __name__ == '__main__':
	main()