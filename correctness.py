#!/usr/bin/python
""" ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** correctness.py
** Uses the C implementation of Qhull to check if two convex hulls are equal.
** Exposes two methods: getQhull(str) and checkCH([int], [int]). 
** The first computes the convex hull from the filepath given as argument, and
** the last compares the two convex hulls given as argument
**
** If executed as is, all .txt files in the directory data/ would be compared
** to the corresponding files in output/, generated after running the binary
** file ./main arg1 arg2 arg3, where arg1 is an integer between 1 and 4
** stating which algorithm to be executed, arg2 is the path to a file in data/
** and arg3 is the path to a file in output/, e.g
**
**            ./main 1 data/input.txt output/INC_CH-input.txt
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------
"""

import subprocess # Run our implementation
from collections import deque # Check if order is correct
try:
	from pyhull.convex_hull import ConvexHull
except ImportError:
	raise ImportError("Install pyhull (http://pythonhosted.org/pyhull/#stable-version)")

def getQhull(infile):
	""" 
	Returns the convex hull in clockwise order using the same format as
	requried by the assignment, i.e. one label pr. vertex indexed from 1
	
	This method uses pyhull (which is are wrapper for qhull) to verify 
	the result from our implementations.
	
	Args:
		infile (str): Path to the input file
	"""
	with open(infile, 'r') as f:
		num_lines = sum(1 for line in open(infile))
		if num_lines >= 1000000:
			return [], num_lines
		# Read the points
		tmp = [line.split(' ') for line in f]
		# Convert them to floats
		points = [[float(x.rstrip()), float(y.rstrip())] for x, y in tmp]

		# Calculate the convex hull
		d = ConvexHull(points, False)
		# The output is in couter-clockwise order and 0 indexed, so we need to
		# reverse the output and order them
		ch = [d.vertices[0][1] + 1, d.vertices[0][0] + 1]
		while len(ch) < len(d.vertices):
			# Order the vertices in clockwise order
			# And only use one label pr. edge
			prev = ch[-1] - 1
			for v in d.vertices:
				if v[1] == prev:
					ch.append(v[0] + 1)
					break
	return ch, len(points)

def getCH(fn):
	outfile = "output/correctness.txt"
	subprocess.call(["./main", "1", fn, outfile])
	# Read the result
	with open(outfile, 'rb') as f:
		current = [int(x.rstrip()) for x in f]
	return current
	
def checkCH(qhull, adv, alg = "", verbose = True):
	"""
	Checks if the convex hull adversary convex hull (adv) equals the correct
	convex hull computed with Qhull. The following checks are executed:
		1. The length of both convex hulls should be equal
		2. No duplicate label must be present
		3. Both convex hull should contain the same elements
		4. The convex hull should be represented in clock-wise order
	Note that only the first error is returned.
	
	args:
		qhull   ([int]): The convex hull returned from the method getQhull
		adv     ([int]): The convex hull that should be compared to qhull
		alg     (str)  : A string representation of the adversary
		verbose (bool) : True if this message should print, False otherwise
	return:
		(bool, str)    : A tuple that indicates if the convex hulls are equal
		                 and the error message given.
	"""
	status = ""
	passed = True
	
	if len(adv) != len(qhull):
		# Convex hull size should be of equal length
		passed = False
		status += "   Size of CH incorrect\n"
		status += "   Expected: " + str(len(qhull)) + "\n"
		status += "   Got:      " + str(len(adv)) + "\n"
	elif len(set(adv)) != len(adv):
		# A label can only occur once in a convex hull
		seen = set()
		passed = False
		status += "   Labels can only occur once in the CH\n"
		status += "   Duplicates: " + str([x for x in adv if x not in seen and not seen.add(x)]) + "\n"
	elif sorted(adv) != sorted(qhull):
		# Check if it contains the correct elements
		setQhull = set(qhull)
		passed = False
		status += "   Incorret labels in CH\n"
		status += "   Wrong labels: " + str([x for x in adv if x not in setQhull]) + "\n"
	else:
		# Check if the order is correct
		deq = deque(adv)
		# Rotate the adversary, such that they both 
		# start with the same label
		deq.rotate(-adv.index(qhull[0]))
		if list(deq) != qhull:
			passed = False
			status += "   The order of the convex hull is incorrect!\n"
	
	if verbose:
		# Print if needed
		print alg + "\t", "         " + str(passed)
		if not passed:
			print status
	# We now know if the adversary passed or not (and why)
	return passed, status

if __name__ == '__main__':
	import os # Listing files to run
	
	allPassed = True
	# Define what we want to check correctness on
	algs = ["INC_CH", "DC_CH", "MbC_CH", "MbC2_CH"]
	inputfiles = [x for x in os.listdir("data/") if x.endswith(".txt")]

	for infile in inputfiles:
		tooBig = False
		datafile = "data/" + infile

		
		# Print what we are doing
		status = "========== RUNNING ON FILE " + infile + " =========="
		print "="*len(status)
		print status
		print "="*len(status)
		
		# Compute the correct convex hull
		qhull, numPoints = getQhull(datafile)
		if qhull == []:
			tooBig = True
			print "Data size too big for Qhull. Using: " + algs[0] + " instead"
			qhull = getCH(datafile)
		print "Data size: " + str(numPoints) + " Convex Hull size: " + str(len(qhull)), "\n"
		
		print "Alg\t        Passed"
		print "----------------------"
		for alg in xrange(len(algs)):
			if tooBig and alg == 0:
				continue
			# Compute the convex hull for each algorithm
			# and place their output in the output-directory
			outfile = "output/" + algs[alg] + "-" + infile
			subprocess.call(["./main", str((alg + 1)), datafile, outfile])
			# Read the result
			with open(outfile, 'rb') as f:
				current = [int(x.rstrip()) for x in f]
			# Check if it is correct
			res, status = checkCH(qhull, current, algs[alg])
			allPassed &= res
	# Finally: Print if all passed
	status = "========== All test passed: " + str(allPassed) + " =========="
	print "="*len(status)
	print status
	print "="*len(status), "\n"

