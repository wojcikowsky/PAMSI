
TRGDIR=./
FLAGS= -Wall -pedantic -std=c++14 -iquote inc

__start__: ${TRGDIR}/sort
	${TRGDIR}/sort

${TRGDIR}/sort: main.o Sort.o

	g++ -o ${TRGDIR}/sort main.o Sort.o

main.o: main.cpp Sort.hh
	g++ -c ${FLAGS} -o main.o main.cpp

Sort.o: Sort.cpp Sort.hh
	g++ -c ${FLAGS} -o Sort.o Sort.cpp