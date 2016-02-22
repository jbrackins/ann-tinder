# GNU C/C++ compiler and linker:
LINK = g++

# COMPILER OPTIONS:

CFLAGS = -c  -g -O0
CXXFLAGS = $(CFLAGS) -std=c++11 -Wall

#OBJECT FILES
OBJS = src/Prm.o src/Perceptron.o src/NeuralNet.o src/ANN.o


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
ANNtest: src/ANNtest.o ${OBJS}
	${LINK} -o $@ $^
ANNtrain: src/ANNtrain.o ${OBJS} 
	${LINK} -o $@ $^
CrossValidate: src/CrossValidate.o ${OBJS}
	${LINK} -o $@ $^
doxygen:
	doxygen doc/doxy.conf 
dox:
	doxygen doc/doxy.conf 
clean:
	rm -f *.o ${TST} *~ core src/*.o inc/*~ src/*~ $(EXECS) *~ prm/testWriter.prm
realclean:
	rm -f *.o ANNtest ANNtrain CrossValidate *~ core src/*.o inc/*~ src/*~ $(EXECS) *~ *.swp
	rm -rf doc/html doc/latex
edit:
	gedit inc/*.h src/*.cpp Makefile &
sublime:
	sublime-text inc/*.h src/*.cpp Makefile &
