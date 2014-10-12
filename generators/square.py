#!/usr/bin/python
""" ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** usage: square.py [-h] -n N [--xmin XMIN] [--xmax XMAX] [--ymin YMIN]
**                  [--ymax YMAX] [-o filename] [--seed SEED]
** 
** Generates N uniformly random points within a square
** 
** optional arguments:
**   -h, --help            show this help message and exit
**   -n N                  The number of points to be generated
**   --xmin XMIN           Smallest x-coordinate
**   --xmax XMAX           Largest x-coordinate
**   --ymin YMIN           Smallest y-coordinate
**   --ymax YMAX           Largest y-coordinate
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

def parseArgs():
	""" Parses command-line args
	"""
	parser = argparse.ArgumentParser(description='Generates N uniformly random points within a square')
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
		args.output = "../data/square-n" + str(args.n) + "-xmin" + str(args.xmin) + "-xmax" + str(args.xmax) + "-ymin" + str(args.ymin) + "-ymax" + str(args.ymax) + "-s" + str(args.seed) + ".txt"
	if os.path.isfile(args.output):
		print "Output file already exists. Skipping file."
		sys.exit(0)
	xmin = args.xmin
	xmax = args.xmax
	ymin = args.ymin
	ymax = args.ymax
	rand = random.uniform

	percentageMark = args.n/10

	with open(args.output, 'wb') as f:
		for i in xrange(args.n):
			if i%percentageMark == 0:
				print ".",
				sys.stdout.flush()
			x = rand(xmin, xmax)
			y = rand(ymin, ymax)
			f.write("{:.15f} {:.15f}\n".format(x, y))
