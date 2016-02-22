# GNU C/C++ compiler and linker:
LINK = g++

# COMPILER OPTIONS:

CFLAGS = -c  -g -O0
CXXFLAGS = $(CFLAGS) -std=c++11 -Wall

#OBJECT FILES
OBJS = src/ANNtest.o src/ANNtrain.o src/CrossValidate.o src/Prm.o

#OBJECT FILES FOR TEST PROGRAMS
TESTS = tst/testPrm.o

#HEADER FILES
HEAD = inc/main.h

#EXECUTABLES
EXECS = ANNtest ANNtrain CrossValidate

#TEST
TST = testPRM

all: ANNtest ANNtrain CrossValidate

tests: ${TST}

testPRM: tst/testPrm.o src/Prm.o
	${LINK} -o $@ $^
ANNtest: src/ANNtest.o src/Prm.o
	${LINK} -o $@ $^
ANNtrain: src/ANNtrain.o src/Prm.o
	${LINK} -o $@ $^
CrossValidate: src/CrossValidate.o
	${LINK} -o $@ $^
doxygen:
	doxygen doc/doxy.conf 
dox:
	doxygen doc/doxy.conf 
clean:
	rm -f *.o ${TST} *~ core src/*.o inc/*~ src/*~ $(EXECS) *~ prm/testWriter.prm
realclean:
	rm -f *.o ANNtest ANNtrain CrossValidate *~ core src/*.o inc/*~ src/*~ $(EXECS) *~ *.swp
edit:
	gedit inc/*.h src/*.cpp Makefile &
sublime:
	sublime-text inc/*.h src/*.cpp Makefile &
