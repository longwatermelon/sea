SRC=$(wildcard src/*.cpp)
OBJS=$(addprefix obj/, $(SRC:.cpp=.o))

CXX=g++
CXXFLAGS=-std=c++17 -ggdb -Wall -Wextra -pedantic
LDFLAGS=

all:
	mkdir -p obj/src/
	$(MAKE) sea

sea: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS)

obj/src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	-rm -rf obj a.out
