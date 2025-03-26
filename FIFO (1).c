#include<stdio.h>

int ref_st[20], len_rs, frames[5], no_of_frames;
int page_fault = 0, front = 0;

int searchpage(int p) {
    int i;
    for (i = 0; i < no_of_frames; i++) {
        if (frames[i] == p) {
            return 0; // Page found in the frames.
        }
    }
    return 1; // Page not found (page fault).
}

void display() {
    int i;
    for (i = 0; i < no_of_frames; i++) {
        if (frames[i] == -2) {
            printf(" - |"); // Empty frame.
        } else {
            printf(" %d |", frames[i]); // Display frame content.
        }
    }
    printf("\n");
}

int main() {
    int i, s;

    printf("Enter length of Reference String: ");
    scanf("%d", &len_rs);
    printf("\nEnter Reference String:\n");
    for (i = 0; i < len_rs; i++) {
        scanf("%d", &ref_st[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    for (i = 0; i < no_of_frames; i++) {
        frames[i] = -2; // Initialize frames as empty.
    }

    for (i = 0; i < len_rs; i++) {
        display();
        s = searchpage(ref_st[i]);
        if (s == 1) { // Page fault occurs.
            page_fault++;
            frames[front] = ref_st[i]; // Replace the oldest page.
            front = (front + 1) % no_of_frames; // Move to the next frame in a circular fashion.
        }
    }
    printf("\nTotal page faults are %d\n", page_fault);
    return 0;
}
