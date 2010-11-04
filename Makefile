# Path to cross tools


EXECUTABLES=$(addprefix bin/, crypto)


# Compiler and linker commands

CC=g++ -Wall -W -O -I include

all: bin/crypto


#### RULE USED TO START SIMICS 

run: bin/crypto 
	./$<

#### RULE TO BUILD BINARIES FROM OBJECT FILES

bin/crypto: $(addprefix build/, EllipticCurve.o Point.o interface.o DiffieHellman.o MasseyOmura.o util.o crypto.o)
	$(CC) -o$i $@ $^ -lgmpxx -lgmp

###### GENERIC BUILD PATTERNS ########

build/%.o: src/%.cc
	$(CC) -c $< -o $@	

pack: 
	tar -czvf crypto.tar.gz include/*.h build/* bin/* src/*.cc Makefile

clean: 
	pwd
	rm -f build/*.o
	rm -f include/*~ include/#* include/*#
	rm -f src/*~ src/#* src/*#
	rm -f ${EXECUTABLES}	
