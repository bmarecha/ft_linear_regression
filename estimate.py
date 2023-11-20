import os

def readThetas (filename:str) -> tuple:
	if not os.path.isfile(filename) :
			print("Missing file :" + filename)
			print("Initialising to 0.")
			return (0, 0)
	file = open(filename, "r")
	line = file.readline().split()
	file.close()
	if (len(line) <= 1) :
		print("Needs two floats.")
		exit(1)
	return (float(line[0]), float(line[1]))
	

def main () :
	th1, th2 = readThetas(".thetas.txt")
	try :
		mileage = input("Please enter a mileage to predict the price : ")
		while (mileage != "quit") :
			if (mileage < 0):
				print("Oops! Try to be more positive this time !")
			else :
				try :
					result = th1 + (int(mileage) * th2)
					print (result if result > 0 else 0)
				except ValueError :
					print("Oops!  That was no valid number.  Try again...")
			mileage = input("Please enter a mileage to predict the price : ")
	except EOFError :
		pass


if __name__ == '__main__':
	main()