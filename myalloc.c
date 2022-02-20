// Caleb Knight
// CS 344
// Project 7
// Programming Exercise in C to write free nodes from allocation using previous
// project 6 myallocator() 

// gcc -Wall -Wextra -Wno-deprecated-declarations -o myalloc myalloc.c
// This ^ is what I used to compile in command line

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))


struct block *head = NULL;

struct block {
	struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
};

void *myalloc(int size)
{
	void *h = sbrk(1024);

	size_t padded_block_size = PADDED_SIZE(sizeof(struct block));

	if(head == NULL) {
		head = h;
		head -> next = NULL;
		head -> size = 1024 - padded_block_size;
		head -> in_use = 0;
	}
	struct block *n = head;

	while(n != NULL){
		if(n -> size >= size && n -> in_use == 0){
			split_space(n, size);
			n->in_use = 1;
			return PTR_OFFSET(n, PADDED_SIZE(sizeof(struct block)));
		}
		n = n -> next;
	}
	return NULL;
}

int required_space = PADDED_SIZE(bytes) + PADDED_SIZE(sizeof(struct block)) + 16;

void find_space(int bytes) 
{
	bytes = bytes + GET_PAD(bytes);
	while(n != NULL){
		if(n -> size >= bytes && n -> in_use == 0){
			split_space(n, bytes);
			n->in_use = 1;
			return PTR_OFFSET(n, PADDED_SIZE(sizeof(struct block)));
		}
		n = n -> next;
	}
	return NULL;
}



// Split_Space(current_node, requested_size):
    // If current_node big enough to split:
        // Add a new struct block with the remaining unused space
        // Wire it into the linked list

void split_space(struct block *n, int bytes)
{
	if (n -> size >= required_space){
		struct block *new_n = PTR_OFFSET(n, PADDED_SIZE(bytes) + PADDED_SIZE(sizeof(struct block))); // create new node
		new_n -> in_use = 0; // declare not in use
		new_n -> size = n->size - (PADDED_SIZE(bytes) + (PADDED_SIZE(sizeof(struct block)))); // declares start of new block
		new_n -> next = NULL; // set value of next to NULL
		n -> next = new_n; // make the next node new
		n -> size = PADDED_SIZE(bytes); // sets up next
	}
}

void print_data(void)
{
	struct block *b = head;

	if (b == NULL) {
		printf("[empty]\n");
		return;
	}

	while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        // printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
		printf("[%d,%s]", b->size, b->in_use? "used": "free");
		if (b -> next != NULL) {
			printf(" -> ");
		}

		b = b -> next;
	}

	printf("\n");
}

int main(void) {
	// void *p;

	// print_data();
	// p = myalloc(64);
	// print_data();

	void *p;

	print_data();
	p = myalloc(16);
	print_data();
	p = myalloc(16);
	printf("%p\n", p);
}
