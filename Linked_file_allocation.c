#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct block {
    int block_number;
    struct block* next; // Pointer to the next block in the chain
};

struct file {
    char fname[10];
    int fsize;           // File size (number of blocks)
    struct block* start; // Starting block
};

struct file files[100];
int file_count = 0;
int memory[1000]; // Array representing disk memory
int n;            // Total number of blocks in the disk
int freeblocks;   // Number of free blocks

void initialize_memory() {
    for (int i = 0; i < n; i++) {
        memory[i] = 0; // Initialize all blocks to free
    }
    freeblocks = n;
}

void display_bit_vector() {
    printf("\nBit Vector:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

struct block* allocate_blocks(int size) {
    if (size > freeblocks) {
        printf("Not enough free memory available.\n");
        return NULL;
    }

    struct block* start = NULL;
    struct block* current = NULL;

    for (int i = 0; i < n && size > 0; i++) {
        if (memory[i] == 0) { // Find a free block
            struct block* new_block = (struct block*)malloc(sizeof(struct block));
            new_block->block_number = i;
            new_block->next = NULL;

            if (start == NULL) {
                start = new_block; // First block in the chain
            } else {
                current->next = new_block; // Link to the next block
            }

            current = new_block;
            memory[i] = 1; // Mark block as allocated
            freeblocks--;
            size--;
        }
    }

    return start;
}

void create_file() {
    char fname[10];
    int fsize;
    printf("Enter file name: ");
    scanf("%s", fname);
    printf("Enter file size (in blocks): ");
    scanf("%d", &fsize);

    struct block* start = allocate_blocks(fsize);
    if (start != NULL) {
        strcpy(files[file_count].fname, fname);
        files[file_count].fsize = fsize;
        files[file_count].start = start;
        file_count++;
        printf("File '%s' created successfully.\n", fname);
    }
}

void show_directory() {
    printf("\nDirectory:\n");
    printf("File Name\tFile Size\tAllocated Blocks\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\t\t%d\t\t", files[i].fname, files[i].fsize);
        struct block* current = files[i].start;
        while (current != NULL) {
            printf("%d -> ", current->block_number);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void delete_file() {
    char fname[10];
    printf("Enter the name of the file to delete: ");
    scanf("%s", fname);

    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].fname, fname) == 0) {
            struct block* current = files[i].start;
            while (current != NULL) {
                memory[current->block_number] = 0; // Mark block as free
                freeblocks++;
                struct block* temp = current;
                current = current->next;
                free(temp); // Free the block memory
            }
            printf("File '%s' deleted successfully.\n", files[i].fname);

            // Remove file from the directory
            for (int j = i; j < file_count - 1; j++) {
                files[j] = files[j + 1];
            }
            file_count--;
            return;
        }
    }

    printf("File not found.\n");
}

int main() {
    int ch;
    printf("Enter the number of blocks in the disk: ");
    scanf("%d", &n);

    initialize_memory();

    while (1) {
        printf("\nPress\n1. Bit Vector\n2. Create File\n3. Show Directory\n4. Delete File\n5. Exit\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                display_bit_vector();
                break;
            case 2:
                create_file();
                break;
            case 3:
                show_directory();
                break;
            case 4:
                delete_file();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
