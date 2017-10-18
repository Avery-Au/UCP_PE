CC = gcc
EXEC = spellChecker
OBJ = spellChecker.o linkList.o fileFunc.o callBackFunc.o
OBJ2 = check.o
CFLAGS = -Wall -ansi -pedantic -g

$(EXEC): $(OBJ) $(OBJ2)
	$(CC) $(OBJ) $(OBJ2) -o $(EXEC)

callBackFunc.o: callBackFunc.c callBackFunc.h check.h
	$(CC) -c callBackFunc.c $(CFLAGS)

fileFunc.o: fileFunc.c fileFunc.h linkList.h check.h
	$(CC) -c fileFunc.c $(CFLAGS)

linkList.o: linkList.c linkList.h
	$(CC) -c linkList.c $(CFLAGS)

spellChecker.o: spellChecker.c spellChecker.h fileFunc.h linkList.h check.h callBackFunc.h
	$(CC) -c spellChecker.c $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
