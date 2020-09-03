all: lab2 

lab2: bcard.cpp
	g++ -Wall bcard.cpp -o lab2

clean:
	rm -f lab2 *.o


