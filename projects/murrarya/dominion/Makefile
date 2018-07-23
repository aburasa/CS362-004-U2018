CFLAGS = -Wall -fpic -coverage -lm -std=c99

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

unittestresults: dominion.o rngs.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	gcc -g -lm -fprofile-arcs -ftestcoverage unittest1.c -o unittest1
	gcc -g -lm -fprofile-arcs -ftestcoverage unittest2.c -o unittest2
	gcc -g -lm -fprofile-arcs -ftestcoverage unittest3.c -o unittest3
	gcc -g -lm -fprofile-arcs -ftestcoverage unittest4.c -o unittest4
	gcc -g -lm -fprofile-arcs -ftestcoverage cardtest1.c -o cardtest1
	gcc -g -lm -fprofile-arcs -ftestcoverage cardtest2.c -o cardtest2
	gcc -g -lm -fprofile-arcs -ftestcoverage cardtest3.c -o cardtest3
	gcc -g -lm -fprofile-arcs -ftestcoverage cardtest4.c -o cardtest4
	./unittest1 > unittestresults.out
	gcov unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov cardtest4 >> unittestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
