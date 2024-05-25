CC = gcc
LIB = -lm
CFLAGS = -Wall -O1
DEBUG = -g
TARGET = clasament 
all: final

test: clean final
	./$(TARGET) ./Input/test2.in ./result1.out ./result2.out

final: 
	$(CC) $(CFLAGS) $(LIB) $(DEBUG) -o $(TARGET) $(shell find . -name '*.c')
	chmod +x $(TARGET) 

clean: 
	rm $(TARGET) &> /dev/null
	# rm -r OutputGrapf &> /dev/null
	# rm -r OutputScor &> /dev/null
	rm result1.out &> /dev/null
	rm result2.out &> /dev/null

