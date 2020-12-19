#include <math.h>
#include "utilities.h"


#define PRIME_MAX_WIDTH 12 //all numbers that are representable by int will fit in a 12-char-array without overflow unless our compiler is somehow using more than 32-bits for int (the maximum number of 99,999,999 is below 2^32)
#define TEXT_LEN 26

int* create_prime_numbers_array(int number, int* array_size);
void sort_primary_array(int* prime_numbers_array, int array_size);
int write_output_file(HANDLE* hTarget, int number, int* prime_numbers_array, int array_size);
int get_num_out_of_buff(char* buff);
#pragma once