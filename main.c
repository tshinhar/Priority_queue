//Authors – Tomer Shinhar 205627524 Yael schwartz 206335010
//Project – Queue


#include "Queue.h"
#include "utilities.h"
#include "file_accessing.h"


int main(int argc, char* argv[]) {
	if (argc != 5) {
		printf("incorrect number of arguments");
		exit(-1);
	}
	char *mission_file_path, *priority_file;
	int num_of_threads, num_of_tasks, status;
	mission_file_path = argv[1];
	priority_file = argv[2];
	num_of_threads = atoi(argv[4]);
	num_of_tasks = atoi(argv[3]);
	// load tasks file to the queue
	Node* queue = file_to_queue(argv[2]);
	// call function to create threads and execute
	status = exec_missions(mission_file_path, num_of_tasks, num_of_threads, queue);
	if (status == 1) { // there was an issue
		printf("had an issue executing the missions");
		destroy_queue(queue);// if everything is working fine queue is freed by the threads
	}
	return status;
}