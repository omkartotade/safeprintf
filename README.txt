CSE-545 - Software Security - Project - Format Strings Vulnerabilities Prevention- 

File provided-
safeprintf.c - Our overloaded library with the printf family of functions
testcase1.c - This is the first of three test cases.
testcase2.c - This is the second of three test cases.
testcase3.c - This is the third of three test cases.

Keep all the above files in the same directory.


Instructions on compiling the files-

1. Compile the  safeprintf library by running the command-

gcc -w -Wall -fPIC -shared -o safeprintf.so safeprintf.c -ldl


safeprintf.so file will be generated in the same directory.

2. Now export the .so file using the command- 

export LD_PRELOAD=./safeprintf.so


3. You can now run any test.c file by compiling it and running it using the command-

./test

The test file will be run using our overloaded family of 'printf' functions.

To unset LD_PRELOAD, use the command-

unset LD_PRELOAD