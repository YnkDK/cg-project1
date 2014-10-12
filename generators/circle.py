#!/usr/bin/python
""" ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** circle.py
** usage: circle.py [-h] -n N [--cx CX] [--cy CY] [--radius RADIUS] [-o filename]
**                  [-seed SEED]
** 
** Generates N uniformly random points within a circle
** 
** optional arguments:
**   -h, --help            show this help message and exit
**   -n N                  The number of points to be generated
**   --cx CX               X-coordinate of the center of the circle
**   --cy CY               Y-coordinate of the center of the circle
**   --radius RADIUS       Radius of the circle
**   -o filename, --output filename
**                         The output file (use default)
**   -seed SEED            Integer seed for the PRNG (default current timestamp)
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
	parser = argparse.ArgumentParser(description='Generates N uniformly random points within a circle')
	parser.add_argument("-n",
		type = int,
		help = "The number of points to be generated",
		required = True,
		metavar = "N"
	)
	parser.add_argument("--cx",
		type = float,
		help = "X-coordinate of the center of the circle",
		default = 0.0
	)
	parser.add_argument("--cy",
		type = float,
		help = "Y-coordinate of the center of the circle",
		default = 0.0
	)
	parser.add_argument("--radius",
		type = float,
		help = "Radius of the circle",
		default = 100.0
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
		args.output = "../data/circle-n" + str(args.n) + "-cx" + str(args.cx) + "-cy" + str(args.cy) + "-r" + str(args.radius) + "-s" + str(args.seed) + ".txt"
	if os.path.isfile(args.output):
		print "Output file already exists. Skipping file."
		sys.exit(0)
	cx = args.cx
	cy = args.cy
	radius = args.radius
	rand = random.random

	percentageMark = args.n/10

	with open(args.output, 'wb') as f:
		for i in xrange(args.n):
			if i%percentageMark == 0:
				print ".",
				sys.stdout.flush()
			a = 2*math.pi*rand()
			r = math.sqrt(rand())
			x = (radius*r) * math.cos(a) + cx
			y = (radius*r) * math.sin(a) + cy
			f.write("{:.15f} {:.15f}\n".format(x, y))
