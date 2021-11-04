all: work12.o
	gcc -o work12m work12.o

nov1.o: work12.c
	gcc -c work12.c

run:
	./work12m

clean:
	rm *.o
	rm work12m
