#
# PROGRAM: Assign 7   
# PROGRAMMER: Samuel Piecz 
# LOGON ID: Z1732715 
# DATE DUE: 11/09/17 
#
# Compiler variables
CCFLAGS = -ansi -Wall -std=c++11

# Rule to link object code files to create executable file
assign7: assign7.o
	g++ $(CCFLAGS) -o assign7 assign7.o

# Rule to compile source code file to object code
assign7.o: assign7.cpp
	g++ $(CCFLAGS) -c assign7.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o assign7
