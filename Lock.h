#include "utilities.h"

typedef struct lock {
	HANDLE semaphore_signal;
	HANDLE mutex_block;
	int readers;
	HANDLE turnstile;
}Lock;

Lock* initialize_lock();

void destroy_lock(Lock* lock);

int read_lock(Lock* lock);

int release_read(Lock* lock);

int write_lock(Lock* lock);

int write_release(Lock* lock);
#pragma once

