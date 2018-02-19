OPTS	:= -O2 -s
CFLAGS	+= -Iinclude -Wall -Werror -Wextra -pedantic -fdata-sections -ffunction-sections -fno-exceptions -fstrict-aliasing -fPIC -std=c90
LDFLAGS	+= --gc-sections
SFLAGS	:= -R .comment -R .gnu.version -R .gnu.version_r -R .note -R .note.ABI-tag

CC	?= cc
LD	?= ld

SOURCES	:= $(wildcard src/*.c)
OBJECTS	:= $(patsubst %.c,%.o,$(SOURCES))
TARGETS := libcrypto.so

all: $(OBJECTS) $(TARGETS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(OPTS) -c -o $@ $<

$(TARGETS): $(OBJECTS)
	$(LD) $(LDFLAGS) -shared -o $@ $^
