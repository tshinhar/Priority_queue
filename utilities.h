#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

#include "Queue.h"


int check_malloc(const void* pointer);
HANDLE create_file(char* file_path, char mode);
void close_handles_of_threads(thread_handles, num_of_threads);
Node* file_to_queue(char* file_path, int num_of_lines);
#pragma once
