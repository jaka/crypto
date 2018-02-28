OPTS := -O2 -s -std=c99
CFLAGS += -Iinclude -Wall -Werror -Wextra -pedantic -fdata-sections -ffunction-sections -fno-exceptions -fstrict-aliasing -fPIC -fvisibility=hidden
LDFLAGS += -Wl,--gc-sections -Wl,-O1 -Wl,--discard-all
SFLAGS := -R .comment -R .gnu.version -R .gnu.version_r -R .note -R .note.ABI-tag

CC ?= cc
DESTDIR ?= /usr/lib

SOURCES	:= $(wildcard src/*.c)
OBJECTS	:= $(patsubst %.c,%.o,$(SOURCES))
TARGET := libutils.so

.PHONY: test

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(OPTS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -shared -o $@ $^

test:
	$(MAKE) -C test/ all

install: $(TARGET)
	install -m 755 $(TARGET) $(DESTDIR)/

install-dev:
	mkdir -p /usr/include/crypto
	cp ./include/*.h /usr/include/crypto

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)
