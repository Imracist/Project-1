CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = simcity

all: $(TARGET)

$(TARGET): main.o config.o region.o simulation.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o config.o region.o simulation.o

main.o: main.cpp config.h region.h simulation.h
	$(CXX) $(CXXFLAGS) -c main.cpp

config.o: config.cpp config.h
	$(CXX) $(CXXFLAGS) -c config.cpp

region.o: region.cpp region.h
	$(CXX) $(CXXFLAGS) -c region.cpp

simulation.o: simulation.cpp simulation.h
	$(CXX) $(CXXFLAGS) -c simulation.cpp

clean:
	rm -f *.o $(TARGET)
