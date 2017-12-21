##-----------------------------------
##Albert Garcia
##awgarcia
##pa2
##-----------------------------------
#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 2
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -g -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -g -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -g -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -g -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -g -c -std=c99 -Wall List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o
 