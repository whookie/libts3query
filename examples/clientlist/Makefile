
BUILDNAME := clientlist

CXX = g++
LNK += -lts3query
CXXFILES += main.cpp

build:
	$(CXX) -o $(BUILDNAME) $(CXXFILES) $(LNK)

clean:
	rm $(BUILDNAME)

.PHONY: build clean
