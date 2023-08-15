//
// Created by zahra roshanaie on 26/04/22.
//
#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "sort_array.h"

/*
 * Test suite for sort array data structure and algorithms
 */

//precedence relation used in tests
static int precedes_int(void* i1_p,void* i2_p){
    int* int1_p = (int*)i1_p;
    int* int2_p = (int*)i2_p;
    if((*int1_p) < (*int2_p))
        return(-1);
    else if((*int1_p) > (*int2_p))
        return (1);
    return(0);
}



//Data elements that are initialized before each test
static int i1,i2,i3;
static int *a[3];

void setUp(void){
    i1 = -12;
    i2 = 0;
    i3 = 4;
    a[0] = &i1;
    a[1] = &i2;
    a[2] = &i3;

}

//void tearDown(void){
//    free(a);
//}

static void test_binary_insertion_sort(void){
    //int* expected_array[] = {&i1, &i2, &i3};
    int* actual_array[] = {&i3, &i2, &i1};
    b_insertion_sort((void *) actual_array, 3, precedes_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(a, actual_array, 3);
}
int main(){
    //test session
    UNITY_BEGIN();

    RUN_TEST(test_binary_insertion_sort);

    return UNITY_END();
}