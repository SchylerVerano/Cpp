CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

OBJS = main.o TextGenerator.o

TARGET = TextGen.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp TextGenerator.h Pattern.h
	$(CXX) $(CXXFLAGS) -c main.cpp

TextGenerator.o: TextGenerator.cpp TextGenerator.h Pattern.h
	$(CXX) $(CXXFLAGS) -c TextGenerator.cpp

clean:
	rm -f $(OBJS) $(TARGET)
