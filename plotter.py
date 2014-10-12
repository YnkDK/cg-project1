#!/usr/bin/python
""" ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** inputGenerator.py
** usage: inputGenerator.py [-h] -s SHAPE -n N [-o filename] [-seed SEED] [-p]
**
** Generates N uniformly random points with a SHAPE
**
** optional arguments:
**  -h, --help            show this help message and exit
**  -s SHAPE, --shape SHAPE
**                        Specifies the shape
**  -n N                  The number of points to be generated
**  -o filename, --output filename
**                        The output file (use default)
**  -seed SEED            Integer seed for the PRNG (default current timestamp)
**  -p, --plot            If given a plot of the data is created
**
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------
"""
import argparse
import matplotlib.pyplot as plt
def parseArgs():
	""" Parses command-line args
	"""
	parser = argparse.ArgumentParser(description='Plots raw input file and optional combines it with an output file (Convex Hull)')
	parser.add_argument("-i", "--input", 
		type = str,
		help = "The input-file coordinates",
		required = True,
		metavar = "input.txt"
	)
	parser.add_argument("-c", "--convexHull",
		type = str,
		help = "A list of labels, which defines the convex hull",
		required = False,
		metavar = "output.txt"
	)
	
	return parser.parse_args()

def readInput(filepath):
	x = []
	y = []
	
	xa = x.append
	ya = y.append
	with open(filepath, 'rb') as f:
		for line in f:
			s = line.split(" ")
			xa(float(s[0]))
			ya(float(s[1]))
	return x,y
	
def readLabels(filepath):
	labels = []
	app = labels.append
	with open(filepath, 'rb') as f:
		for line in f:
			app(int(line) - 1)
	return labels

if __name__ == "__main__":
	# Parse args
	args = parseArgs()
	xs, ys = readInput(args.input)
	if args.convexHull is not None:
		dist = 0.0
		labels = readLabels(args.convexHull)
		for i in range(1,len(labels)):
			x1 = xs[labels[i-1]]
			y1 = ys[labels[i-1]]
			
			x2 = xs[labels[i]]
			y2 = ys[labels[i]]
			
			plt.plot([x1, x2], [y1, y2], 'k-')
		# Connect first and last point
		x1 = xs[labels[0]]
		y1 = ys[labels[0]]
		
		x2 = xs[labels[-1]]
		y2 = ys[labels[-1]]

		plt.plot([x1, x2], [y1, y2], 'k-')
		
		# Remove the points from xs and ys
		l = sorted(labels)
		tmpx = []
		tmpy = []
		for i in xrange(len(xs)):
			if len(l) > 0 and i == l[0]:
				del l[0]
				plt.plot(xs[i], ys[i], "o", color = 'r')
				continue
			tmpx.append(xs[i])
			tmpy.append(ys[i])
		xs = tmpx
		ys = tmpy
	plt.scatter(xs, ys)
	plt.show()	
