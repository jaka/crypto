CFLAGS += -I ../include

all: test_base64 test_sha1

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

test_%: _%.o test.o
	@$(CC) -o $@ $^
	@./$@
	@rm -f $@ $<
