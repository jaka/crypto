CFLAGS += -I ../include

TARGETS = test_base64 test_sha1

all: $(TARGETS)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

test_%: _%.o test.o
	@$(CC) -o $@ $^
	@./$@
	@rm -f $@ $<

clean:
	rm -f $(TARGETS)
