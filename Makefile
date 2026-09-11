
REMOVE = rate_dsob.out scheduler edf_dsob.out

all:
	gcc main.c -o scheduler
	./scheduler edf voo.txt
	./scheduler rate voo.txt

compile:
	gcc main.c -o scheduler

clean:
	rm -f $(REMOVE)