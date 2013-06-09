/*
 * File:   test1.c
 * Author: zem
 *
 * Created on 05-jun-2013, 17:47:30
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

void test1() {
    
    wind_size = 600;
    wind_size_x = 600;
    wind_size_y = 600;
    hor_point_number = 0;
    ver_point_number = 0;
     
    size = GenerateParameters(40);
    if(size > 0){
        printf("%%TEST_FAILED%% time=0 testname=test2 (test1) message=error message sample\n");
    }
}

void test2() {
    printf("test1 test 2\n");
    
    int sq_size;
    
    sq_size = PlotSquare(1, 1, 2);
    
    if (sq_size == 1){
        printf("%%TEST_FAILED%% time=0 testname=test2 (test1) message=error message sample\n");
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test1\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (test1)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (test1) \n");

    printf("%%TEST_STARTED%% test2 (test1)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (test1) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
