CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


unittestresults: unittest1mine.c unittest2mine.c unittest3remodel.c unittest4gameover.c dominion.o interface.o rngs.o
	gcc -o UnitTestBug1 unittest1mine.c dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o UnitTestBug2 unittest2mine.c dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o UnitTestBug3 unittest3remodel.c dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o UnitTestBug4 unittest4gameover.c dominion.o rngs.o interface.o $(CFLAGS)
	./UnitTestBug1
	./UnitTestBug2
	./UnitTestBug3
	./UnitTestBug4
	gcov dominion.c -b -f >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe UnitTestBug*
