CC = gcc

TARGET1 = test
TARGET2 = main

remove:
		rm main test

test: Main_test.c skiplist.c
		$(CC) ../../Resources/C/Unity/unity.c Main_test.c skiplist.c -o $(TARGET1)

main: Main.c skiplist.c
		$(CC) Main.c skiplist.c -o  $(TARGET2)

runtest: $(TARGET1)
	./$(TARGET1)

runmain: $(TARGET2)
	./$(TARGET2) "../dataset/dictionary.txt" "../dataset/correctme.txt"

