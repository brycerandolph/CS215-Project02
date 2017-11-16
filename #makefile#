P2.out: Proj2app.o SetLimits.o CGame.o
	g++ -g -o P2.out Proj2app.o SetLimits.o CGame.o

Proj2app.o: Proj2app.cpp SetLimits.h CGame.h
	g++ -g -c Proj2app.cpp

SetLimits.o: SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

CGame.o: CGame.cpp CGame.h
	g++ -g -c CGame.cpp

clean:
	rm *.o P2.out

run : P2.out
	clear
	./P2.out

runin : P2.out input
	clear
	./P2.out < input

submit : Proj2app.cpp CGame.h CGame.cpp makefile README.txt
	rm -rf randolphP2
	mkdir randolphP2
	cp Proj2app.cpp randolphP2
	cp CGame.h randolphP2
	cp CGame.cpp randolphP2
	cp makefile randolphP2
	cp README.txt randolphP2
	tar cfvz randolphP2.tgz randolphP2
	cp randolphP2.tgz ~cs215/cs215drop
