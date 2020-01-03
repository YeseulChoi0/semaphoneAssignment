all: go.o functions.o
	gcc -o ./go go.o
	gcc -o ./functions functions.o

go.o: go.c header.h
	gcc -c go.c header.h

functions.o: functions.c header.h
	gcc -c functions.c header.h
	
