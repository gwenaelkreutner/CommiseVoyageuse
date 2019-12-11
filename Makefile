IDIR = include
ODIR = obj
SDIR = src

CC = gcc
CFLAGS = -g -Wall -std=c99 -I$(IDIR)

PROG = map

_DEPS = list.h road.h town.h graph.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= list.o road.o town.o main.o graph.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: run all clean delete

run : all
	./$(PROG)

all : $(PROG) # others app can be build here

$(PROG) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -f $(ODIR)/*.o core

delete : clean
	rm $(PROG)
