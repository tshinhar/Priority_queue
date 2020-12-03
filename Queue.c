//Authors - Tomer Shinhar 205627524 Yael schwartz 206335010
//Project - Queue


//Description - this modul implemets the queue using linked list


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


Node* initialize_queue() {
	return create_new_node(NULL);
}


void destroy_queue(Node* head) {
	while (head != NULL) {
		Node* next_node = head->next;
		free(head);
		head = next_node;
	}
}


Node* push(Node* head, int value) {
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
	if (head == NULL) {
		printf("Error - can't remove a node from an empty list\n");
	}
	
	Node* new_head = head->next;
	free(head);
	return new_head;
	
}


int top(Node* head) {
	return head->data;
}


int empty(Node* head) {
	if (head == NULL)
		return true;
	return false;
}


void print_list(Node* head) {
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