#!/usr/bin/python
""" ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**

** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------
"""
import argparse
import math
import random
import time
import sys
import os
from decimal import Decimal, getcontext

getcontext().prec = 50

def parseArgs():
	""" Parses command-line args
	"""
	parser = argparse.ArgumentParser(description='Generates N uniformly random points within a triangle. Convex hull size should be 3')
	parser.add_argument("-n",
		type = int,
		help = "The number of points to be generated",
		required = True,
		metavar = "N"
	)
	parser.add_argument("--xmin",
		type = float,
		help = "Smallest x-coordinate",
		default = -10.0
	)
	parser.add_argument("--xmax",
		type = float,
		help = "Largest x-coordinate",
		default = 10.0
	)
	parser.add_argument("--ymin",
		type = float,
		help = "Smallest y-coordinate",
		default = -10.0
	)
	parser.add_argument("--ymax",
		type = float,
		help = "Largest y-coordinate",
		default = 10.0
	)
	parser.add_argument("-o", "--output",
		type = str,
		help = "The output file (use default)",
		metavar = "filename"
	)
	parser.add_argument("--seed",
		type = int,
		help = "Integer seed for the PRNG (default current timestamp)",
		default = int(time.time())
	)
	return parser.parse_args()
	
if __name__ == "__main__":
	# Parse args
	args = parseArgs()
	# Update the random seed
	random.seed(args.seed)
	
	# Format output file name
	if args.output is None:
		args.output = "../data/triangle-n" + str(args.n) + "-xmin" + str(args.xmin) + "-xmax" + str(args.xmax) + "-ymin" + str(args.ymin) + "-ymax" + str(args.ymax) + "-s" + str(args.seed) + ".txt"
	if os.path.isfile(args.output):
		print "Output file already exists. Skipping file."
		sys.exit(0)
	xmin = args.xmin
	xmax = args.xmax
	ymin = args.ymin
	ymax = args.ymax
	rand = random.uniform
	
	# Pick the two cornor points (The third is origin)
	v1 = [Decimal(rand(xmin, xmax)), Decimal(rand(ymin, ymax))]
	v2 = [Decimal(rand(xmin, xmax)), Decimal(rand(ymin, ymax))]
	

	percentageMark = args.n/10

	with open(args.output, 'wb') as f:
		f.write("0.000000000000000 0.000000000000000\n")
		f.write("{:.15f} {:.15f}\n".format(v1[0], v1[1]))
		f.write("{:.15f} {:.15f}\n".format(v2[0], v2[1]))
		for i in xrange(args.n - 3):
			if i%percentageMark == 0:
				print ".",
				sys.stdout.flush()


			while True:
				a1 = Decimal(rand(0, 1))
				a2 = Decimal(rand(0, 1))
				if a1 + a2 < 1:
					break
			x = a1 * v1[0] + a2 * v2[0]
			y = a1 * v1[1] + a2 * v2[1]
			f.write("{:.15f} {:.15f}\n".format(x, y))
