#VigenereChpher: VigenereCipher.o
#	g++ -Wall -o VigenereCipher VigenereCipher.o

#VigenereCipher.o: VigenereCipher.cpp
#	g++ -c VigenereCipher.cpp
test: test.o
	g++ -Wall -o test test.o -L../lib -lViCi

test.o: test.cpp
	g++ -Wall -I../include -c test.cpp

.PHONY: clean rebuild
clean:
	-rm ../lib/*.o *.o test

rebuild:
	-rm ../lib/*
	g++ -Wall  -I../include \
	-o ../lib/VigenereCipher.o \
	-c ../src/VigenereCipherSource.cpp
	ar rcs ../lib/libViCi.a ../lib/VigenereCipher.o
