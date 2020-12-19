#include "file_accessing.h"


//global variables
Lock* lock;
HANDLE queue_access;


int exec_missions(char* mission_file_path, int num_of_missions, int num_of_threads, Node* queue)
{
    lock = initialize_lock();
    THREAD_ARGS thread_args;
    queue_access = CreateSemaphore(NULL, 1, 1, NULL);
    if (queue_access == NULL || lock == NULL){
        printf("Error creating locks");
        return EXIT_FAILURE;
    }
    HANDLE* thread_handles = (HANDLE*)(malloc(sizeof(HANDLE) * num_of_threads));
    if (check_malloc(thread_handles) != 0) {// there was an error with thread_handles
        destroy_lock(lock);
        CloseHandle(queue_access);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_of_threads; i++) {
        thread_args = (THREAD_ARGS){ .in_file_path = mission_file_path, .queue = queue };
        thread_handles[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)exec_missions_thread, &thread_args, 0, NULL);
        printf("thread %d created \n", i);
        if (thread_handles[i] == NULL) { // CreatThread failed
            printf("thread %d faild \n", i);
            close_handles_of_threads(thread_handles, num_of_threads);//closes each of the handles which are in the array "thread_handles" (could be that only one of the thread handles has failed, and the rest needs to be released)
            free(thread_handles);
            destroy_lock(lock);
            CloseHandle(queue_access);
            return EXIT_FAILURE;
        }
    }
    int wait_mul_objects = WaitForMultipleObjects(num_of_threads, thread_handles, true, TIMEOUT); // 20 seconds
    if (wait_mul_objects != WAIT_OBJECT_0)//if WaitForMultipleObjects failed
    {
        printf("wait failed faild\n");
        destroy_lock(lock);
        close_handles_of_threads(thread_handles, num_of_threads);//closes each of the handles which are in the array "thread_handles"
        free(thread_handles);
        CloseHandle(queue_access);
        return EXIT_FAILURE;
    }
    destroy_lock(lock);
    close_handles_of_threads(thread_handles, num_of_threads);//closes each of the handles which are in the array "thread_handles"
    CloseHandle(queue_access);
    free(thread_handles);
    return 0;
}



DWORD WINAPI exec_missions_thread(LPVOID lpParam)
{
    int array_of_prime_number_size;
    int* prime_numbers_array = NULL;

    THREAD_ARGS* thread_args;
    thread_args = (THREAD_ARGS*)lpParam;
    char* input_file_path = thread_args->in_file_path;
    char buff[BUFFER_SIZE];
    DWORD dwBytesRead;
    HANDLE source = NULL;
    while (!empty(thread_args->queue)) {
        //get offset from the queue
        int wait_obj = WaitForSingleObject(queue_access, 5000);// wait 5 seconds to get to the queue
        if (wait_obj != WAIT_OBJECT_0) {//if wait failed
            printf("Timeout wating for other threads");
            return EXIT_FAILURE;
        }
        int offset = top(thread_args->queue);
        thread_args->queue = pop(thread_args->queue);
        ReleaseSemaphore(queue_access, 1, NULL);
        //read from file with the given offset
        read_lock(lock);
        source = create_file(input_file_path, 'r');
        DWORD first_byte_pointer = SetFilePointer(source, offset, NULL, FILE_BEGIN);
        if (!ReadFile(source, buff, sizeof(buff), &dwBytesRead, NULL)) { //this is a simple read, we need to extract the line from it
            printf("Source file not read from. Error %u", GetLastError());
            CloseHandle(source);
            return EXIT_FAILURE;
        }
        printf("line read from file\n");
        CloseHandle(source);
        release_read(lock);

        int num_to_break = get_num_out_of_buff(buff);

        prime_numbers_array = create_prime_numbers_array(num_to_break, &array_of_prime_number_size);// create_prime_numbers_array function is in prime_number.c
        sort_primary_array(prime_numbers_array, array_of_prime_number_size);

        write_lock(lock);
        HANDLE output = create_file(input_file_path, 'a');
        first_byte_pointer = SetFilePointer(output, 0, NULL, FILE_END);
        if (0 != write_output_file(output, num_to_break, prime_numbers_array, array_of_prime_number_size)) {
            CloseHandle(output);
            free(prime_numbers_array);
            return EXIT_FAILURE;
        }
        printf("line was written to file\n");
        CloseHandle(output);
        write_release(lock);
        free(prime_numbers_array);
    }
    return 0;
}