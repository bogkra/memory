CXX=g++
CFLAGS=--std=c++14 -Wall -Wextra -Wpedantic -Iincludes

list2: *.cpp #includes/*.hpp
	$(CXX) list2.cpp -o $@ $(CFLAGS)

clean:
	rm list2
