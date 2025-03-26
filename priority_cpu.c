#include<stdio.h>
#include<string.h>

struct node {
    char pname[10];
    int at, bt, st, ct, tat, wt, priority;
};

int gantt_chart[10];

void accept(struct node a[], int n) {
    int i;
    printf("Enter Process Name, Arrival Time, Burst Time, and Priority:\n");
    for (i = 0; i < n; i++) {
        scanf("%s%d%d%d", &a[i].pname, &a[i].at, &a[i].bt, &a[i].priority);
    }
}

void sort(struct node a[], int n) {
    int i, j;
    struct node temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j].at > a[j + 1].at) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void priority_scheduling(struct node a[], int n) {
    int completed[10] = {0}, i, j = 0, ft = 0, n1 = 0, id = -1, highest_priority;

    while (n1 != n) {
        highest_priority = 1000; // Set to a very high value initially.

        // Find the process with the highest priority available at the current time.
        for (i = 0; i < n; i++) {
            if (completed[i] == 0 && a[i].at <= ft) {
                if (a[i].priority < highest_priority || 
                   (a[i].priority == highest_priority && a[i].at < a[id].at)) {
                    highest_priority = a[i].priority;
                    id = i;
                }
            }
        }

        if (id >= 0) {
            a[id].st = ft;
            a[id].ct = ft + a[id].bt;
            ft = a[id].ct;
            a[id].tat = a[id].ct - a[id].at;
            a[id].wt = a[id].tat - a[id].bt;
            completed[id] = 1;
            gantt_chart[j] = id;
            j++;
            n1++;
            id = -1; // Reset the selected process ID for the next iteration.
        } else {
            ft++; // If no process is available, increase the time.
        }
    }
}

void display(struct node a[], int n) {
    float sum_tat = 0, sum_wt = 0;
    int i;
    printf("\nTable\n\nProcess\tAT\tBT\tPriority\tST\tFT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n", 
               a[i].pname, a[i].at, a[i].bt, a[i].priority, 
               a[i].st, a[i].ct, a[i].tat, a[i].wt);
        sum_tat += a[i].tat;
        sum_wt += a[i].wt;
    }
    printf("\nAvg TAT=%f\nAvg WT=%f\n", sum_tat / n, sum_wt / n);

    printf("\nGantt Chart\n");
    for (i = 0; i < n; i++) {
        printf("%d| %s  |%d\n", a[gantt_chart[i]].st, a[gantt_chart[i]].pname, a[gantt_chart[i]].ct);
    }
}

int main() {
    struct node a[10];
    int n;
    printf("Enter how many processes: ");
    scanf("%d", &n);
    accept(a, n);
    sort(a, n);
    priority_scheduling(a, n);
    display(a, n);
    return 0;
}
