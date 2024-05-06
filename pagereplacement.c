/*Function: pageIsFound(f[], count, a)
Input: 
    f[]: Array representing the page frames
    count: Number of pages currently in the frames
    a: Page to be searched

Algorithm:
1. Loop through each element in the page frames array.
2. If the current element matches the page 'a', return 1 (indicating page found).
3. If no match is found, return 0 (indicating page not found).
fifo Function
mathematica
Copy code
Function: fifo(arr[], n, f[], fno)
Input:
    arr[]: Array representing the sequence of page requests
    n: Number of page requests
    f[]: Array representing the page frames
    fno: Number of page frames

Algorithm:
1. Initialize a 2D array fifoArr to store the page frames at each step.
2. Initialize variables front = 0 (representing the front of the frame array), count = 0 (representing the number of pages currently in frames), p = 0 (representing the number of page faults).
3. Iterate through each page request in the sequence:
    a. If the page is found in the frame array, do nothing.
    b. If the page is not found:
        i. Increment the page fault count (p).
        ii. Replace the page at the front of the frame array with the current page.
        iii. Update the front pointer to the next position in the frame array.
        iv. If the count is less than the number of frames (fno), increment the count.
    c. Update the fifoArr with the current frame status.
4. Print the page requests, page frames, and the total number of page faults.
lru Function
mathematica
Copy code
Function: lru(arr[], n, f[], fno)
Input:
    arr[]: Array representing the sequence of page requests
    n: Number of page requests
    f[]: Array representing the page frames
    fno: Number of page frames

Algorithm:
1. Initialize a 2D array lruArr to store the page frames at each step.
2. Initialize variables count = 0 (representing the number of pages currently in frames), p = 0 (representing the number of page faults).
3. Iterate through each page request in the sequence:
    a. If the page is found in the frame array, do nothing.
    b. If the page is not found:
        i. Increment the page fault count (p).
        ii. If the count is equal to the number of frames (fno):
            - Find the least recently used page in the frame array.
            - Replace it with the current page.
        iii. If the count is less than the number of frames (fno), add the current page to the frame array.
    c. Update the lruArr with the current frame status.
4. Print the page requests, page frames, and the total number of page faults.
optimal Function
mathematica
Copy code
Function: optimal(arr[], n, f[], fno)
Input:
    arr[]: Array representing the sequence of page requests
    n: Number of page requests
    f[]: Array representing the page frames
    fno: Number of page frames

Algorithm:
1. Iterate through each page request in the sequence:
    a. If the page is found in the frame array, do nothing.
    b. If the page is not found:
        i. Increment the page fault count.
        ii. If the count is equal to the number of frames (fno):
            - Find the page that will not be used for the longest period in the future.
            - Replace it with the current page.
        iii. If the count is less than the number of frames (fno), add the current page to the frame array.
    c. Print the page fault and the current state of the page frames.
2. Print the total number of page faults.
printPageTable Function
mathematica
Copy code
Function: printPageTable(f[], size)
Input:
    f[]: Array representing the page frames
    size: Number of elements in the frame array

Algorithm:
1. Print "Page Frames:" followed by each element of the frame array separated by a space.
2. Print a newline character.
main Function
vbnet
Copy code
Function: main()
Input: None

Algorithm:
1. Read the number of frames (frameNum) and the number of page requests (n) from the user.
2. Read the page requests into the array arr[].
3. Initialize an array F[] to represent the page frames.
4. Create a loop to present a menu for selecting page replacement algorithms until the user chooses to exit:
    a. Display the menu options.
    b. Read the user's choice.
    c. Depending on the choice, call the corresponding page replacement function (fifo, lru, optimal), passing the necessary parameters.
5. Exit the program when the user chooses to exit.*/


#include <stdio.h>

