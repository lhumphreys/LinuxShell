CC=gcc

NAME=mysh
MAIN=cscd340Lab8.c
LL_DEP=./linkedlist/linkedList.o ./linkedlist/listUtils.o
PATH_DEP=./path/path.o ./path/pathUtils.o
HIST_DEP=./history/history.o ./history/historyUtils.o
UTILS_DEP=./utils/myUtils.o ./utils/lauraUtils.o

${NAME}:	cscd340Lab8.c ./tokenize/makeArgs.o ./process/process.o ./pipes/pipes.o ./redirect/redirect.o ${LL_DEP} ${PATH_DEP} ${HIST_DEP} ${UTILS_DEP}
	gcc -g cscd340Lab8.c ./tokenize/makeArgs.o ./process/process.o ./pipes/pipes.o ./redirect/redirect.o ${LL_DEP} ${PATH_DEP} ${HIST_DEP} ${UTILS_DEP} -o ${NAME}

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

lauraUtils.o:	./utils/lauraUtils.c ./utils/lauraUtils.h
	gcc -g -c ./utils/lauraUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

path.o:		./path/path.c ./path/path.h
	gcc -g -c -m32 ./path/path.c

pathUtils.o:	./path/pathUtils.c ./path/pathUtils.h
	gcc -g -c -m32 ./path/pathUtils.c

linkedList.o:	./linkedlist/linkedList.h ./linkedlist/linkedList.c ./linkedlist/genericData.h ./linkedlist/requiredIncludes.h
	gcc -c -g -m32 ./linkedlist/linkedList.c

listUtils.o:	./linkedlist/listUtils.c ./linkedlist/listUtils.h
	gcc -c -g -m32 ./linkedlist/listUtils.c

history.o:	./history/history.c ./history/history.h
	gcc -g -c -m32 ./history/history.c

historyUtils.o:	./history/historyUtils.c ./history/historyUtils.h
	gcc -g -c -m32 ./history/history.c

redirect.o:	./redirect/redirect.c ./redirect/redirect.h
	gcc -g -c ./redirect/redirect.c
clean:
	rm ./pipes/pipes.o	
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./linkedlist/linkedList.o
	rm ./linkedlist/listUtils.o
	rm ./path/path.o
	rm ./path/pathUtils.o
	rm ./utils/lauraUtils.o
	rm ./history/history.o
	rm ./history/historyUtils.o
	rm ./redirect/redirect.o
	rm mysh
