CC=         g++
CFLAGS=     -g -gdwarf-2 -Wall -std=c++11 -static-libstdc++
TARGETS=	rorschach

all:	$(TARGETS)


rorschach:	parse.o watch.o utilities.o changes.o main.o
	@$(CC) $(CFLAGS) -o $@ $^

parse.o:	parse.cpp
	@$(CC) $(CFLAGS) -c -o $@ $^

watch.o:	watch.cpp
	@$(CC) $(CFLAGS) -c -o $@ $^

utilities.o: utilities.cpp
	@$(CC) $(CFLAGS) -c -o $@ $^

changes.o: changes.cpp
	@$(CC) $(CFLAGS) -c -o $@ $^

main.o:		main.cpp
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o
