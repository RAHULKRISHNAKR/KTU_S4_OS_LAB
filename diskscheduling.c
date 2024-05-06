/*Here's the explanation of each function in the provided code:

*isort(int arr[], int n, int dir)*

This function implements the insertion sort algorithm to sort the given array arr of size n in either ascending (dir = 1) or descending (dir = -1) order. 

*Algorithm:*

1. Start with the second element (i = 1).
2. Compare the current element (arr[i]) with the previous element (arr[i-1]).
3. If the current element is smaller than the previous element in ascending order or larger in descending order:
    - Shift the larger elements one position to the right.
    - Insert the current element in its correct position.
4. Repeat steps 2 and 3 for all remaining elements.

*fCFS(int head, int n, int arr[30])*

This function implements the First Come First Serve (FCFS) disk scheduling algorithm. It processes the requests in the order they arrive, without considering their location.

*Algorithm:*

1. Print the initial head position and the first request.
2. Calculate the seek time between the head and the current request.
3. Iterate through all remaining requests:
    - Calculate the seek time between the previous request and the current request.
    - Print the current request.
4. Print the total seek time.

*sSTF(int head, int n, int arr[30])*

This function implements the Shortest Seek Time First (SSTF) disk scheduling algorithm. It prioritizes the request with the shortest seek time from the current head position.

*Algorithm:*

1. Create a processed array to track serviced requests.
2. Print the initial head position.
3. Iterate for n times (number of requests):
    - Find the request with the minimum seek time from the head position that hasn't been processed yet.
    - Print the request.
    - Update the head position and mark the request as processed.
4. Print the total seek time.

*scan(int head, int n, int arr[30])*

This function implements the SCAN (Elevator) disk scheduling algorithm. It serves requests in one direction until it reaches the end of the disk, then reverses direction and serves requests in the opposite direction.

*Algorithm:*

1. Ask for the disk size and previous head position.
2. Determine the initial direction based on the previous head position.
3. Create two arrays: ar1 for requests greater than the head and ar2 for requests less than the head.
4. Sort ar1 in descending order and ar2 in ascending order.
5. Initialize the total seek time (ans).
6. Print the initial head position.
7. If the direction is negative (moving towards the beginning):
    - Process requests in ar2 from the end to the beginning, updating the head position and calculating seek time.
    - Process requests in ar1 from beginning to end, updating the head position and calculating seek time.
8. Else (direction is positive):
    - Process requests in ar1 from beginning to end, updating the head position and calculating seek time.
    - Process requests in ar2 from end to the beginning, updating the head position and calculating seek time.
9. Print the total seek time.

*cscan(int head, int n, int arr[30])*

This function implements the Circular SCAN (C-SCAN) disk scheduling algorithm. It is similar to SCAN but treats the disk as a circular track, meaning the head immediately jumps to the beginning of the disk after reaching the end.

*Algorithm:*

1. Similar to SCAN, ask for disk size and previous head position.
2. Determine the initial direction.
3. Create two arrays: ar1 for requests greater than the head and ar2 for requests less than the head.
4. Sort ar1 in descending order and ar2 in ascending order.
5. Initialize the total seek time (ans).
6. Print the initial head position.
7. If the direction is negative:
    - Process requests in ar2 from the end to the beginning, updating the head position and calculating seek time.
    - Jump to the beginning of the disk and process requests in ar1 from beginning to end, updating the head position and calculating seek time.
8. Else (direction is positive):
    - Process requests in ar1 from beginning to end, updating the head position and calculating seek time.
    - Jump to the beginning of the disk and process requests in ar2 from end to the beginning, updating the head position and calculating seek time.
9. Print the total seek time.

*look(int head, int n, int arr[30])*

This function implements the LOOK algorithm, which is similar to SCAN but only serves requests in the current direction until there are no more requests in that direction.

*Algorithm:*

1. Similar to SCAN, ask for the previous head position.
2. Determine the initial direction.
3. Create two arrays: ar1 for requests greater than the head and ar2 for requests less than the head.
4. Sort ar1 in descending order and ar2 in ascending order.
5. Initialize the total seek time (ans).
6. Print the initial head position.
7. If the direction is negative:
    - Process requests in ar2 from the end until there are no more requests in that direction, updating the head position and calculating seek time.
    - Process requests in ar1 from beginning to end, updating the head position and calculating seek time.
8. Else (direction is positive):
    - Process requests in ar1 from beginning until there are no more requests in that direction, updating the head position and calculating seek time.
    - Process requests in ar2 from end to beginning, updating the head position and calculating seek time.
9. Print the total seek time.

*clook(int head, int n, int arr[30])*

This function implements the C-LOOK algorithm, which is a variant of LOOK that treats the disk as circular. After serving requests in one direction, it immediately jumps to the other end of the disk instead of going all the way back.

*Algorithm:*

1. Similar to LOOK, ask for the previous head position.
2. Determine the initial direction.
3. Create two arrays: ar1 for requests greater than the head and ar2 for requests less than the head.
4. Sort ar1 in descending order and ar2 in ascending order.
5. Initialize the total seek time (ans).
6. Print the initial head position.
7. If the direction is negative:
    - Process requests in ar2 from the end until there are no more requests in that direction, updating the head position and calculating seek time.
    - Jump to the end of the disk and process requests in ar1 from beginning to end, updating the head position and calculating seek time.
8. Else (direction is positive):
    - Process requests in ar1 from beginning until there are no more requests in that direction, updating the head position and calculating seek time.
    - Jump to the end of the disk and process requests in ar2 from end to beginning, updating the head position and calculating seek time.
9. Print the total seek time.

*main()*

This function is the main driver of the program. It:

1. Prints the menu of disk scheduling algorithms.
2. Gets the initial head position and number of requests from the user.
3. Gets the request positions from the user.
4. Presents a menu of options to choose the desired disk scheduling algorithm.
5. Based on the user's choice, it calls the corresponding function (fCFS, sSTF, scan, cscan, look, or clook) to calculate and print the seek time for that algorithm.
6. Allows the user to exit the program.*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void isort(int arr[], int n, int dir)
{
    int i, key, j;
    if (dir == 1)
    {
        for (i = 1; i < n; i++)
        {
            key = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
    else
    {
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                if (arr[j] < arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

void fCFS(int head, int n, int arr[30])
{
    printf("Order = %d %d ", head, arr[0]);
    int time = abs(arr[0] - head);
    for (int i = 1; i < n; i++)
    {
        time += abs(arr[i] - arr[i - 1]);
        printf("%d ", arr[i]);
    }
    printf("\nSeek Time = %d\n\n", time);
}

void sSTF(int head, int n, int arr[30])
{
    int processed[30] = {0};
    printf("Order = %d ", head);
    int time = 0;
    for (int count = 0; count < n; ++count)
    {
        int minDist = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < n; ++i)
        {
            if (!processed[i] && abs(arr[i] - head) < minDist)
            {
                minIndex = i;
                minDist = abs(arr[i] - head);
            }
        }
        if (minIndex == -1)
            break;
        printf("%d ", arr[minIndex]);
        time += minDist;
        head = arr[minIndex];
        processed[minIndex] = 1;
    }
    printf("\nSeek Time = %d\n", time);
}

void scan(int head, int n, int arr[30])
{
    int dir = 1;
    int siz, prev;
    printf("Enter the Size:");
    scanf("%d", &siz);
    printf("\nEnter the previous position...\n");
    scanf("%d", &prev);
    if (prev > head)
        dir = -1;

    int ar1[30], ar2[30], n1 = 0, n2 = 0;
     if(dir==1)
    {ar1[0] =siz -1;
    n1 = 1;}
    else
    {ar2[0] = 0;
    n2 = 1;}
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > head)
        {
            ar1[n1++] = arr[i];
        }
        else
        {
            ar2[n2++] = arr[i];
        }
    }
    isort(ar1, n1, -1);
    isort(ar2, n2, 1);

    int ans = 0;
    printf("SCAN ORDER IS:\n");
    n2--;
    n1--;
    printf("%d ", head);
    if (dir == -1)
    {
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        ans += head - 0; 
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        printf("\n");
        printf("Seek Time = %d\n\n", ans);
    }
    else
    {
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        ans += siz - head;
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        printf("\n");
        printf("Seek Time = %d\n\n", ans-1);
    }
}


void cscan(int head, int n, int arr[30])
{
    int dir = 1, siz, prev;
    printf("Enter the Size:");
    scanf("%d", &siz);
    printf("\nEnter the previous position...\n");
    scanf("%d", &prev);
    if (prev > head)
        dir = -1;

    int ar1[30], ar2[30], n1 = 0, n2 = 0;
    ar1[0] = siz - 1;
    n1 = 1;
    ar2[0] = 0;
    n2 = 1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > head)
        {
            ar1[n1++] = arr[i];
        }
        else
        {
            ar2[n2++] = arr[i];
        }
    }
    isort(ar1, n1, -1);
    isort(ar2, n2, 1);

    int ans = 0;
    printf("CSCAN ORDER IS:\n");
    printf("%d ", head);
    if (dir == -1)
    {
        n2--;
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        for (int i = 0; i < n1; i++)
        {
            ans += abs(head - ar1[i]);
            printf("%d ", ar1[i]);
            head = ar1[i];
        }
    }
    else
    {
        n1--;
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        for (int i = 0; i < n2; i++)
        {
            ans += abs(head - ar2[i]);
            printf("%d ", ar2[i]);
            head = ar2[i];
        }
    }
    printf("\n");
    printf("Seek Time = %d\n\n", ans);
}

void look(int head, int n, int arr[30])
{
    int dir = 1, prev;
    printf("\nEnter the previous position...\n");
    scanf("%d", &prev);
    if (prev > head)
        dir = -1;

    int ar1[30], ar2[30], n1 = 0, n2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > head)
        {
            ar1[n1++] = arr[i];
        }
        else
        {
            ar2[n2++] = arr[i];
        }
    }
    isort(ar1, n1, -1);
    isort(ar2, n2, 1);

    int ans = 0;
    printf("LOOK ORDER IS:\n");
    n2--;
    n1--;
    printf("%d ", head);
    if (dir == -1)
    {
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
    }
    else
    {
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
    }
    printf("\n");
    printf("Seek Time: %d\n\n", ans);
}

void clook(int head, int n, int arr[30])
{
    int dir = 1, prev;
    printf("\nEnter the previous position...\n");
    scanf("%d", &prev);
    if (prev > head)
        dir = -1;

    int ar1[30], ar2[30], n1 = 0, n2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > head)
        {
            ar1[n1++] = arr[i];
        }
        else
        {
            ar2[n2++] = arr[i];
        }
    }
    isort(ar1, n1, -1);
    isort(ar2, n2, 1);

    int ans = 0;
    printf("CLOOK ORDER IS:\n");
    printf("%d ", head);
    if (dir == -1)
    {
        n2--;
        while (n2 >= 0)
        {
            ans += abs(head - ar2[n2]);
            printf("%d ", ar2[n2]);
            head = ar2[n2--];
        }
        for (int i = 0; i < n1; i++)
        {
            ans += abs(head - ar1[i]);
            printf("%d ", ar1[i]);
            head = ar1[i];
        }
    }
    else
    {
        n1--;
        while (n1 >= 0)
        {
            ans += abs(head - ar1[n1]);
            printf("%d ", ar1[n1]);
            head = ar1[n1--];
        }
        for (int i = 0; i < n2; i++)
        {
            ans += abs(head - ar2[i]);
            printf("%d ", ar2[i]);
            head = ar2[i];
        }
    }
    printf("\n");
    printf("Seek Time = %d\n\n", ans);
}

int main()
{
    int head, n;
    int arr[30];
    printf("DISK SCHEDULING ALGORITHMS\n\n");
    printf("Enter the current position...\n");
    scanf("%d", &head);
    printf("Enter the number of requests...\n");
    scanf("%d", &n);
    printf("Enter the requests...\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int op = 0;
    while (op != 7)
    {
        printf("\n\nEnter your option...\n1. FCFS\n2. SSTF\n3. SCAN\n4. CSCAN\n5. LOOK\n6. CLOOK\n7. Exit\n\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            fCFS(head, n, arr);
            break;
        case 2:
            sSTF(head, n, arr);
            break;
        case 3:
            scan(head, n, arr);
            break;
        case 4:
            cscan(head, n, arr);
            break;
        case 5:
            look(head, n, arr);
            break;
        case 6:
            clook(head, n, arr);
            break;
        case 7:
            return 0;
            break;
        }
    }
}