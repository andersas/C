VERSION = -DVERSION="3.0"
SOURCES	= main.c functions.c threesides.c twosides.c oneside.c output.c
PROGRAM = triangle
OBJECTS = $(SOURCES:.c=.o)
WINDOZE = # -DWINDOZE # for running better in a windoze enviroment

CC	= gcc
CFLAGS  = -c -Wall $(VERSION)
LIBS	= -lm



all : $(PROGRAM)


clean :
	rm -f $(OBJECTS) $(PROGRAM)

$(PROGRAM)	: $(OBJECTS)
	$(CC) $(LIBS) -o $@ $(OBJECTS)

$(OBJECTS)	: $(SOURCES)
	$(CC) $(CFLAGS) $(WINDOZE) $*.c -o $@




