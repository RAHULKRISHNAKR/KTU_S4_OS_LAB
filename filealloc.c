/*linked():
Initialize an array f to keep track of allocated blocks.
Declare variables bs, p, i, j, k, a, st, len, n, and alloc.
Declare a structure struct lfile with fields name, start, siz, and blocks.
Declare an array of struct lfile named files to store file information.
Ask the user for the number of files (nof).
Loop through each file:
Prompt the user to enter the file name.
Prompt the user to enter the starting block (st) for the file.
Mark the starting block as allocated in array f.
Prompt the user to enter the number of blocks (n) for the file.
Loop to input the block numbers for the file:
Mark each block as allocated in array f.
Store each block number in the blocks array of the current file.
Store the starting block, size, and blocks array in the files array.
Display the file information.
indexed():
Initialize an array f to keep track of allocated blocks.
Declare variables index, alocfil, allocated, i, n, st, len, j, c, k, ind, and count.
Ask the user for the number of files (nof).
Loop through each file:
Prompt the user to enter the index block (ind) for the file.
Check if the index block is available in array f.
If available, prompt the user to enter the number of blocks (n) for the file.
Loop to input the block numbers for the file:
Check if each block is available in array f.
If available, mark the block as allocated in array f.
If all blocks are available, mark the index block as allocated.
Store the file number, index block, and length in the alocfil array.
Display the allocated blocks for each file.
seq():
Initialize an array files to keep track of allocated blocks.
Declare variables alocfiles, startBlock, len, j, k, ch, allocated, and n.
Ask the user for the number of files (n).
Loop through each file:
Prompt the user to enter the starting block (startBlock) and length (len) for the file.
Check if consecutive blocks starting from startBlock are available.
If available, mark those blocks as allocated in array files.
Store the file number, start block, and length in the alocfiles array.
Display the allocated files.
Prompt the user to enter a file number to check its space occupied. If found, display the space occupied by the file.
main():
Print "File Allocations".
Declare variable op to store the user's choice.
Start a loop that continues until op is 4:
Display a menu with options to choose allocation methods.
Prompt the user to enter an option (op).
Use a switch-case statement to call the corresponding function based on the user's choice.
If the user chooses to exit (option 4), end the loop and exit the program.*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct lfile
{

  char name[26];

  int start, siz;

  int blocks[20];

};



void
linked ()
{

  int f[200], bs[20], p, i, j, k, a, st, len, n, alloc = 0;

  char name[26];

  struct lfile files[20];

  int nof;

  for (i = 0; i < 200; i++)
    f[i] = 0;

  printf ("Enter the number of Files...\n");

  scanf ("%d", &nof);

  for (int w = 0; w < nof; w++)

    {

      printf ("Enter the file name...\n");
      scanf ("%s", files[alloc].name);

      printf ("Enter the starting block...\n");

      scanf ("%d", &st);

// if(f[st]==1) // UNCOMMENT IF CHECKING IS REQUIRED
// {
//     printf("Block is already Allocated!\n");
//     continue;
// }
      f[st] = 1;

      printf ("Enter the number of blocks...\n");

      scanf ("%d", &n);

      printf ("Enter Block Numbers...\n");

      int flag = 0;

      for (i = 0; i < n; i++)

	{

	  scanf ("%d", &a);

// if(f[a]==1)
// {
//     printf("The block %d is already allocated!\n",a);
//     int flag=1;
//     break;
// }
	  f[a] = 1;

	  files[alloc].blocks[i] = a;

	}

// if(flag==1)continue;
      files[alloc].start = st;

      files[alloc].siz = n;

      alloc++;

    }

  printf ("\nFile\tStart\tSize\tBlock\n");

  for (int i = 0; i < alloc; i++)

    {

      printf ("%s\t%d\t%d\t", files[i].name, files[i].start, files[i].siz);

      printf ("%d ", files[i].blocks[0]);

      for (int j = 1; j < files[i].siz; j++)

	printf ("--> %d ", files[i].blocks[j]);

      printf ("\n");

    }
}

void
indexed ()
{

  int f[200], index[50], alocfil[50][3], allocated =
    0, i, n, st, len, j, c, k, ind, count = 0;

  for (i = 0; i < 200; i++)

    f[i] = 0;

  int nof;

  printf ("Enter the number of Files...\n");

  scanf ("%d", &nof);

  for (int w = 0; w < nof; w++)

    {

      printf ("Enter the index block: ");

      scanf ("%d", &ind);

      if (f[ind] != 1)

	{

	  printf ("Enter blocks occupied by the file : \n", ind);

	  scanf ("%d", &n);

	}

      else

	{

	  printf ("%d index is already allocated \n", ind);

	  continue;

	}

      count = 0;

      printf ("Enter blocks of file...\n ");

      for (i = 0; i < n; i++)

	{

	  scanf ("%d", &index[i]);

	  if (f[index[i]] == 0)

	    count++;

	}

      if (count == n)

	{

	  for (j = 0; j < n; j++)

	    f[index[j]] = 1;

	  printf ("Allocated!\n");

	  alocfil[allocated][0] = w + 1;

	  alocfil[allocated][1] = ind;

	  alocfil[allocated][2] = n;

	  allocated++;

	}

      else

	{

	  printf ("File in the index is already allocated \n");

	}
    }

  printf ("\nAllocated Blocks\nFile\tIndex\tLength\n");

  for (int i = 0; i < allocated; i++)

    {

      printf ("%d\t%d\t%d\n", alocfil[i][0], alocfil[i][1], alocfil[i][2]);

    }
}

void
seq ()
{

  int files[200], alocfiles[32][3];

  int startBlock, len, j, k, ch, allocated = 0;

  int n;

  for (int i = 0; i < 200; i++)

    files[i] = 0;

  printf ("Enter the number of files...\n");

  scanf ("%d", &n);

  for (int i = 0; i < n; i++)

    {

      int flag = 0;

      printf ("Enter the starting block and the length of the file %d:  ",
	      i + 1);

      scanf ("%d%d", &startBlock, &len);

      for (j = startBlock; j < (startBlock + len); j++)
	{

	  if (files[j] == 0)

	    flag++;

	}

      if (len == flag)
	{

	  for (int k = startBlock; k < (startBlock + len); k++)
	    {

	      if (files[k] == 0)
		{

		  files[k] = 1;

		}

	    }

	  printf ("The file %d is allocated to the disk\n", i + 1);

	  alocfiles[allocated][0] = i + 1;

	  alocfiles[allocated][1] = startBlock;

	  alocfiles[allocated][2] = len;

	  allocated++;

	}

      else

	printf ("The file %d is not allocated to the disk\n", i + 1);

    }

  printf ("\nAllocated Files:\n\nFile No\tStart Block\tLength\n");

  for (int i = 0; i < allocated; i++)

    {

      printf ("%d\t%d\t\t%d\n", alocfiles[i][0], alocfiles[i][1],
	      alocfiles[i][2]);

    }
  int filno;

  printf ("\nEnter File Number: ");

  scanf ("%d", &filno);

  for (int i = 0; i < allocated; i++)

    {

      if (alocfiles[i][0] == filno)

	{
	  printf ("File Number : %d\t Space Occupied : %d\n", alocfiles[i][0],
		  alocfiles[i][2]);

	  filno = -1;

	}

    }

  if (filno != -1)

    printf ("File Number Not Found!\n\n");

  return;

}



int
main ()
{
  printf ("File Allocations");

  int op = 0;

  while (op != 4)

    {

      printf
	("\n\n1. SEQUENTIAL\n2. INDEXED\n3. LINKED\n4. Exit\nEnter your option...\n\n");

      scanf ("%d", &op);

      switch (op)

	{

	case 1:

	  seq ();

	  break;

	case 2:

	  indexed ();

	  break;

	case 3:

	  linked ();

	  break;

	}

    }

}