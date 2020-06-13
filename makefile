execute:
	g++ -c LifeGame.cc
	g++ -o LifeGame.exe LifeGame.o
	-mv LifeGame.exe ./tmp
	-mv LifeGame.o ./tmp
	./tmp/LifeGame.exe

clean:
	rm ./tmp/LifeGame.o 
	rm ./tmp/LifeGame.exe