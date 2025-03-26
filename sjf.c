#include<stdio.h>

void main() {
    int n, total_tat = 0, total_wt = 0, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int proc[n], at[n], bt[n], tat[n], wt[n], ct[n];
    
    // Input process details
    for(i = 0; i < n; i++) {
        proc[i] = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d%d", &at[i], &bt[i]);
    }

    // Sort processes by burst time (SJF) then by arrival time if burst times are equal
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(bt[i] > bt[j] || (bt[i] == bt[j] && at[i] > at[j])) {
                // Swap burst times
                int temp = bt[j];
                bt[j] = bt[i];
                bt[i] = temp;
                
                // Swap arrival times
                temp = at[j];
                at[j] = at[i];
                at[i] = temp;
                
                // Swap corresponding processes
                temp = proc[j];
                proc[j] = proc[i];
                proc[i] = temp;
            }
        }
    }

    // Calculate completion, turnaround, and waiting times
    int time = 0;
    for(i = 0; i < n; i++) {
        time = (time < at[i]) ? at[i] : time; // Wait if the process hasn't arrived yet
        time += bt[i];
        ct[i] = time;
        tat[i] = ct[i] - at[i]; // TAT = CT - AT
        wt[i] = tat[i] - bt[i]; // WT = TAT - BT
        total_tat += tat[i];
        total_wt += (wt[i] < 0) ? 0 : wt[i]; // Avoid negative waiting time
    }

    // Display Gantt chart
    printf("Gantt chart: ");
    for(i = 0; i < n; i++) printf("P%d|", proc[i]);
    printf("\n");

    // Display completion times
    for(i = 0; i < n; i++) printf("%d|", ct[i]);
    printf("\n");

    // Display TAT and WT
    printf("Turnaround times of processes:\n");
    for(i = 0; i < n; i++) printf("%d|", tat[i]);
    printf("\nAverage TAT = %.2f\n", (double)total_tat / n);

    printf("Waiting times of processes:\n");
    for(i = 0; i < n; i++) printf("%d|", wt[i]);
    printf("\nAverage WT = %.2f\n", (double)total_wt / n);
}