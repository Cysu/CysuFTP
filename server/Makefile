CC := gcc
CFLAGS := -g -Wall -O2

COMMONDIR := ../common

OBJS := main.o ftpserver.o \
	$(COMMONDIR)/common.o $(COMMONDIR)/utils.o

all: ftpserver

ftpserver: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm *.o
	rm $(COMMONDIR)/*.o
