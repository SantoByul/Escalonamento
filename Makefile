

all:
	gcc main.c -o escalonamento
	./escalonamento

clean:
	rm -f escalonamento