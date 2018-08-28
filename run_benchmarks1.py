#! /usr/bin/env python3

# Katherine Hecht, Julia Hughes, Richard Stefanik
import os
import subprocess
import time

BACKENDS = ["unsorted", "sorted", "bst", "rbtree", "treap"]
NITEMS = [10, 100, 1000]
#NITEMS = [10, 100, 1000, 10000, 100000, 1000000, 10000000]
PADLENGTH = [1, 2, 4, 8]

oFile = open("table1.txt", "w")

head = "| Backend     | NITEMS    | PADLENGTH | Insert Time   | Search Time   |"
blank = "|-------------|-----------|-----------|---------------|---------------|"
print(head)
print(blank)
oFile.write(head + "\n")
oFile.write(blank + "\n")

for b in BACKENDS:
	for n in NITEMS:
		for p in PADLENGTH:
			
			command = "./map_bench -b " + b + " -n " + str(n) + " -p " + str(p) 
			output = os.popen(command).read().splitlines()
			iTime = output[0][8:]
			sTime = output[1][8:]
			'''
			start_time = time.time();
			h = subprocess.check_output(["./map_bench", "-b", b, "-n", str(n), "-p", str(p)])
			while (time.time() - start_time) < 5:
				print("Still Working")
				time.sleep(1)
				if not h.poll() is None:
					break
			print("Hi " + h.decode())
			'''
			oString = "|{:13}|{:>11}|{:>11}|{:>15}|{:>15}|".format(b.upper(), str(n), str(p), iTime, sTime)
			print(oString)
			oFile.write(oString + "\n")
oFile.close()
