

all: main

main:   main.o 
			gcc  -o main    main.o
set_tags:   set_tags.o 
			gcc  -o set_tags    set_tags.o

main.o: main.c 
			gcc -o main.o -c main.c

set_tags.o: set_tags.c 
			gcc -o set_tags.o -c set_tags.c

clean:
		rm -rf *.o

clean_all: clean
		rm -rf main
		rm -rf set_tags