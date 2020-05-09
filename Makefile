HEADERS = biblio.h 
TARGETS = tags 

all: tags



tags: tags.o biblio.o
		gcc  -o tags tags.o biblio.o

tags.o: tags.c  $(HEADERS) tags.h
			gcc -o tags.o -c tags.c

biblio.o: biblio.c tags.h
			gcc -o biblio.o -c biblio.c

clean:
		rm -rf *.o

clean_all: clean
		rm -rf $(TARGETS)
		