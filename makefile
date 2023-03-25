# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g -O3
INCLUDE = ../
# ****************************************************
# Targets needed to bring the executable up to date
 
exp.e: exponential.o 
	$(CC) $(CFLAGS) -o exp exponential.o -I $(INCLUDE) 
	
exponential.o: exponential.cpp rand.o randInt.o randExp.o randNorm.o randBernouli.o
	$(CC) $(CFLAGS) -c exponential.cpp -I $(INCLUDE) 
    
rand.o: rand.cpp RNG.o
	$(CC) $(CFLAGS) -c rand.cpp -I $(INCLUDE)
	
randInt.o: randInt.cpp RNG.o
	$(CC) $(CFLAGS) -c randInt.cpp -I $(INCLUDE)
	
randExp.o: randExp.cpp RNG.o
	$(CC) $(CFLAGS) -c randExp.cpp -I $(INCLUDE)
	
randNorm.o: randNorm.cpp RNG.o
	$(CC) $(CFLAGS) -c randNorm.cpp -I $(INCLUDE)
	
randBernouli.o: randBernouli.cpp RNG.o
	$(CC) $(CFLAGS) -c randBernouli.cpp -I $(INCLUDE)
	
RNG.o: RNG.cpp RNG.h
	$(CC) $(CFLAGS) -c RNG.cpp -I $(INCLUDE)
	
clean:
	rm exponential.o
	rm randBernouli.o
	rm randNorm.o
	rm randExp.o
	rm randInt.o
	rm rand.o
	rm RNG.o
	rm rand.cpp
	rm randInt.cpp
	rm randBernouli.cpp
	rm randExp.cpp
	rm randNorm.cpp 
	rm exp 
