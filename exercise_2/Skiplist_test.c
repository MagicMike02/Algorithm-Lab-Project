//
// Created by zahra roshanie on 31/07/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "skiplist.h"


//It returns a number less than zero iff the first string is less than
//the second one , 0 iff both are equal and  greater than zero otherwise.
static int precedes_record_string_field(void *s1_p, void *s2_p) {
    if (s1_p == NULL) {
        fprintf(stderr, "precedes_string: the first parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    if (s2_p == NULL) {
        fprintf(stderr, "precedes_string: the second parameter is a null pointer");
        exit(EXIT_FAILURE);
    }

    return strcmp((char *) s1_p, (char *) s2_p);
}

//Data elements that are initialized before each test
static char str1[10],str2[10],str3[10];
static Skiplist *list_str;

void setUp(void){
    strcpy(str1, "macellaio");
    strcpy(str2, "ammarerai");
    strcpy(str3, "riavviera");

    list_str = skipList_create(precedes_record_string_field);
}

void tearDown(void){
    skiplist_free(list_str);
}

static void test_skiplist_add_one_el(void){
    insertSkiplist(list_str, (void *) str1);
    char expected_str[] = "macellaio";
    char * actual_str = (char *)searchSkipList(list_str, (void *)str1);
    TEST_ASSERT_EQUAL_STRING(expected_str, actual_str);
}

static void test_skiplist_add_two_el(void){
    insertSkiplist(list_str, (void *) str2);
    char expected_str[] = "ammarerai";
    char * actual_str = (char *)searchSkipList(list_str, (void *)str2);
    TEST_ASSERT_EQUAL_STRING(expected_str, actual_str);
}

static void test_skiplist_add_three_el(void){
    insertSkiplist(list_str, (void *) str3);
    char expected_str[] = "riavviera";
    char * actual_str = (char *)searchSkipList(list_str, (void *)str3);
    TEST_ASSERT_EQUAL_STRING(expected_str, actual_str);
}

static void test_skiplist_is_empty(void){
    TEST_ASSERT_NULL((char *)searchSkipList(list_str, (void *)str3));
}

int main(void) {

    //test session
    UNITY_BEGIN();

    RUN_TEST(test_skiplist_add_one_el);
    RUN_TEST(test_skiplist_add_two_el);
    RUN_TEST(test_skiplist_add_three_el);
    RUN_TEST(test_skiplist_is_empty);

    return UNITY_END();
}


