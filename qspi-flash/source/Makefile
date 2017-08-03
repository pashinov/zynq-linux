APP=qspi-flash
CC=gcc
CFLAGS=-I.
DEPS = 
OBJ = qspi-flash.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(APP): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	rm -f *.o
