import os


th1 = 0
th2 = 0
if os.path.isfile(".thetas.txt") :
	file = open(".thetas.txt", "r")
	line = file.readline().split()
	file.close()
	if (len(line) > 1) :
		th1 = float(line[0])
		th2 = float(line[1])

mileage = input("Please enter a mileage to predict the price : ")
while (mileage != "quit") :
	try :
		result = th1 + (int(mileage) * th2)
		print (result)
	except ValueError :
		print("Oops!  That was no valid number.  Try again...")
	mileage = input("Please enter a mileage to predict the price : ")