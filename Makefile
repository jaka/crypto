OPTS := -O2 -s -std=c99
CFLAGS += -Iinclude -Wall -Werror -Wextra -pedantic -fdata-sections -ffunction-sections -fno-exceptions -fstrict-aliasing -fPIC 
LDFLAGS += --gc-sections
SFLAGS := -R .comment -R .gnu.version -R .gnu.version_r -R .note -R .note.ABI-tag

CC ?= cc
LD ?= ld

SOURCES	:= $(wildcard src/*.c)
OBJECTS	:= $(patsubst %.c,%.o,$(SOURCES))
TARGET := libcrypto.so

.PHONY: test

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(OPTS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -shared -o $@ $^

test:
	$(MAKE) -C test/ all

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)
