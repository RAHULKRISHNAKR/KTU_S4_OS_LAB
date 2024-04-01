/*Initialization:

- The code starts by including the `stdio.h` header for standard input/output functions.
- Three functions are defined: `firstfit`, `worstfit`, and `bestfit`. Each takes four integer arrays as arguments:
    - `p_size`: Array containing sizes of processes (n elements)
    - `n`: Number of processes
    - `m_size`: Array containing sizes of memory blocks (m elements)
    - `m`: Number of memory blocks
- A `main` function is defined.

main function
- The program prompts the user to enter the number of processes (`n`) and reads it using `scanf`.
- It then prompts the user to enter the sizes of each process (`p_size[i]`) in a loop and reads them using `scanf`.
- Similarly, the program prompts the user to enter the number of memory blocks (`m`) and reads it using `scanf`.
- Finally, it prompts the user to enter the sizes of each memory block (`m_size[i]`) in a loop and reads them using `scanf`.


**a) `firstfit` function (First Fit):**

  1. Prints a header "FIRST FIT".
  2. Iterates through each process size (`p_size[i]`) in a loop (`i` from 0 to `n-1`).
     - Initializes a flag `flag` to 0 (indicating process not allocated yet).
     - Loops through each memory block size (`m_size[j]`) in another loop (`j` from 0 to `m-1`).
       - If the current memory block size is sufficient to hold the process (`m_size[j] >= p_size[i]`), performs the following:
         - Prints a message indicating the process size, allocated memory block size, and remaining space after allocation.
         - Updates the memory block size by subtracting the process size (`m_size[j] = m_size[j] - p_size[i]`).
         - Sets the flag to 1 (indicating process allocated).
         - Breaks out of the inner loop (`j`) as allocation is successful.
     - If the inner loop finishes without finding a suitable block (flag remains 0), prints a message indicating the process cannot be allocated.

**b) `worstfit` function (Worst Fit):**

  1. Prints a header "WORST FIT".
  2. Iterates through each process size (`p_size[i]`) in a loop (`i` from 0 to `n-1`).
     - Initializes variables `max` to the first memory block size (`m_size[0]`) and `loc` to its index (0).
     - Loops through each memory block size (`m_size[j]`) in another loop (`j` from 1 to `m-1`).
       - If the current memory block size is larger than the current `max` size, updates `max` and `loc` with the current block size and its index.
     - If there's a memory block large enough to hold the process (`max >= p_size[i]`), performs the following:
       - Prints a message indicating the process size, allocated memory block size, and remaining space after allocation.
       - Updates the memory block size at index `loc` by subtracting the process size (`m_size[loc] = m_size[loc] - p_size[i]`).
     - If no suitable block is found, prints a message indicating the process cannot be allocated.

best fit
Iterates through each process size (p_size[i]) in a loop (i from 0 to n-1):
Initializes a variable loc to -1 (indicating no best-fitting block found yet).
Loops through each memory block size (m_size[j]) in another loop (j from 0 to m-1):
If the current memory block size is sufficient to hold the process (m_size[j] >= p_size[i]), performs the following:
If loc is -1 (no best block found yet), sets loc to the current index (j).
If the current block size is smaller than the previous best block size (m_size[loc] > m_size[j]), updates loc to the current index (j) as it's a better fit.
If a suitable block is found (loc != -1):
Allocates the process p_size[i] to the memory block m_size[loc]:
Updates the memory block size by subtracting the process size (m_size[loc] = m_size[loc] - p_size[i]).
Prints a message indicating the process size, allocated memory block size, and remaining space after allocation.
If no suitable block is found (loc == -1):
Prints a message indicating the process cannot be allocated.*/


#include<stdio.h>
void firstfit(int p_size[],int n,int m_size[],int m)
{
  printf("\t\tFIRST FIT \n");
  int i,j,flag,psize[100],msize[100];
  for(i=0;i<n;i++)
  {
    psize[i] = p_size[i];
  }
  for(i=0;i<m;i++)
  {
    msize[i] = m_size[i];
  }
  for(i=0;i<n;i++)
  {
    flag=0;
    for(j=0;j<m;j++)
    {
      if(msize[j]>=psize[i])
      {
        printf("%d ALLOCATED IN %d MEMORY BLOCK",psize[i],msize[j]);
        msize[j] = msize[j]-psize[i];
        printf(" => %d SPACE REMAINING \n",msize[j]);
        flag=1;
        break;
      }
    }
    if(flag==0)
    {
      printf("%d CANNOT BE ALLOCATED \n",psize[i]);
    }
  }
}
void worstfit(int p_size[],int n,int m_size[],int m)
{
  printf("\t\tWORST FIT \n");
  int i,j,max,loc,psize[100],msize[100];
  for(i=0;i<n;i++)
  {
    psize[i] = p_size[i];
  }
  for(i=0;i<m;i++)
  {
    msize[i] = m_size[i];
  }
  for(i=0;i<n;i++)
  {
    max = msize[0];
    loc = 0;
    for(j=0;j<m;j++)
    {
      if(msize[j]>max)
      {
        max = msize[j];
        loc = j;
      }
    }
    if(max>=psize[i])
    {
      printf("%d ALLOCATED IN %d MEMORY BLOCK",psize[i],msize[loc]);
      msize[loc] = msize[loc]-psize[i];
      printf(" => %d SPACE REMAINING \n",msize[loc]);
    }
    else
    {
      printf("%d CANNOT BE ALLOCATED \n",psize[i]);
    }
  }
}
void bestfit(int p_size[],int n,int m_size[],int m)
{
  printf("\t\tBEST FIT \n");
  int i,j,max,loc,psize[100],msize[100];
  for(i=0;i<n;i++)
  {
    psize[i] = p_size[i];
  }
  for(i=0;i<m;i++)
  {
    msize[i] = m_size[i];
  }
  for(i=0;i<n;i++)
  {
    loc = -1;
    for(j=0;j<m;j++)
    {
      if(msize[j]>=psize[i])
      {
        if(loc == -1)
        {
          loc = j;
        }
        else if(msize[loc]>msize[j])
        {
          loc = j;
        }
      }
    }
    if(loc != -1)
    {
      printf("%d ALLOCATED IN %d MEMORY BLOCK",psize[i],msize[loc]);
      msize[loc] = msize[loc]-psize[i];
      printf(" => %d SPACE REMAINING \n",msize[loc]);
    }
    else
    {
      printf("%d CANNOT BE ALLOCATED \n",psize[i]);
    }
  }
}
int main()
{
  int i,p_size[100],m_size[100],n,m;
  printf("ENTER THE NUMBER OF PROCESS : ");
  scanf("%d",&n);
  printf("ENTER THE ARRAY OF PROCESS : ");
  for(i=0;i<n;i++)
  {
    scanf("%d",&p_size[i]);
  }
  printf("ENTER THE NUMBER OF MEMORY BLOCK : ");
  scanf("%d",&m);
  printf("ENTER THE ARRAY OF MEMORY BLOCK : ");
  for(i=0;i<m;i++)
  {
    scanf("%d",&m_size[i]);
  }
  firstfit(p_size,n,m_size,m);
  bestfit(p_size,n,m_size,m);
  worstfit(p_size,n,m_size,m);
  return 0;
}
