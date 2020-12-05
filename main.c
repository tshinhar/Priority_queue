//Authors – Tomer Shinhar 205627524 Yael schwartz 206335010
//Project – Queue


#include "Queue.h"
#include "utilities.h"


int main(int argc, char* argv[]) {
	if (argc != 5) {
		printf("incorrect number of arguments");
		exit(-1);
	}
	int num_of_threads, num_of_tasks;
	num_of_threads = atoi(argv[4]);
	num_of_tasks = atoi(argv[3]);
	// load tasks file to the queue
	Node* head = file_to_queue(argv[2], num_of_tasks);
	return 0;
}