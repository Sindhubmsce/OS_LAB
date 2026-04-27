#include <stdio.h>
#include <math.h>
#define MAX_TASKS 10

// Task structure
typedef struct {
    int id;
    int C;  // Execution time
    int T;  // Period
    int remaining_time;
    int next_arrival;
} Task;

// Step 1 & 2: Check schedulability
void check_schedulability(Task tasks[], int n) {
    double U = 0.0;

    for (int i = 0; i < n; i++) {
        U += (double)tasks[i].C / tasks[i].T;
    }

    double bound = n * (pow(2, 1.0/n) - 1);

    printf("CPU Utilization: %.4f\n", U);
    printf("RMS Bound: %.4f\n", bound);

    if (U <= bound) {
        printf("Schedulable using RMS\n\n");
    } else {
        printf("Not guaranteed schedulable (need further analysis)\n\n");
    }
}

// Step 4: Sort tasks by period (ascending)
void sort_tasks(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (tasks[i].T > tasks[j].T) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

// Step 5: RMS Scheduling simulation
void rms_schedule(Task tasks[], int n, int simulation_time) {
    int time = 0;

    printf("Scheduling Timeline:\n\n");

    while (time < simulation_time) {
        int highest = -1;

        // Check for task arrivals
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].C;
                tasks[i].next_arrival += tasks[i].T;
            }
        }

        // Select highest priority READY task
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                highest = i;
                break; // already sorted → first is highest priority
            }
        }

        if (highest != -1) {
            printf("Time %d: Executing T%d\n", time, tasks[highest].id);
            tasks[highest].remaining_time--;
        } else {
            printf("Time %d: Idle\n", time);
        }

        time++;
    }
}

int main() {
    int n = 3;

    Task tasks[MAX_TASKS] = {
        {1, 1, 4, 0, 0},   // T1
        {2, 2, 5, 0, 0},   // T2
        {3, 1, 10, 0, 0}   // T3
    };

    check_schedulability(tasks, n);

    sort_tasks(tasks, n);

    rms_schedule(tasks, n, 20);

    return 0;
}
