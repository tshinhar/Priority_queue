#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>


#define EXTRA_CHARS 20


int check_malloc(const void* pointer);
HANDLE create_file(char* file_path, char mode);
void close_handles_of_threads(thread_handles, num_of_threads);
#pragma once
