CC = gcc

TARGET1 = test
TARGET2 = main

remove:
			rm main test

test: Skiplist_test.c skiplist.c 
			$(CC) unity.c Skiplist_test.c skiplist.c -o $(TARGET1)

main: main.c skiplist.c 
			$(CC) main.c skiplist.c -o $(TARGET2)

runtest: $(TARGET1)
		./$(TARGET1)

runmain: $(TARGET2)
		./$(TARGET2) dictionary.txt correctme.txt