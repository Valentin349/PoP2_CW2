/*
 ============================================================================
 Name        : CWK2Q4.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement your own XOR Linked List (https://en.wikipedia.org/wiki/XOR_linked_list)
 in C capable of storing names. Your implementation should have the following
 functions:
    void insert_string(const char* newObj)
	int insert_before(const char* before, const char* newObj)
	int insert_after(const char* after, const char* newObj)
	void remove_string(char* result)
	int remove_after(const char *after, char *result)
	int remove_before(const char *before, char *result)
    void print_list()

 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char* data;
	struct Node* link;
};

struct Node* head;

struct Node* XOR (struct Node *a, struct Node *b)
{
    return (struct Node*) ((uintptr_t)a ^ (uintptr_t)b);
}

void insert_string(const char* newObj){
	// allocate memory for the data entry
	struct Node* node = malloc(sizeof(struct Node));
	node->data = malloc(sizeof(char)*strlen(newObj));
	strcpy(node->data, newObj); 
	// set the node pointer to start of the linked list
	node->link = head;
	if (head != NULL){
		// if linked list has an entry
		head->link = XOR(node, head->link);
	}
	head = node;

}


int insert_before(const char* before, const char* newObj){
	// if the linked list is not empty
	if (head != NULL){
		struct Node* curr = head;
		struct Node* prev = NULL;
		struct Node* next = XOR(prev, curr->link);

		while (next != NULL){
			if (strcmp(next->data, before) == 0){
				struct Node* node = malloc(sizeof(struct Node));
				// store XOR or prev and new node
				curr->link = XOR(XOR(curr->link, next), node);
				// update pointer of next node
				next->link = XOR(XOR(next->link, curr), node);
				// allocate memory and write a string to it.
				node->data = malloc(sizeof(char)*strlen(newObj));
				strcpy(node->data, newObj);
				node->link = XOR(curr, next);
				return 1;
			}
			// iterate thorugh the addresses of the next entries of the linked list
			prev = curr;
			curr = next;
			next = XOR(prev, curr->link);
		}
	}
	return 0;
}


int insert_after(const char* after, const char* newObj) {
	// if the linked list is not empty
	if (head != NULL){
		struct Node* curr = head;
		struct Node* prev = NULL;
		struct Node* next = XOR(prev, curr->link);


		while (curr != NULL){
			if (strcmp(curr->data, after) == 0){
				struct Node* node = malloc(sizeof(struct Node));
				// store XOR or prev and new node
				curr->link = XOR(XOR(curr->link, next), node);
				// update pointer of next node
				next->link = XOR(XOR(next->link, curr), node);
				
				node->data = malloc(sizeof(char)*strlen(newObj));
				strcpy(node->data, newObj);
				node->link = XOR(curr, next);
				return 1;
			}
			prev = curr;
			curr = next;
			next = XOR(prev, curr->link);
		}
	}

	return 0;
}


int remove_string(char* result){
	if (head == NULL){
		return 0;
	} else {
		struct Node* node = head;
		head = XOR(NULL, node->link);
		// linked list has entries
		if (head != NULL){
			// XOR 0^A
			head->link = XOR(NULL, XOR(head->link, node));
		}
		// write to result and free the memory used for the entry
		strcpy(result, node->data);
		free(node);
		return 1;
	}
}


int remove_after(const char *after, char *result){
	if (head != NULL){
		struct Node* curr = head;
		struct Node* prev = NULL;
		struct Node* next = XOR(prev, curr->link);


		while (curr != NULL){
			next = XOR(prev, curr->link);
			// if the current entry is the entry we need
			if (strcmp(curr->data, after) == 0){
				// one more iteration so that curr becomes next
				prev = curr;
				curr = next;
				next = XOR(prev, curr->link);

				// link pointers of prev and next
				prev->link = XOR(next, XOR(curr, prev->link));
				next->link = XOR(prev, XOR(curr, next->link));
				strcpy(result, curr->data);
				free(curr);
				return 1;
			}
			// else iterate through the next entries
			prev = curr;
			curr = next;
		}
	}

	return 0;
}


int remove_before(const char *before, char *result) {
	if (head != NULL){
		struct Node* curr = head;
		struct Node* prev = NULL;
		struct Node* next = XOR(prev, curr->link);


		while (curr != NULL){
			next = XOR(prev, curr->link);
			// if current entry is the one we look for
			if (strcmp(curr->data, before) == 0){
				// link pointers of prev and next
				prev->link = XOR(next, XOR(curr, prev->link));
				next->link = XOR(prev, XOR(curr, next->link));
				// write and the free the memory address
				strcpy(result, curr->data);
				free(curr);
				return 1;
			}
			prev = curr;
			curr = next;
		}
	}

	return 0;
}

void print_list(){
	struct Node *curr = head;
    struct Node *prev = NULL;
    struct Node *next;

	while (curr != NULL){
		next = XOR(prev, curr->link);
		// if not the last entry
		if (next != NULL){
			printf("%s -> ", curr->data);
		} else {
			printf("%s\n", curr->data);
		}
		prev = curr;
		curr = next;
	}
}

int main(int argc, char *argv[]) {

	insert_string("Alpha");
	insert_string("Bravo");
	insert_string("Charlie");
	insert_after("Bravo", "Delta");
	insert_before("Alpha", "Echo");
	print_list(); // Charlie -> Bravo -> Delta -> Echo -> Alpha

	char result[10];
	int ret;

	ret = remove_after("Delta",result);
	if(ret)
		printf("Removed: %s\n", result);

	ret = remove_before("Bravo", result);
	if(ret)
		printf("Removed: %s\n", result);

	ret = remove_string(result);
	if(ret)
		printf("Removed: %s\n", result);
		
	print_list();
}
