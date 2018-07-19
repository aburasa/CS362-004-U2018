testme.o:
	gcc -c testme.c -g
	
default: testme.o
	gcc -o testme testme.o
	
runtest: default
	./testme

clean:
	rm -f testme *.o