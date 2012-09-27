objdir = bin
objs = $(addprefix $(objdir)/, sudoku.o strategies.o testa.o)
CFLAGS = -O0 -ggdb3 -Wall # -Werror -ansi -pedantic

all: testa *.c

testa: $(objs)
	$(CC) $(CFLAGS) $(objs) -o $(objdir)/$@

bin/%.o: %.c
	mkdir -p $(objdir)
	$(CC) -c $(CFLAGS) $< -o $@

$(objdir):
	mkdir -p $(objdir)

clean:
	rm -Rf bin
