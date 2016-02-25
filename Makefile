# GNU C/C++ compiler and linker:
LINK = g++ -pg

# COMPILER OPTIONS:

CFLAGS = -c  -g -O0
CXXFLAGS = $(CFLAGS) -std=c++11 -Wall -pg

#OBJECT FILES
OBJS = src/ANN.o src/NeuralNet.o src/Perceptron.o src/Prm.o src/ANN.o src/Csv.o src/Wts.o

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
	(cd ./doc/latex && make)
	cp ./doc/latex/refman.pdf Program_Writeup.pdf	
dox:
	make doxygen
clean:
	rm -f *.o ${TST} *~ core src/*.o inc/*~ src/*~ $(EXECS) *~ prm/testWriter.prm
#Hahaha I am a bad speller sometimes so let's add these for no reason:
clena:
	make clean
celan:
	make clean
realclean:
	rm -f *.o ANNtest ANNtrain CrossValidate *~ core src/*.o inc/*~ src/*~ $(EXECS) *~ *.swp
	rm -rf doc/html doc/latex pa1_brac_carr_nien.tar Program_Writeup.pdf
edit:
	gedit inc/*.h src/*.cpp Makefile &
sublime:
	subl inc/*.h src/*.cpp Makefile &
#ZIP UP ENTIRE ARCHIVE FOR SUBMISSION. GENERATE LATEX PDF AND LET ER GO
archive:
	make realclean
	make doxygen
	tar --exclude='../ann-tinder/.git' --exclude='../ann-tinder/doc' -cvf pa1_brac_carr_nien.tar ../ann-tinder/
#Don't ask.....
a_better_person:
	@echo ""
	@echo "( ͡° ͜ʖ ͡°)  ﻿ｙｏｕ  ａｒｅ  ａ  ｗｏｎｄｅｒｆｕｌ  ｐｅｒｓｏｎ"
	@echo ""