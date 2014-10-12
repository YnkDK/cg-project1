Computational Geometry (Fall 2014) - Project 1 (Convex Hull)
============================================================

This software is implemented as part of the course Computational Geometry 
(Fall 2014) at Aarhus Univerity Denmark. 

Author: Martin Storgaard and Konstantinos Mampentzidis

To create an executable for running either convex hull algorithm use: make main
Afterwards execute ./main [alg] [inputFile] [outputFile], where [alg] is a number
between 1 and 4:
1: Incremental CH
2: Divide-and-Conquer CH
3: MbC without extra pruning
4: MbC with extra pruning
and [inputFile] and [outputFile] are paths to the input file and output file respectively.

To generate the test cases used in our report, simply use make tests (Warning: This might take
approximatly 20 hours). 

When all tests cases are created, one can run performance benchmark using make perf, and then
execute ./perf

To compare the output with qhull, simply runn ./correctness.py - this script compares all input
data located in data/

To generate other shapes, see python generators/[shape].py -h, where shape is either, circle
curve, lines, square or triangle.