int pageIsFound(int f[],int count,int a){
    for(int i=0;i<count;i++){
        if(f[i]==a)
            return 1;
    }
    return 0;
}
void fifo(int arr[],int n, int f[],int fno){
    printf("\nFIFO Page Replacement\n");
    int fifoArr[fno][n];
    int front=0,count=0,p=0,j,k,i;
    for(i=0;i<n;i++){
        if(pageIsFound(f,count,arr[i])){}
        else{
            p++;
            f[front] = arr[i];
            front = (front+1)%fno;
            if(count != fno)
                count++;
        }
        for(j=0,k=0;j<fno;j++){
            if(k<count)
                fifoArr[k++][i] = f[j];
            else 
                fifoArr[k++][i] = -1;
        }

    }
    printf("Pages\n");
    for(i=0;i<n;i++){
        printf("%d  ",arr[i]);
    }
    printf("\nPage Frames\n");
    for(i=0;i<fno;i++){
        for(j=0;j<n;j++){
            if(fifoArr[i][j] != -1)
                printf("%d  ",fifoArr[i][j]);
            else 
                printf("   ");
        }
        printf("\n");
    }
    printf("Page Faults(in FIFO) = %d\n\n",p);
}

int recentAccessLRU(int arr[],int i,int a){
    int count=0;
    for(int j=i;j>=0;j--){
        count++;
        if(arr[j]==a)
            return count;
    }
}
void lru(int arr[],int n, int f[],int fno){
    int index,count=0,p=0,i,j,k,x,lruArr[fno][n];
    for( i=0;i<n;i++){
        if(pageIsFound(f,count,arr[i])){}
        else{
            p++;
            if(count == fno){
                int max = -1;
                for(j=0;j<fno;j++){
                    x = recentAccessLRU(arr,i,f[j]);
                    if(x > max){
                        index = j;
                        max = x;
                    }
                }
                f[index] = arr[i];
            }
            else{
                f[count++]=arr[i];
            }
        }
        for(j=0,k=0;j<fno;j++){
            if(k<count)
                lruArr[k++][i] = f[j];
            else 
                lruArr[k++][i] = -1;
        }
    }
    printf("Pages\n");
    for(i=0;i<n;i++){
        printf("%d  ",arr[i]);
    }
    printf("\nPage Frames\n");
    for(i=0;i<fno;i++){
        for(j=0;j<n;j++){
            if(lruArr[i][j] != -1)
                printf("%d  ",lruArr[i][j]);
            else 
                printf("   ");
        }
        printf("\n");
    }
    printf("Page Faults(in LRU) = %d\n\n",p);
}

void printPageTable(int f[],int size){
    printf("Page Frames: ");
    for(int i=0;i<size;i++)
        printf("%d ",f[i]);
    printf("\n");
}

int acessInOptimal(int arr[],int n,int i,int a){
    int count = 0;
    for(int j=i+1;j<n;j++){
        count++;
        if(arr[j]==a)
            return count;
    }
    return count+1;
}

void optimal(int arr[],int n, int f[],int fno){
    printf("\nOptimal Page Replacement Algorithm\n");
    int i,j,count=0,p=0,x,index;
    for(i=0;i<n;i++){
        printf("Page:%d => ",arr[i]);
        if(pageIsFound(f,count,arr[i])){
            printf("No Page Fault\n");
        }
        else{
            printf("Page Fault    => ");
            p++;
            if(count == fno){
                int max = -1;
                for(j=0;j<fno;j++){
                    x = acessInOptimal(arr,n,i,f[j]);
                    if(x > max){
                        index = j;
                        max = x;
                    }
                }
                f[index] = arr[i];
            }
            else{
                f[count++]=arr[i];
            }
            printPageTable(f,count);
        }
    }
    printf("Number of page faults in Optimal Algorithm = %d\n",p);
}

void main(){
    int n,i,frameNum;
    printf("Enter the number of frames: ");
    scanf("%d",&frameNum);
    printf("Enter the number of page requests: ");
    scanf("%d",&n);
    printf("Enter the page string each seperated by a space\n");
    int arr[n],F[frameNum];
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    int choice;

    do{
        printf("Page Replacement Algorithms\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. OPTIMAL\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1: 
                fifo(arr,n ,F,frameNum);
                break;
            case 2:
                lru(arr,n ,F,frameNum);
                break;
            case 3: 
                optimal(arr,n ,F,frameNum);
                break;
            case 4:
                break;
        }
    }while(choice != 4);
}