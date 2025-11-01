all: brighten

Image.o: Image.cpp Image.H
	g++ -c -Wall -Werror -std=c++17 Image.cpp

main.o: main.cpp Image.H
	g++ -c -Wall -Werror -std=c++17 main.cpp

brighten: main.o Image.o
	g++ -o brighten main.o Image.o

clean:
	rm -f *.o brighten brightened.ppm
