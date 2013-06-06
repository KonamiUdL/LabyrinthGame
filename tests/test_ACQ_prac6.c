/*
 * File:   test_ACQ_prac6.c
 * Author: zem
 *
 * Created on 06-jun-2013, 18:10:41
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Simple C Test Suite
 */

int maze_columns = 50;
int wind_size;
int *ver_points;
int *hor_points;
int wind_size_x;
int wind_size_y;
int hor_point_number;
int ver_point_number;
int size;
int num_columns;

void test1() {

    wind_size_x = 600;
    wind_size_y = 600;
    hor_point_number = 0;
    ver_point_number = 0;
    num_columns = 40;
     
    size = GenerateParameters(num_columns);
    if(size < 0){
        printf("%%TEST_FAILED%% time=0 testname=test1 (test1) message=Error generating cells size\n");
    }
}

void test2() {
    printf("test1 test 2\n");
    
    double sq_size = 1;
    
    sq_size = PlotSquare(1, 1, sq_size);
    
    if (sq_size < 1){
        printf("%%TEST_FAILED%% time=0 testname=test2 (test1) message=Wrong square side size \n");
    }
}

void test3() {

    wind_size_x = 600;
    wind_size_y = 600;
    hor_point_number = 0;
    ver_point_number = 0;
    num_columns = 40;
    
    size = GenerateParameters(num_columns);
    if(size < 0){
        printf("%%TEST_FAILED%% time=0 testname=test3 (test3) message=Error with diferent proportions\n");
    }
}

void test4() {

    wind_size_x = 600;
    wind_size_y = 600;
    hor_point_number = 0;
    ver_point_number = 0;
    num_columns = 1;
     
    size = GenerateParameters(num_columns);
    if(hor_point_number != ver_point_number){
        printf("%%TEST_FAILED%% time=0 testname=test4 (test4) message=Diferent rows and columns\n");
    }
}

void test5() {

    wind_size_x = 1000000000;
    wind_size_y = 1000000000;
    hor_point_number = 0;
    ver_point_number = 0;
    num_columns = 10000;
     
    size = GenerateParameters(num_columns);
    if(size < 0){
        printf("%%TEST_FAILED%% time=0 testname=test5 (test5) message=Error with big numbers\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_ACQ_prac6\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (test_ACQ_prac6)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (test_ACQ_prac6) \n");

    printf("%%TEST_STARTED%% test2 (test_ACQ_prac6)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (test_ACQ_prac6) \n");
    
    printf("%%TEST_STARTED%% test3 (test_ACQ_prac6)\n");
    test3();
    printf("%%TEST_FINISHED%% time=0 test3 (test_ACQ_prac6) \n");
    
    printf("%%TEST_STARTED%% test4 (test_ACQ_prac6)\n");
    test4();
    printf("%%TEST_FINISHED%% time=0 test4 (test_ACQ_prac6) \n");

    printf("%%TEST_STARTED%% test5 (test_ACQ_prac6)\n");
    test5();
    printf("%%TEST_FINISHED%% time=0 test5 (test_ACQ_prac6) \n");

    
    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
