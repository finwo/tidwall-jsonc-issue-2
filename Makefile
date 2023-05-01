CPP=g++

SRC:=
SRC+=$(wildcard src/*.c)

override CFLAGS?=-Wall -s -O2

INCLUDES:=
INCLUDES+=-I src

include lib/.dep/config.mk

OBJ:=$(SRC:.c=.o)
OBJ:=$(OBJ:.cc=.o)

override CFLAGS+=$(INCLUDES)
override CPPFLAGS=`pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`
override LDFLAGS+=`pkg-config --libs gtk+-3.0 webkit2gtk-4.0`

default: example

util/bin2c:
	$(CC) $@.c -o $@

src/index.h: util/bin2c src/index.html
	util/bin2c < src/index.html > src/index.h

$(OBJ): src/index.h

example: $(OBJ)
	$(CPP) $(LDFLAGS) $(OBJ) -o $@
