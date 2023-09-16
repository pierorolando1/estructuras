CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = main

$(TARGET): main.cpp
	rm -f main && $(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp && clear && ./$(TARGET) && rm -f main

clean:
	rm -f $(TARGET)
