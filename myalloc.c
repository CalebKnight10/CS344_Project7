// Caleb Knight
// CS 344
// Programming Exercise in C to write an allocator 

// gcc -Wall -Wextra -Wno-deprecated-declarations -o myalloc myalloc.c
// This ^ is what I used to compile in command line
// Already late so don't want to continue to waste time on makefile

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
	// int needed_space = PADDED_SIZE(size) + PADDED_SIZE(sizeof(struct block)) + 16;

	while(n != NULL){
		if(n -> size >= size && n -> in_use == 0){
			// if (n->size >= needed_space){
			// 	split_space(n, size);
			// }
			n->in_use = 1;
			return PTR_OFFSET(n, PADDED_SIZE(sizeof(struct block)));
		}
		n = n -> next;
	}
	return NULL;
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
