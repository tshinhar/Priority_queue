#include "utilities.h"
#include "Queue.h"
#include "Lock.h"
#include "prime_number.h"

#define BUFFER_SIZE 10
#define MAX_NUM_DIGITS 8

typedef struct {
	char* in_file_path;
	Node *queue;

} THREAD_ARGS;


int exec_missions(char* mission_file_path, int num_of_missions, int num_of_threads, Node* queue);
DWORD WINAPI exec_missions_thread(LPVOID lpParam);
#pragma once