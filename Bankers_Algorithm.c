/*1. Initialization:

The program declares variables for the number of processes (n), resources (m), available resources (available), allocation (allocation), maximum needs (max), need (need), process completion flag (finish), work vector (work), a temporary process sequence array (p), and auxiliary variables (i, j, k, flag, and y).
It prompts the user to enter the number of resource types, number of processes, and the number of available instances for each resource type. These values are stored in the available array and copied to the work vector.
The user is then prompted to enter the number of allocated instances for each process for each resource type. These values are stored in the allocation matrix.
Finally, the user is asked to enter the number of maximum instances each process can request for each resource type. These values are stored in the max matrix.
The finish array is initialized to all zeros, indicating no process has finished yet.
2. Calculate Need Matrix:

The program iterates through each process (i) and resource type (j) to calculate the need matrix.
The need for a process-resource pair is the difference between the maximum the process can request (max[i][j]) and what it currently holds (allocation[i][j]). This represents the remaining resources a process needs to finish.
3. Safety Check Algorithm:

This is the core of the Banker's Algorithm. It iterates through all processes multiple times to find a safe sequence.
Inside the outer loop (i < n):
The inner loop (j < n) iterates through each process.
For each process (j), it checks if it's unfinished (finish[j] == 0).
If unfinished, a flag variable is set to 0, assuming the process can finish in this iteration.
Another inner loop (k < m) iterates through each resource type.
Within this loop, it checks if the process's need for a resource (need[j][k]) is greater than the currently available resources (available[k]).
If a single resource need exceeds available resources, the flag is set to 1, indicating the process cannot finish yet.
After checking all resources, if the flag remains 0, it means the process can finish its execution because its needs are met by the current available resources.
If a process can finish (flag == 0):
The process ID (j) is added to a temporary sequence array (p).
The allocated resources for the finishing process are added back to the available resources pool (available). This simulates releasing resources after the process finishes.
The finish flag for the process is set to 1, indicating it's completed.
4. Print Safe Sequence (if found):

After iterating through all processes, the program checks if any processes finished (entries in p array).
If a safe sequence exists (processes finished), the program prints "Safe Sequence:" followed by the process IDs in the order they can finish execution without encountering a deadlock
*/

#include <stdio.h>
void main()
{
    int n, m, available[10], need[10][10], allocation[10][10], max[10][10], i, j, k, p[10], work[10], finish[10], index = 0, flag, y;
    printf("Enter number of Resource Types:");
    scanf("%d", &m);
    printf("\nEnter number of Processes:");
    scanf("%d", &n);
    printf("\nEnter number of instances of each Resource Type:");
    for (i = 0; i < m; i++)
    {
        printf("\nEnter number of instances of Resource Type %d:", i + 1);
        scanf("%d", &available[i]);
        work[i] = available[i];
    }
    printf("\nEnter number of Allocated instances for each Process:");
    for (i = 0; i < n; i++)
    {
        printf("\nProcess %d:", i + 1);
        for (j = 0; j < m; j++)
        {
            printf("\nResource Type %d:", j + 1);
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("\nEnter number of Maximum instances for each Process:");
    for (i = 0; i < n; i++)
    {
        printf("\nProcess %d:", i + 1);
        for (j = 0; j < m; j++)
        {
            printf("\nResource Type %d:", j + 1);
            scanf("%d", &max[i][j]);
        }
    }
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (finish[j] == 0)
            {
                flag = 0;
                for (k = 0; k < m; k++)
                {
                    if (need[j][k] > available[k])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    p[index++] = j;
                    for (y = 0; y < m; y++)
                    {
                        available[y] += allocation[j][y];
                    }
                    finish[j] = 1;
                }
            }
        }
    }
    printf("\nSafe Sequence:");
    for (i = 0; i < n - 1; i++)
    {
        printf("P%d->", p[i]);
    }
    printf("P%d", p[n - 1]);
}
