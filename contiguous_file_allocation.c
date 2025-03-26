#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct directory {
    char fname[10];
    int start, end, fsize;
};

struct directory files[100]; // Directory to store file info
int file_count = 0;

int main() {
    int n, memory[1000], i, j, ch, freeblocks, fs, new_block, first_free_block, allocated;
    printf("Enter how many blocks in disk: ");
    scanf("%d", &n);

    freeblocks = n;

    // Initialize memory blocks to 0 (free)
    for (i = 0; i < n; i++) {
        memory[i] = 0;
    }

    while (1) {
        printf("\nPress\n1. Bit Vector\n2. Create File\n3. Show Directory\n4. Delete File\n5. Exit\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: // Display Bit Vector
                printf("Bit Vector is:\n");
                for (i = 0; i < n; i++) {
                    printf("%d ", memory[i]);
                }
                printf("\n");
                break;

            case 2: // Create File
                printf("Enter file name: ");
                char fname[10];
                scanf("%s", fname);
                printf("Enter size of file (in blocks): ");
                scanf("%d", &fs);

                if (fs > freeblocks) {
                    printf("Not enough free memory available.\n");
                    break;
                }

                // Attempt to find a contiguous block of memory
                allocated = 0;
                for (i = 0; i <= n - fs; i++) {
                    for (j = i; j < i + fs; j++) {
                        if (memory[j] == 1) {
                            break;
                        }
                    }

                    if (j == i + fs) { // Found contiguous free blocks
                        first_free_block = i;
                        allocated = 1;
                        break;
                    }
                }

                if (allocated) {
                    printf("File allocation in progress...\n");

                    // Allocate memory for the file
                    for (i = first_free_block; i < first_free_block + fs; i++) {
                        memory[i] = 1;
                    }
                    freeblocks -= fs;

                    // Update directory
                    files[file_count].start = first_free_block;
                    files[file_count].end = first_free_block + fs - 1;
                    files[file_count].fsize = fs;
                    strcpy(files[file_count].fname, fname);
                    file_count++;

                    printf("File '%s' allocated from block %d to block %d.\n", fname, first_free_block, first_free_block + fs - 1);
                } else {
                    printf("Not enough contiguous memory available.\n");
                }
                break;

            case 3: // Show Directory
                printf("\nDirectory:\n");
                printf("File Name\tStart Block\tEnd Block\tSize\n");
                for (i = 0; i < file_count; i++) {
                    printf("%s\t\t%d\t\t%d\t\t%d\n", files[i].fname, files[i].start, files[i].end, files[i].fsize);
                }
                break;

            case 4: // Delete File
                printf("Enter the name of the file to delete: ");
                scanf("%s", fname);

                for (i = 0; i < file_count; i++) {
                    if (strcmp(files[i].fname, fname) == 0) {
                        // Free the blocks occupied by the file
                        for (j = files[i].start; j <= files[i].end; j++) {
                            memory[j] = 0;
                        }
                        freeblocks += files[i].fsize;

                        printf("File '%s' deleted successfully.\n", files[i].fname);

                        // Remove the file from the directory
                        for (j = i; j < file_count - 1; j++) {
                            files[j] = files[j + 1];
                        }
                        file_count--;
                        break;
                    }
                }

                if (i == file_count) {
                    printf("File not found.\n");
                }
                break;

            case 5: // Exit
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}



/*
Enter how many blocks in disk: 50

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 1
Bit Vector is:
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 2
Enter file name: abc.txt
Enter size of file (in blocks): 7
File allocation in progress...
File 'abc.txt' allocated from block 0 to block 6.

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 1
Bit Vector is:
1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 3

Directory:
File Name       Start Block     End Block       Size
abc.txt         0               6               7

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 2
Enter file name: nrc.txt
Enter size of file (in blocks): 20
File allocation in progress...
File 'nrc.txt' allocated from block 7 to block 26.

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 3

Directory:
File Name       Start Block     End Block       Size
abc.txt         0               6               7
nrc.txt         7               26              20

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 1
Bit Vector is:
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 4
Enter the name of the file to delete: abc.txt
File 'abc.txt' deleted successfully.

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 1
Bit Vector is:
0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 3

Directory:
File Name       Start Block     End Block       Size
nrc.txt         7               26              20

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 2
Enter file name: ram.txt
Enter size of file (in blocks): 3
File allocation in progress...
File 'ram.txt' allocated from block 0 to block 2.

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 1
Bit Vector is:
1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

Press
1. Bit Vector
2. Create File
3. Show Directory
4. Delete File
5. Exit
Enter your choice: 5
*/

