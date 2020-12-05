#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int data;
	struct node* next;
}Node;

Node* initialize_queue(int value);

void destroy_queue(Node* head);

Node* push(Node* head, int value);

Node* push_to_beginning(Node* head, int value);

Node* pop(Node* head);

int top(Node* head);

int empty(Node* head);

void print_list(Node* head);
#pragma once
