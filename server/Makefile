CC := gcc
CFLAGS := -g -w -O2

COMMONDIR := ../common

OBJS := main.o ftpserver.o \
	$(COMMONDIR)/common.o $(COMMONDIR)/utils.o $(COMMONDIR)/const.o

all: ftpserver

ftpserver: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY:
clean:
	rm -f *.o
	rm -f ftpserver
	rm -f ../common/*.o
