AutoCorrect : main.o Linklist.o FileIO.o check.o checkFunc.o  Linklist.h FileIO.h check.h checkFunc.h config.h
	gcc main.o Linklist.o FileIO.o check.o checkFunc.o  Linklist.h FileIO.h check.h checkFunc.h config.h -o AutoCorrect -g

main.o : main.c Linklist.h FileIO.h check.h checkFunc.h config.h
	gcc main.c -c -g

Linklist.o : Linklist.c Linklist.h
	gcc Linklist.c -c -g

FileIO.o : FileIO.c config.h Linklist.h
	gcc FileIO.c -c -g

checkFunc.o : checkFunc.c 
	gcc checkFunc.c -c -g

clean :
	printf "The .o's have been terminated\n"# i tried
	printf "get to the chopper now\n"
	rm main.o Linklist.o checkFunc.o FileIO.o AutoCorrect