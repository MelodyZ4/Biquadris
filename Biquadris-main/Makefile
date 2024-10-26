CXX=g++ 
CXXFLAGS=-std=c++20 -Wall -O -g -MMD -Werror=vla # use -MMD to generate dependencies
LIBFLAGS=-L/usr/lib/x86_64-linux-gnu/ -lboost_program_options -L/usr/X11R6/lib -lX11
SOURCES=$(wildcard *.cc)   # list of all .cc files in the current directory
OBJECTS=${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=biquadris

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(LIBFLAGS)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) -I/usr/include/boost/

-include ${DEPENDS}

.PHONY: clean

clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
