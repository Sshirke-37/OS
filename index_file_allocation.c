#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file {
    char fname[10];
    int fsize;       // File size (number of blocks)
    int index_block; // Index block number
    int* blocks;     // Array of allocated blocks
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

int allocate_index_block(int size) {
    for (int i = 0; i < n; i++) {
        if (memory[i] == 0) { // Find a free block for the index block
            memory[i] = 1;    // Mark block as allocated
            freeblocks--;
            return i;
        }
    }
    printf("Not enough free memory available for index block.\n");
    return -1;
}

int* allocate_blocks(int size) {
    if (size > freeblocks) {
        printf("Not enough free memory available for file blocks.\n");
        return NULL;
    }

    int* allocated_blocks = (int*)malloc(size * sizeof(int));
    int count = 0;

    for (int i = 0; i < n && count < size; i++) {
        if (memory[i] == 0) { // Find free blocks for the file
            allocated_blocks[count++] = i;
            memory[i] = 1; // Mark block as allocated
            freeblocks--;
        }
    }

    if (count != size) {
        printf("Not enough free memory available.\n");
        free(allocated_blocks);
        return NULL;
    }

    return allocated_blocks;
}

void create_file() {
    char fname[10];
    int fsize;
    printf("Enter file name: ");
    scanf("%s", fname);
    printf("Enter file size (in blocks): ");
    scanf("%d", &fsize);

    int index_block = allocate_index_block(fsize);
    if (index_block == -1) {
        return;
    }

    int* blocks = allocate_blocks(fsize);
    if (blocks != NULL) {
        strcpy(files[file_count].fname, fname);
        files[file_count].fsize = fsize;
        files[file_count].index_block = index_block;
        files[file_count].blocks = blocks;
        file_count++;

        printf("File '%s' created successfully.\n", fname);
        printf("Index Block: %d\n", index_block);
        printf("Allocated Blocks: ");
        for (int i = 0; i < fsize; i++) {
            printf("%d ", blocks[i]);
        }
        printf("\n");
    } else {
        memory[index_block] = 0; // Free the index block if allocation fails
        freeblocks++;
    }
}

void show_directory() {
    printf("\nDirectory:\n");
    printf("File Name\tFile Size\tIndex Block\tAllocated Blocks\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\t\t%d\t\t%d\t\t", files[i].fname, files[i].fsize, files[i].index_block);
        for (int j = 0; j < files[i].fsize; j++) {
            printf("%d ", files[i].blocks[j]);
        }
        printf("\n");
    }
}

void delete_file() {
    char fname[10];
    printf("Enter the name of the file to delete: ");
    scanf("%s", fname);

    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].fname, fname) == 0) {
            // Free the blocks allocated to the file
            for (int j = 0; j < files[i].fsize; j++) {
                memory[files[i].blocks[j]] = 0; // Mark block as free
                freeblocks++;
            }
            free(files[i].blocks); // Free the allocated memory for blocks

            // Free the index block
            memory[files[i].index_block] = 0;
            freeblocks++;

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
