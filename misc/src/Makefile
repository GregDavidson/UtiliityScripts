BINS = now
PGMS = $(BINS) $(SCRIPTS)

now: now.c
	gcc -o now now.c
install: $(PGMS)
	mv $(BINS) ../bin.`arch`
