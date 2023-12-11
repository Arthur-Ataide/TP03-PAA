all:
	gcc ./headers/include.h	 ./headers/shifitAnd.h  ./headers/bm.h   ./headers/codificar.h	./headers/random_key.h  ./headers/leitura.h 	   ./source/shifitAnd.c  ./source/bm.c 	 ./source/codificar.c  ./source/random_key.c	./source/leitura.c	main.c	-lm  -o	 exec
	./exec
