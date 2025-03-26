#include<stdio.h>

int ref_st[20], len_rs, frames[5][2], no_of_frames;
int page_fault = 0, tm = 0;

int searchpage(int p) {
    int i;
    for (i = 0; i < no_of_frames; i++) {
        if (p == frames[i][0]) {
            frames[i][1]++; // Increment frequency count for the page.
            return 0;
        }
    }
    return 1;
}

int LFU() {
    int i, min = 1000, ind = -1;
    for (i = 0; i < no_of_frames; i++) {
        if (frames[i][1] < min) { // Find page with the least frequency.
            min = frames[i][1];
            ind = i;
        }
    }
    return ind;
}

int findfreeframe() {
    int i;
    for (i = 0; i < no_of_frames; i++) {
        if (frames[i][0] == -2) { // Check for a free frame.
            return i;
        }
    }
    i = LFU(); // If no free frame, replace the least frequently used page.
    return i;
}

void display() {
    int i;
    for (i = 0; i < no_of_frames; i++) {
        if (frames[i][0] == -2) {
            printf(" - |");
        } else {
            printf(" %d |", frames[i][0]);
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
        frames[i][0] = -2; // Initialize frames to be empty.
        frames[i][1] = 0;  // Initialize frequency to 0.
    }

    for (i = 0; i < len_rs; i++) {
        display();
        s = searchpage(ref_st[i]);
        if (s == 1) { // Page fault occurs.
            page_fault++;
            ind = findfreeframe();
            frames[ind][0] = ref_st[i]; // Replace page.
            frames[ind][1] = 1;        // Reset frequency to 1.
        }
    }
    printf("\nTotal page faults are %d\n", page_fault);
    return 0;
}
