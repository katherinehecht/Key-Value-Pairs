#! /usr/bin/env python3

#Katherine Hecht, Julia Hughes, Richard Stefanik
import os
import time

titles = ["Beowulf", "Alice's Adventures in Wonderland", "The Jungle Book"]
fileNames = ["input_beowulf.txt", "input_wonderland.txt", "input_jungle.txt"]
BACKENDS = ["unsorted", "sorted", "bst", "rbtree", "treap"]

oFile = open("table2.txt", "w")

head =  "| Backend     | Text                               | File Size | Elasped Time  |"
blank = "|-------------|------------------------------------|-----------|---------------|"
print(head)
print(blank)
oFile.write(head + "\n")
oFile.write(blank + "\n")

for b in BACKENDS:
	for i, f in enumerate(fileNames):
			start_time = time.time()
			command = "./frequencies < " + f + " -b " + b
			output = os.popen(command).read()
			time_elapsed = "{:.8}".format(str((time.time() - start_time))) + " s"

			command = "ls -lh | grep " + f + " | cut -d \" \" -f 5 "
			fileSize = os.popen(command).read().rstrip()
			
			oString = "|{:13}|{:36}|{:>11}|{:>15}|".format(b.upper(), titles[i], str(fileSize), time_elapsed)
			print(oString)
			oFile.write(oString + "\n")
oFile.close()
