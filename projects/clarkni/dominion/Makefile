CFLAGS = -Wall -fpic -coverage -lm -std=c99


unittest1: unittest1.c dominion.o rngs.o interface.o 
	gcc -o unittest1 -g -std=c99 unittest1.c dominion.o rngs.o interface.o  $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g -std=c99 unittest2.c dominion.o rngs.o interface.o  $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g -std=c99 unittest3.c dominion.o rngs.o interface.o  $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g -std=c99 unittest4.c dominion.o rngs.o interface.o  $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g -std=c99 cardtest1.c dominion.o rngs.o interface.o  $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g -std=c99 cardtest2.c dominion.o rngs.o interface.o  $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g -std=c99 cardtest3.c dominion.o rngs.o interface.o  $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g -std=c99 cardtest4.c dominion.o rngs.o interface.o  $(CFLAGS)

assignment3_test_suite: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

unittestresults: assignment3_test_suite dominion.o rngs.o interface.o
	./unittest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
