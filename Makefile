HEADERS = biblio.h
TARGETS = cmd tag parcour

all: tags

tags:   main.o biblio.o parcour.o
			gcc  -o tag    main.o biblio.o parcour.o

parcour: parcour.o biblio.o
		gcc -o parcour parcour.o biblio.o

cmd: cmd.o biblio.o
		gcc  -o cmd cmd.o biblio.o

main.o: main.c $(HEADERS)
			gcc -o main.o -c main.c

cmd.o: cmd.c  $(HEADERS) cmd.h
			gcc -o cmd.o -c cmd.c

parcour.o: parcour.c  $(HEADERS)
			gcc -o parcour.o -c parcour.c

biblio.o: biblio.c 
			gcc -o biblio.o -c biblio.c

clean:
		rm -rf *.o

clean_all: clean
		rm -rf $(TARGETS)
		