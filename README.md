## Operating Systems Concepts: Programming Assignment C1

_data structures and pointers in the C language_ 
_Authors: Brian Sherer, Alex Jones, Logan Nagel, Anthony Ales_

* * * 

### Project Description

As specified by the project requirements this program sucessfully reads words from a file and sorts them using a binary tree. Each word that is read is inserted into the tree in its proper order before moving on to reading the next word in the file. When the end of the file is reached we pass our dynamically allocated binary tree into our displayInOrder() which traverses the tree and outputs the words and their counts in the specified format to a file that useses parsed characters from the input file's name to specify which input file it corresponds too. The program will do this for any number of input files passed in as arguments when running the executeable. Should the user happen to enter a file name that does not exist within the executable's directory, then "File Not Found" is printed to the console and the program exits. 

### Common issues

For most variables we attempted to dynamically allocate them in memory and use pointers to manipulate their values. Doing so resulted in several "segmentation Fault" errors and forced us to evaluate how certain variables and functions are being called and referenced as opposed to other programming languages we were more familiar with such as Java. 

Initally one of the most difficult issues for some members on our team was determining how to properly allocate the tree in memory so that it can be used throughout the program without causing a segmentation fault. 