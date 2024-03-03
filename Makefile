CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

all: llrec-test

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------

OBJS = llrec-test.o llrec.o

llrec-test: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)


clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 