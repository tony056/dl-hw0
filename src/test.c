#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "matrix.h"
#include "image.h"
#include "test.h"
#include "args.h"
#include <stdbool.h>

double what_time_is_it_now()
{
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

bool test_copy_matrix()
{
  matrix a = random_matrix(10, 10, 1);
  matrix c = copy_matrix(a);
  assert(c.rows == a.rows);
  assert(c.cols == a.cols);
  bool result = true;
  for (int i = 0; i < a.rows * a.cols; i++) {
    if (a.data[i] != c.data[i])
      result = false;
  }

  free_matrix(a);
  free_matrix(c);

  return result;
}

bool test_transpose_matrix()
{
  matrix a = random_matrix(5, 3, 1);
  matrix c = transpose_matrix(a);
  matrix r = transpose_matrix(c);
  assert(a.rows == r.rows);
  assert(a.cols == r.cols);
  for (int i = 0; i < a.rows * a.cols; i++){
    assert(a.data[i] == r.data[i]);
  }
  free_matrix(a);
  free_matrix(c);
  free_matrix(r);
}

void test_matrix_speed()
{
    int i;
    int n = 128;
    matrix a = random_matrix(512, 512, 1);
    matrix b = random_matrix(512, 512, 1);
    double start = what_time_is_it_now();
    for(i = 0; i < n; ++i){
        matrix d = matmul(a,b);
        free_matrix(d);
    }
    printf("Matmul elapsed %lf sec\n", what_time_is_it_now() - start);
    start = what_time_is_it_now();
    for(i = 0; i < n; ++i){
        matrix at = transpose_matrix(a);
        free_matrix(at);
    }
    printf("Transpose elapsed %lf sec\n", what_time_is_it_now() - start);
}

void run_tests()
{
    test_matrix_speed();
    assert(test_copy_matrix() == true);
    test_transpose_matrix();
    //printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
}
