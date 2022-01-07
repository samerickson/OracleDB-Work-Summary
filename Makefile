

G = g++-4.9
IFLAG = -I
CFLAGS = -I/usr/local/lib/Oracle/instantclient_11_2/sdk/include
LFLAGS = -L/usr/local/lib/Oracle/instantclient_11_2 -locci -lociei
INCLUDE = include
SOURCE = src
OBJECT = build
BINARY = bin

$(BINARY)/main: $(OBJECT)/main.o $(OBJECT)/interface.o
	$(G) $(LFLAGS) $(IFLAG) $(INCLUDE) $(OBJECT)/main.o $(OBJECT)/interface.o -o $(BINARY)/main

$(OBJECT)/main.o: $(SOURCE)/main.cpp
	$(G) $(IFLAG) $(INCLUDE) -c $(CFLAGS) $(SOURCE)/main.cpp -o $(OBJECT)/main.o

$(OBJECT)/interface.o: $(SOURCE)/interface.cpp $(INCLUDE)/interface.hpp
	$(G) $(IFLAG) $(INCLUDE) -c $(CFLAGS) $(SOURCE)/interface.cpp -o $(OBJECT)/interface.o

clean:
	rm ${BUILD}* ${BINARY}/main

docs:
	pandoc -s -V geometry:margin=1in README.md -o README.pdf
