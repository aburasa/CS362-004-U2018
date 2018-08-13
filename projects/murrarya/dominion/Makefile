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
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage unittest1.c dominion.o rngs.o -o unittest1
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage unittest2.c dominion.o rngs.o -o unittest2
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage unittest3.c dominion.o rngs.o -o unittest3
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage unittest4.c dominion.o rngs.o -o unittest4
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage cardtest1.c dominion.o rngs.o -o cardtest1
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage cardtest2.c dominion.o rngs.o -o cardtest2
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage cardtest3.c dominion.o rngs.o -o cardtest3
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage cardtest4.c dominion.o rngs.o -o cardtest4
	./unittest1 > unittestresults.out
	gcov -b unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b cardtest4 >> unittestresults.out

randomtests: dominion.o rngs.o randomtestcard1.c
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage randomtestcard1.c dominion.o rngs.o -o randomtestcard1
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage randomtestcard2.c dominion.o rngs.o -o randomtestcard2
	gcc --std=c99 -g -lm -fprofile-arcs -ftest-coverage randomtestcard3.c dominion.o rngs.o -o randomtestcard3
	./randomtestcard1 > randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	./randomtestcard3 >> randomtestresults.out
	gcov -f -b dominion.c >> randomtestresults.out
	#gcov -b randomtestcard1 >> randomtestresults.out
	#gcov -b randomtestcard2 >> randomtestresults.out
	#gcov -b randomtestcard3 >> randomtestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
