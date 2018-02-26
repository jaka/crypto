CFLAGS += -I ../include

TARGETS = test_base64 test_sha1 test_hmac-sha1

all: $(TARGETS)

%.o: %.c
	@$(CC) $(CFLAGS) -c -g -o $@ $<

test_%: _%.o test.o
	@$(CC) -g -o $@ $^
	@./$@
	@rm -f $@ $<

clean:
	rm -f $(TARGETS)
