CC = gcc

TARGET1 = test
TARGET2 = main

remove:
		rm main test

test: sort_array_tests.c sort_array.c
		$(CC) unity.c sort_array_tests.c sort_array.c -o $(TARGET1)

main: main.c sort_array.c
		$(CC) main.c sort_array.c -o $(TARGET2)


runtest: $(TARGET1)
	./$(TARGET1)

runmain: $(TARGET2)
	./$(TARGET2) ../records.csv
