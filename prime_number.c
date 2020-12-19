#include "prime_number.h"


//the function gets an interger number and returns an array of its primery numbers (the array is arranged from the smallest number to the largest when having only one thread. if having multiple threads the is a need to call "arrange_primary_array")
int* create_prime_numbers_array(int number, int* array_size)
{
    int i = 0;
    int* prime_numbers_array = (int*)malloc((sizeof(int)));
    check_malloc(prime_numbers_array);
    // Check how many 2's divide the number and put them in the array
    while (number % 2 == 0)
    {
        prime_numbers_array = (int*)realloc(prime_numbers_array, ((i + 1) * sizeof(int)));// i+1 since i starts from 0, but allocation memory starts from 1
        check_realloc(prime_numbers_array);
        prime_numbers_array[i] = 2;
        i = ++i;//different than i++, since i++
        number = number / 2;
    }
    // n has to be an odd number at this point
    for (int j = 3; j <= sqrt(number); j = j + 2)
    {
        // While i divides n, print i and divide n  
        while (number % j == 0)
        {
            prime_numbers_array = (int*)realloc(prime_numbers_array, ((i + 1) * sizeof(int)));// i+1 since i starts from 0, but allocation memory starts from 1
            check_realloc(prime_numbers_array);
            prime_numbers_array[i] = j;
            i = ++i;//different than i++, since i++
            number = number / j;
        }
    }
    //if n=1- we have found all the prime numbers of "number", and are done
    //if the number is a prime number greater than 2  (if we got here, it doesn't have any 2's or any other prime numbers except for itself)
    if (number > 2)
    {
        prime_numbers_array = (int*)realloc(prime_numbers_array, ((i + 1) * sizeof(int)));// i+1 since i starts from 0, but allocation memory starts from 1
        check_realloc(prime_numbers_array);
        prime_numbers_array[i] = number;
        i = ++i;//different than i++, since i++
    }
    *array_size = i;
    return prime_numbers_array;
}

void sort_primary_array(int* prime_numbers_array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {

        for (int j = i + 1; j < array_size; j++)
        {

            if (prime_numbers_array[i] > prime_numbers_array[j])
            {

                int temp = prime_numbers_array[i];
                prime_numbers_array[i] = prime_numbers_array[j];
                prime_numbers_array[j] = temp;

            }

        }

    }
}

int write_output_file(HANDLE* hTarget, int number, int* prime_numbers_array, int array_size)
{
    char addition[PRIME_MAX_WIDTH + 2];// extra 2 chars for ", "
    char start_of_string[TEXT_LEN + PRIME_MAX_WIDTH];
    sprintf_s(start_of_string, sizeof(start_of_string), "The prime factors of %d are:", number);
    int line_size_in_bytes = (sizeof(start_of_string) + sizeof(addition) * (array_size)) * sizeof(char);
    char* output_string = (char*)malloc(line_size_in_bytes);//for some reason the sizeof(output_string) is allways 4, not matter what I do- as the warning says
    if (output_string)
    {
        //*output_string = '\0';//setting the first character to the null character will give an empty string:
        strcpy_s(output_string, line_size_in_bytes, start_of_string);//"The prime factors of [number] are: "
        for (int i = 0; i < array_size; i++)
        {
            if (i == array_size - 1)// if the number itself is primary or if it is the last number, it is the only thing that should be printed ('1' does not need to be printed)
            {
                sprintf_s(addition, sizeof(addition), " %d", prime_numbers_array[i]);
            }
            else
            {
                sprintf_s(addition, sizeof(addition), " %d,", prime_numbers_array[i]);
            }
            strcat_s(output_string, line_size_in_bytes, addition);
        }
        strcpy_s(addition, sizeof(addition), "\r\n");
        strcat_s(output_string, line_size_in_bytes, addition);
        if (FALSE == WriteFile(hTarget, output_string, line_size_in_bytes, NULL, NULL)){
            printf("Error writing to file");
            free(output_string);
            return EXIT_FAILURE;
        }
        free(output_string);
    }
    return 0;
}

int get_num_out_of_buff(char* buff)
{
    int buff_as_int = -1;
    for (int i = 0; i < sizeof(buff); i++)
    {
        if (buff[i] == '\r')
        {
            buff[i] = '\0';
            buff_as_int = atoi(buff);
            break;
        }
    }
    return buff_as_int;
}