all:
	gcc ./headers/include.h	 ./headers/shifitAnd.h  ./headers/bm.h   ./headers/codificar.h	./headers/random_key.h  ./headers/leitura.h 	   ./source/shifitAnd.c  ./source/bm.c 	 ./source/codificar.c  ./source/random_key.c	./source/leitura.c	main.c	-lm  -o	 exec
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