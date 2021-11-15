/*
 ============================================================================
 Name        : CWK2Q3.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement your own Hash Table in C for storing and searching names, i.e. char
 arrays. In the event of collisions, you should use linear probing with an
 interval of 1. The hash function should be the sum of the ASCII values of the
 string modulo the size of the underlying data structure. Your Hash Table
 implementation should have the following interface:
	int hash_function(const char *key)
	void resize_map(int new_size)
	void add_to_map(const char *name)
	int remove_from_map(const char *name)
	int search_map(const char *name)
	void print_map()

 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** hash_map;  // this is where you should store your names
int mapSize;

int hash_function(const char *key) {
	int sum = 0;
	while (*key != '\0'){
		// add the ASCII value to the sum
		sum += *(key++);
	}
	return sum % mapSize;
}

void resize_map(int new_size) {
	if (hash_map){
		// realocate the memory to a bigger size
		hash_map = realloc(hash_map, new_size * sizeof(char*));
		for (int i=mapSize; i<new_size; i++){
			// new memory addresses init with NULL
			hash_map[i] = NULL;
		}
	} else {
		// allocate to memory first time
		hash_map = malloc(new_size * sizeof(char*));
		for (int i=0; i<new_size; i++){
			// init memory addresses with NULL
			hash_map[i] = NULL;
		}
	}
	mapSize = new_size;
}

void add_to_map(const char *name) {
	int hashCode = hash_function(name);

	// check if there is an entry in the hash map
	if(hash_map[hashCode] == NULL){
		// allocate memory for the string and copy the string into the hashmap
		hash_map[hashCode] = malloc(strlen(name)*sizeof(char));
		strcpy(hash_map[hashCode], name);
	} else if (strcmp(hash_map[hashCode],name) != 0){
		// spot is taken so keep iterating until it finds an empty spot
		int i = 0;
		while (hash_map[hashCode+i] != NULL){
			i++;
		}
		hash_map[hashCode+i] = malloc(strlen(name)*sizeof(char));
		strcpy(hash_map[hashCode+i], name);
	}
	
}

int remove_from_map(const char *name) {
	int hashCode = hash_function(name);
	int i=0;
	// iterate through hashmap from the key index
	while ((strcmp(hash_map[hashCode+i],name) != 0) && (hashCode+i < mapSize)){
		i++;
	}
	// found the value
	if (strcmp(hash_map[hashCode+i],name) == 0) {
		// free memory and the freed memory acts as a place holder
		free(hash_map[hashCode+i]);
		return 1;
	} else {
		return 0;
	}
}

int search_map(const char *name) {
	int hashCode = hash_function(name);

	int i=0;
	// iterate through hashmap from the key index untill it finds item or runs out of indices
	while ((hash_map[hashCode+i] != NULL) && (hashCode+i < mapSize)){
		if(strcmp(hash_map[hashCode+i],name) == 0){
			return 1;
		}
		i++;
	}
	return 0;
	
}

void print_map() {
	printf("Hash Map: ");
	for (int i=0; i<mapSize; i++){
		// print all non null values (prints placeholders as well)
		if (hash_map[i] != NULL){
			printf("[%s] ", hash_map[i]);
		}
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	char *stringOne = "#Hello world";
	char *stringTwo = "How are you?";
	char *stringThree = "Be the best you...!!";
	char *stringFour = "Be kind to yourself";
	char *stringFive = "Principles of Programming 2"; 

	resize_map(6);
	add_to_map(stringOne);
	add_to_map(stringTwo);
	add_to_map(stringOne);
	add_to_map(stringThree);
	add_to_map(stringFour);
	add_to_map(stringFive);
	print_map();
	int ret = search_map(stringOne);
	if(ret)
		printf("Found %s!\n", stringOne);
		
	remove_from_map(stringThree);

	ret = search_map(stringFive);
	if(ret)
		printf("Found %s!\n", stringFive);
	print_map();

	add_to_map(stringThree);
	print_map(); 

	return EXIT_SUCCESS;
}
