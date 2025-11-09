CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
OBJ = main.o Book.o Exercise.o
TARGET = exercises

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp Book.h Exercise.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Book.o: Book.cpp Book.h Exercise.h
	$(CXX) $(CXXFLAGS) -c Book.cpp

Exercise.o: Exercise.cpp Exercise.h Book.h
	$(CXX) $(CXXFLAGS) -c Exercise.cpp

clean:
	rm -f $(OBJ) $(TARGET)
