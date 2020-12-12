//Authors - Tomer Shinhar 205627524 Yael schwartz 206335010
//Project - Lock


//Description - this modul implemets the lock 
//the lock uses two mutexes one semaphore and the number of threads


#include "Lock.h"


#define TIMEOUT 5000


Lock* initialize_lock() {
	Lock* new_lock = (Lock*)malloc(sizeof(Lock));
	if (check_malloc(new_lock) == 1)
		return NULL;
	new_lock->readers = 0;
	new_lock->semaphore_signal = CreateSemaphore(NULL, 1, 1, NULL);
	if (new_lock->semaphore_signal == NULL) {
		destroy_lock(new_lock);
		return NULL;
	}
	new_lock->mutex_block = CreateMutex(NULL, FALSE, NULL);
	if (new_lock->mutex_block == NULL) {
		destroy_lock(new_lock);
		return NULL;
	}
	new_lock->turnstile = CreateMutex(NULL, FALSE, NULL);
	if (new_lock->turnstile == NULL) {
		destroy_lock(new_lock);
		return NULL;
	}
	return new_lock;
}


void destroy_lock(Lock* lock){
	if (lock->semaphore_signal != NULL)
		CloseHandle(lock->semaphore_signal);
	if (lock->mutex_block != NULL)
		CloseHandle(lock->mutex_block);
	if (lock->turnstile != NULL)
		CloseHandle(lock->turnstile);
	free(lock);
}


int read_lock(Lock* lock) {
	if (WaitForSingleObject(lock->turnstile, TIMEOUT) != WAIT_OBJECT_0) {
		printf("wait failed\n");
		return EXIT_FAILURE;
	}
	if (ReleaseMutex(lock->turnstile) == FALSE) {
		printf("Error releasing\n");
		return EXIT_FAILURE;
	}
	//lock the access of the semaphore
	if (WaitForSingleObject(lock->mutex_block, TIMEOUT) != WAIT_OBJECT_0) {
		printf("wait failed\n");
		return EXIT_FAILURE;
	}
	lock->readers++;
	if(lock->readers == 1)//indicte that someone is reading - we can't write
		if (WaitForSingleObject(lock->semaphore_signal, TIMEOUT) != WAIT_OBJECT_0) {
			printf("wait failed\n");
			return EXIT_FAILURE;
		}
	if (ReleaseMutex(lock->mutex_block) == FALSE) {
		printf("Error releasing\n");
		return EXIT_FAILURE;
	}
	return 0;
}


int release_read(Lock* lock) {
	//lock threades for updating semaphore
		//lock the access of the semaphore
	if (WaitForSingleObject(lock->mutex_block, TIMEOUT) != WAIT_OBJECT_0) {
		printf("wait failed\n");
		return EXIT_FAILURE;
	}
	lock->readers--;
	if (lock->readers == 0)//no readers, write can take place
		if (ReleaseSemaphore(lock->semaphore_signal, 1, NULL) == FALSE) {
			printf("Error releasing\n");
			return EXIT_FAILURE;
		}
	if (ReleaseMutex(lock->mutex_block) == FALSE) {
		printf("Error releasing\n");
		return EXIT_FAILURE;
	}
	return 0;
}


int write_lock(Lock* lock) {
	//lock read out 
	if (WaitForSingleObject(lock->turnstile, TIMEOUT) != WAIT_OBJECT_0) {
		printf("wait failed\n");
		return EXIT_FAILURE;
	}
	//wait for all readers to finish
	if (WaitForSingleObject(lock->semaphore_signal, TIMEOUT) != WAIT_OBJECT_0) {
		printf("wait failed\n");
		return EXIT_FAILURE;
	}
	return 0;
}

int write_release(Lock* lock) {
	//open so readers can enter
	if (ReleaseMutex(lock->turnstile) == FALSE) {
		printf("Error releasing\n");
		return EXIT_FAILURE;
	}
	if (ReleaseSemaphore(lock->semaphore_signal, 1, NULL) == FALSE) {
		printf("Error releasing\n");
		return EXIT_FAILURE;
	}
	return 0;
}