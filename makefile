all:
	gcc ./headers/include.h	 ./headers/shifitAnd.h	   ./source/shifitAnd.c 	mainArthur.c	-lm  -o	 exec
	./exec

leitura:
	gcc ./headers/include.h	 ./headers/leitura.h	   ./source/leitura.c 	mainLeitura.c	-lm  -o	 exec
	./exec

gpt:
	gcc ./headers/include.h	 	   shifitAndGPT.c	-lm  -o	 exec
	./exec

main:
	gcc ./headers/include.h	   main.c	-lm  -o	 exec
	./exec