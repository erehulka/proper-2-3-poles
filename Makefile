BA_GRAPH_PATH = /Users/erehulka/Documents/Informatika/ZIMA2/RP/ba-graph
CFLAGS = -std=c++17 -fconcepts -I$(BA_GRAPH_PATH)/include
LDFLAGS = -lstdc++fs -lcurl
DBGFLAGS = -g -O0 -pedantic
COMPILE_DBG = g++-12 -O2 $(CFLAGS) $(DBGFLAGS)


copy_implementation:
	cp $(BA_GRAPH_PATH)/test/implementation_basic.h implementation.h
all: copy_implementation compile_test
compile_test:
	$(COMPILE_DBG) test.cpp -o test.out $(LDFLAGS)

clean:
	rm -rf *.out

.PHONY: clean all copy_implementation compile_test