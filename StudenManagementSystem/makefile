CC=gcc
OBJS=ms.o main.o
CFLAGF=-c -g
main:$(OBJS)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGF) $< -o $@
.PHONY:clean
clean:
	$(RM) *.o main