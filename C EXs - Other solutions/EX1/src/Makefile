CC = gcc

TARGET1 = test
TARGET2 = main

remove:
		rm main test

test: Main_test.c structure.c sort_lib.c
		$(CC) ../../Resources/C/Unity/unity.c Main_test.c structure.c sort_lib.c -o $(TARGET1)

main: Main.c structure.c sort_lib.c
		$(CC) Main.c structure.c sort_lib.c -o $(TARGET2)


runtest: $(TARGET1)
	./$(TARGET1)

runmain: $(TARGET2)
	./$(TARGET2) ./dataset/records.csv
