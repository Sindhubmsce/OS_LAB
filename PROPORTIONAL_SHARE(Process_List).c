

#include <stdio.h>
#define MAX 10
#define TIME_QUANTUM 10

typedef struct {
    int id;
    int arrival;
    int burst;
    int remaining;
    int weight;
    int completed;
} Process;

void proportional_share(Process p[], int n) {
    int total_weight = 0;
    int completed_count = 0;
    int t = 0;


    for (int i = 0; i < n; i++) {
        total_weight += p[i].weight;
    }

    printf("\nExecution Timeline:\n\n");

    // Step 4
    while (completed_count < n) {

        int executed_any = 0;

        // Step 5
        for (int i = 0; i < n; i++) {

            if (p[i].arrival <= t && p[i].completed == 0) {

                executed_any = 1;

                int time_slice = (p[i].weight * TIME_QUANTUM) / total_weight;

                if (time_slice <= 0)
                    time_slice = 1;

                printf("Time %d: Running P%d for %d units\n", t, p[i].id, time_slice);

                // Step 9–10
                if (p[i].remaining <= time_slice) {
                    t += p[i].remaining;
                    p[i].remaining = 0;
                } else {
                    p[i].remaining -= time_slice;
                    t += time_slice;
                }


                if (p[i].remaining == 0 && p[i].completed == 0) {
                    p[i].completed = 1;
                    completed_count++;
                    total_weight -= p[i].weight;

                    printf("P%d completed at time %d\n", p[i].id, t);
                }
            }
        }

        if (!executed_any) {
            printf("Time %d: Idle\n", t);
            t++;
        }
    }
}

int main() {
    int n;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Weight: ");
        scanf("%d", &p[i].weight);

        p[i].remaining = p[i].burst;
        p[i].completed = 0;
    }

    proportional_share(p, n);

    return 0;
}
