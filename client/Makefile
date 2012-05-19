CC := gcc
CFLAGS := -g -w -O2

COMMONDIR := ../common

OBJS := main.o ftpclient.o \
	$(COMMONDIR)/common.o $(COMMONDIR)/utils.o $(COMMONDIR)/const.o

all: ftpclient

ftpclient: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY:
clean:
	rm -f *.o
	rm -f ftpclient
	rm -f ../common/*.o
