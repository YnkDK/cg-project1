#!/usr/bin/python
""" ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
** 
** lines.py
** usage: lines.py [-h] -n N [-l L] [--scale SCALE] [-o filename] [--seed SEED]
** 
** Generates L lines each containing N/L points
** 
** optional arguments:
**   -h, --help            show this help message and exit
**   -n N                  The number of points to be generated
**   -l L                  Number of lines generated
**   --scale SCALE         A scale multiplied on the slope and the intersection
**                         of the y-axis
**   -o filename, --output filename
**                         The output file (use default)
**   --seed SEED           Integer seed for the PRNG (default current timestamp)
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
	parser = argparse.ArgumentParser(description='Generates L lines each containing N/L points')
	parser.add_argument("-n",
		type = int,
		help = "The number of points to be generated",
		required = True,
		metavar = "N"
	)
	parser.add_argument("-l",
		type = int,
		help = "Number of lines generated",
		default = 5
	)
	parser.add_argument("--scale",
		type = float,
		help = "A scale multiplied on the slope and the intersection of the y-axis",
		default = -10.0
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
		args.output = "../data/lines-n" + str(args.n) + "-l" + str(args.l) + "-scale" + str(args.scale) + "-s" + str(args.seed) + ".txt"

	if os.path.isfile(args.output):
		print "Output file already exists. Skipping file."
		sys.exit(0)
	rand = random.uniform
	scale = Decimal(args.scale)
	l = args.l
	n = args.n

	rand = random.uniform
	# Write to output file
	with open(args.output, 'wb') as f:		
		for i in xrange(l):
			a = Decimal(rand(-1, 1)) * scale
			b = Decimal(rand(-1, 1)) * scale
			for j in xrange(n/l):
				x = Decimal(rand(-1, 1) * (i + 1))
				y = Decimal(a*x + b)
				f.write("{:.15f} {:.15f}\n".format(x, y))
			print ".",
			sys.stdout.flush()
