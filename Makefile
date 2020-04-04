HEADERS = biblio.h

all: main

main:   main.o biblio.o
			gcc  -o main    main.o biblio.o

main.o: main.c $(HEADERS)
			gcc -o main.o -c main.c

biblio.o: biblio.c 
			gcc -o biblio.o -c biblio.c

clean:
		rm -rf *.o

clean_all: clean
		rm -rf main
		