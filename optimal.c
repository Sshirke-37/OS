#include<stdio.h>

int ref_st[20], len_rs, frames[5], no_of_frames;
int page_fault = 0;

int searchpage(int p) {
    int i;
    for (i = 0; i < no_of_frames; i++) {
        if (frames[i] == p) {
            return 0; // Page is already in the frame.
        }
    }
    return 1; // Page fault.
}

int findReplacementIndex(int current) {
    int i, j, farthest = -1, ind = -1;
    int used[5] = {0}; // Track usage of pages in future references.

    for (i = 0; i < no_of_frames; i++) {
        used[i] = 0; // Reset usage tracking.
        for (j = current + 1; j < len_rs; j++) {
            if (frames[i] == ref_st[j]) {
                used[i] = j; // Store the future index of usage.
                break;
            }
        }
        if (used[i] == 0) { // If a page is never used in the future.
            return i;
        }
        if (used[i] > farthest) { // Find the farthest page in the future.
            farthest = used[i];
            ind = i;
        }
    }
    return ind; // Return the frame index to replace.
}

void display() {
    int i;
    for (i = 0; i < no_of_frames; i++) {
        if (frames[i] == -2) {
            printf(" - |"); // Empty frame.
        } else {
            printf(" %d |", frames[i]); // Display page in the frame.
        }
    }
    printf("\n");
}

int main() {
    int i, s, ind;

    printf("Enter length of Reference String: ");
    scanf("%d", &len_rs);
    printf("\nEnter Reference String:\n");
    for (i = 0; i < len_rs; i++) {
        scanf("%d", &ref_st[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    for (i = 0; i < no_of_frames; i++) {
        frames[i] = -2; // Initialize frames to be empty.
    }

    for (i = 0; i < len_rs; i++) {
        display();
        s = searchpage(ref_st[i]);
        if (s == 1) { // Page fault occurs.
            page_fault++;
            if (frames[no_of_frames - 1] == -2) { // Check for free frames.
                for (ind = 0; ind < no_of_frames; ind++) {
                    if (frames[ind] == -2) {
                        frames[ind] = ref_st[i]; // Assign page to free frame.
                        break;
                    }
                }
            } else {
                ind = findReplacementIndex(i); // Find optimal replacement index.
                frames[ind] = ref_st[i]; // Replace the frame.
            }
        }
    }
    printf("\nTotal page faults are %d\n", page_fault);
    return 0;
}
