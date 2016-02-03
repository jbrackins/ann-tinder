# GNU C/C++ compiler and linker:
LINK = g++

# COMPILER OPTIONS:

CFLAGS = -c  -g -O0
CXXFLAGS = $(CFLAGS) -std=c++11 -Wall

#OBJECT FILES
OBJS = src/ANNtest.o src/ANNtrain.o src/CrossValidate.o src/Prm.o

#HEADER FILES
HEAD = inc/main.h

#EXECUTABLES
EXECS = ANNtest ANNtrain CrossValidate

all: ANNtest ANNtrain CrossValidate

ANNtest: src/ANNtest.o src/Prm.o
	$(LINK) -o $@ $^
ANNtrain: src/ANNtrain.o
	${LINK} -o $@ $^
CrossValidate: src/CrossValidate.o
	${LINK} -o $@ $^
doxygen:
	doxygen doc/doxy.conf 
dox:
	doxygen doc/doxy.conf 
clean:
	rm -f *.o ANNtest ANNtrain CrossValidate *~ core src/*.o inc/*~ src/*~ $(EXECS) *~
realclean:
	rm -f *.o ANNtest ANNtrain CrossValidate *~ core src/*.o inc/*~ src/*~ $(EXECS) *~ *.swp
edit:
	gedit inc/*.h src/*.cpp Makefile &
sublime:
	sublime inc/*.h src/*.cpp Makefile &
