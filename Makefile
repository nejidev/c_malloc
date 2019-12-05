CROSSCOMPILE := 
CFLAGS  := -Wall -O2 -c -Wall -Werror -g
LDFLAGS :=
TARGET  := sram_malloc

CC := $(CROSSCOMPILE)gcc
LD := $(CROSSCOMPILE)ld

OBJS := main.o sram.o

all:$(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $^
	
clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	
%.o:%c
	$(CC) $(CFLAGS) -o $@ $<