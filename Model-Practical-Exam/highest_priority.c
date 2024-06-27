#include <stdio.h>

typedef struct {
    int id;
    int priority;
} Process;

Process processes[] = {
    {1, 3},
    {2, 1},
    {3, 2},
    {4, 5},
    {5, 4}
};

Process* find_highest_priority_process() {
    Process* highest = &processes[0];
    for (int i = 1; i < sizeof(processes) / sizeof(Process); i++) {
        if (processes[i].priority > highest->priority) {
            highest = &processes[i];
        }
    }
    return highest;
}

int main() {
    Process* next_process = find_highest_priority_process();

    printf("Executing process %d with priority %d\n", next_process->id, next_process->priority);

    return 0;
}