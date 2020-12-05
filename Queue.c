//Authors - Tomer Shinhar 205627524 Yael schwartz 206335010
//Project - Queue


//Description - this modul implemets the queue using linked list 
//with head being the first item in the queue
//the linked list is also used for other functionalitys in the project, 
//so some extra methodes are implemented


#include "Queue.h"
#include "utilities.h"


Node* create_new_node(int value) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (check_malloc(new_node) == 1)
		exit(EXIT_FAILURE);
	new_node->data = value;
	new_node->next = NULL;
	return new_node;
}


Node* initialize_queue(int value) {
	//creates a new queue by creating a node and returning it as the head of the queue
	Node* new_node = create_new_node(value);
	return new_node;
}


Node* push_to_beginning(Node* head, int value) {
	//adds a node to the head of the queue
	Node* new_node = create_new_node(value);
	new_node->next = head;
	return new_node;
}


void destroy_queue(Node* head) {
	//frees all nodes in the queue
	while (head != NULL) {
		Node* next_node = head->next;
		free(head);
		head = next_node;
	}
}


Node* push(Node* head, int value) {
	//creates a new node and addes it to the end of the queue
	Node* new_node = create_new_node(value);
	if (head == NULL)
		return new_node;
	Node* current_node = head;
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}
	current_node->next = new_node;
	return head;
}


Node* pop(Node* head) {
	// removes the first item from the queue
	if (head == NULL) {
		printf("Error - can't remove a node from an empty list\n");
	}
	Node* new_head = head->next;
	free(head);
	return new_head;
}


int top(Node* head) {
	//returns the first item in the queue
	return head->data;
}


int empty(Node* head) {
	//checks if the queue is empty
	if (head == NULL)
		return true;
	return false;
}


void print_list(Node* head) {
	//for debugging - prints the queue
	if (head == NULL) {
		printf("[]\n");
		return;
	}
	Node* current_node = head;
	printf("[");
	while (current_node->next != NULL) {
		printf("%d, ", current_node->data);
		current_node = current_node->next;
	}
	printf("%d]\n", current_node->data);
}