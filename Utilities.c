//Authors - Tomer Shinhar 205627524 Yael schwartz 206335010
//Project - Queue

//Description - this modul contains general utilities to be used by the other moduels of the project

#include "utilities.h"


int check_malloc(const void* pointer) {
	if (!pointer)
	{
		printf("ERROR - malloc failed\n");
		return 1;
	}
	return 0;
}


HANDLE create_file(char* file_path, char mode) {
	// this function creates a file and returns the handle, mode is indicating read or write
	HANDLE* hFile;
	if (mode == 'r') {
		hFile = CreateFileA(file_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else
		if (mode == 'w') {
			hFile = CreateFileA(file_path, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		else {
			printf("ERROR: not 'r' or 'w' for file");
			return NULL;
		}

	// Check for error
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("File not created. Error %u", GetLastError());
		return NULL;
	}
	return hFile;
}


void close_handles_of_threads(HANDLE* thread_handles, int num_of_threads)
{
	for (int i = 0; i < num_of_threads; i++)
	{
		CloseHandle(thread_handles[i]);
	}
}