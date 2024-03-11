/*
1. FCFS (First Come First Served) Algorithm
    
    1. Input: Number of processes (n), arrival time (at) and burst time (bt) for each process.
    2. Sorting: Sort processes by arrival time (at) to ensure they are processed in the order they arrive.
    3. Initialization:
         `ct`: Completion time (initialized to 0) for the first process, as there's no prior execution.
         `wt`: Waiting time (initialized to 0 for each process).
         `tat`: Turnaround time (initialized to 0 for each process).
    4. Process Loop:
         Iterate through the sorted processes:
             Update completion time for the current process: `ct[i] = ct[i-1] + bt[i]`, considering the previous process's completion time.
             Calculate waiting time for the current process: `wt[i] = ct[i] - at[i] - bt[i]`. It considers the difference between completion time, arrival time, and burst time.
             Calculate turnaround time for the current process: `tat[i] = wt[i] + bt[i]`.
    5. Output: Print process name, completion time, waiting time, and turnaround time for each process.
    6. Average Metrics: Calculate and print the average waiting time (sum of all waiting times divided by n) and average turnaround time (sum of all turnaround times divided by n).

2. SJF (Shortest Job First) Algorithm (Non-preemptive)
    
        1. Input: Number of processes (n), arrival time (at) and burst time (bt) for each process.
        2. Ready List: Create a data structure (like a queue) to store ready processes (processes that have arrived).
        3. Initialization: Same as FCFS (ct, wt, tat initialized to 0).
        4. Process Loop:
             Continuously loop until all processes are completed:
                 Add processes to the ready list based on their arrival time.
                 Find the process in the ready list with the shortest burst time.
                 Update completion time: `ct = ct + bt[selected_process]`.
                 Update waiting time for all processes in the ready list **except** the selected one: `wt[i] = ct - at[i] - bt[i]` (consider processes that arrived before the selected one).
                 Update turnaround time for the selected process: `tat[selected_process] = wt[selected_process] + bt[selected_process]`.
                 Remove the selected process from the ready list.
        5. Output: Same as FCFS.
        6. Average Metrics: Same as FCFS.
    
    
    3. Priority Scheduling Algorithm (Non-preemptive)
    
    1. Input: Number of processes (n), arrival time (at), burst time (bt), and priority (pr) for each process (lower numerical value represents higher priority).
    2. Ready List: Same as SJF.
    3. Initialization: Same as FCFS (ct, wt, tat initialized to 0).
    4. Process Loop: Similar to SJF, but prioritize processes based on their priority instead of burst time:
         Find the process in the ready list with the highest priority (lowest numerical value in pr).
         Update completion time, waiting time (for non-selected processes), and turnaround time (for the selected process) using the same formulas as SJF.
         Remove the selected process from the ready list.


4. Round Robin
Algorithm:

    Input: Number of processes (n), arrival time (at), burst time (bt) for each process, and time quantum (t).
    Data Structures:
    q: Queue to store process IDs during scheduling.
    p: Array of structures to store process information (same as other functions).
    Initialization:
    ls: Local variable to keep track of the number of completed processes (initialized to 0).
    front and rear variables to manage the queue q (both initialized to -1, indicating an empty queue).
    idle: Flag to track idle CPU time (initialized to 0, meaning CPU is busy initially).
    Process Loop:
    Iterate until all processes are completed (ls < n):
    For each process:
    If the process arrival time is less than or equal to the current time (i) and its status is 0 (not yet processed), add the process ID to the queue (enqueue(j)) and update its status to 1 (under process).
    Check for idle CPU time:
    If idle is 1 and the queue is empty (front == -1), it indicates an idle CPU period. Add "Idle" to the Gantt chart information (d) with the current time as both start and completion time (d[num].st = i; d[num].ct = i;). Increment i to reflect the idle time and set idle back to 0.
    If the queue is not empty (front != -1):
    If idle is 1, update the completion time in the Gantt chart for the previous process (d[num].ct = i). Set idle to 0 and increment num to move to the next entry in the Gantt chart information.
    Dequeue a process ID from the front of the queue (k = dequeue()).
    Update the start time in the Gantt chart for the dequeued process (d[num].st = i).
    If the remaining burst time of the process (p[k].left) is less than or equal to the time quantum (t):
    Update the completion time in the Gantt chart (d[num].ct = i + p[k].left).
    Update the process's completion time (p[k].ct = d[num].ct), turnaround time (p[k].tt = i - p[k].at), and waiting time (p[k].wt = p[k].tt - p[k].bt), marking it as completed.
    Increment ls to indicate one more process completion.
    Increment num to the next Gantt chart information entry.
    Else (remaining burst time is greater than the time quantum):
    Reduce the remaining burst time of the process (p[k].left = p[k].left - t).
    Enqueue the process ID back to the queue (enqueue(k)).
    Increment num to the next Gantt chart information entry.
    If none of the above conditions apply, simply increment the current time (i).
    Output: Print process information like name, completion time, waiting time, and turnaround time for each process.
    Gantt Chart: Display the Gantt chart information (d) showing process execution and idle periods.
    Average Metrics: Calculate and print the average waiting time (sum of all waiting times divided by n) and average turnaround time (sum of all turnaround times divided by n).

*/

#include<stdio.h>
#include<string.h>

int q[100],front=-1,rear=-1;

struct process
{
  char name[20];
  int at,tt,bt,wt,ct,status,left,pr;
}p[20],temp;

struct done
{
  char name[20];
  int st,ct;
}d[20];

void enqueue(int j)
{
  if(front==-1 && rear==-1)
  {
    front++;
  }
  rear++;
  q[rear] = j;
}
int dequeue()
{
  int item;
  item = q[front];
  if(front == rear)
  {
    front = -1;
    rear = -1;
  }
  else
  {
    front++;
  }
  return(item);
}
void roundrobin()
{
  int n,i,j,idle=0,k,num,ls,t;
  float avwt=0,avtt=0;
  printf("ENTER THE NUMBER OF PROCESSES : ");
  scanf("%d",&n);
  for(i=0;i<n;i++)                         //Input process details
  {
    printf("\nENTER DETAILS OF PROCESS %d",i+1);
    printf("\nPROCESS NAME : ");
    scanf(" %s",p[i].name);
    printf("ARRIVAL TIME : ");
    scanf("%d",&p[i].at);
    printf("BURST TIME : ");
    scanf("%d",&p[i].bt);
    p[i].left = p[i].bt;
    p[i].status = 0;
  }
  printf("\nENTER THE TIME QUANTUM : ");
  scanf("%d",&t);

  for(i=0,num=0,ls=0;ls<n;)
  {
    for(j=0;j<n;j++)
    {
      if(p[j].status==0 && p[j].at<=i)
      {
        enqueue(j);
        p[j].status = 1;
      }
    }
    if(idle==0 && front == -1)
    {
      strcpy(d[num].name,"Idle");
      d[num].st = i;
      idle = 1;
      i++;
    }
    else if(front!=-1)
    {
      if(idle==1)
      {
        d[num].ct = i;
        idle = 0;
        num++;
      }
      k = dequeue();
      d[num].st = i;
      strcpy(d[num].name,p[k].name);
      if(p[k].left<=t)
      {
        d[num].ct = i+p[k].left;
        p[k].ct = d[num].ct;
        i = d[num].ct;
        p[k].tt = i - p[k].at;
        p[k].wt = p[k].tt - p[k].bt;
        p[k].status = 2;
        ls++;
        num++;
      }
      else if(p[k].left>t)
      {
        d[num].ct = i+t;
        i = d[num].ct;
        p[k].left = p[k].left-t;
        num++;
        for(j=0;j<n;j++)
        {
          if(p[j].status==0 && p[j].at<=i)
          {
            enqueue(j);
            p[j].status = 1;
          }
        }
        enqueue(k);
      }
    }
    else
    {
      i++;
    }
  }

  printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
  for(i=0;i<n;i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].name,p[i].ct,p[i].wt,p[i].tt);
    avwt+=p[i].wt;
    avtt+=p[i].tt;
  }
  printf("\n\nGANTT CHART ");
  printf("\n\t--------------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
    printf("|");
    printf("%s\t",d[i].name);
  }
  printf(" |");
  printf("\n\t--------------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
      printf("%d\t",d[i].st);
  }
  printf("%d\t",d[num-1].ct);
  printf("\n\nAVERAGE WAITING TIME : %f",(avwt/n));
  printf("\nAVERAGE TURNAROUND TIME : %f\n",(avtt/n));
}

void priority()
{
  int n,i,j,ls,min,fnd,num,idle;
  float twt=0.0,ttt=0.0;
  printf("ENTER THE NUMBER OF PROCESSES : ");
  scanf("%d",&n);
  for(i=0;i<n;i++)                         //Input process details
  {
    printf("\nENTER DETAILS OF PROCESS %d",i+1);
    printf("\nPROCESS NAME : ");
    scanf(" %s",p[i].name);
    printf("ARRIVAL TIME : ");
    scanf("%d",&p[i].at);
    printf("BURST TIME : ");
    scanf("%d",&p[i].bt);
    printf("PRIORITY : ");
    scanf("%d",&p[i].pr);
    p[i].status = 0;
  }
  for(i=0,ls=0,num=0,idle=0;ls<n;)
  {
    for(j=0,fnd=0;j<n;j++)
    {
      if(i>=p[j].at && p[j].status==0)
      {
        if(fnd==0)
        {
          min = j;
          fnd = 1;
        }
        else if((p[min].pr>p[j].pr)||(p[min].pr==p[j].pr && p[min].at>p[j].at))
        {
          min = j;
        }
      }
    }
    if(idle==0 && fnd==0)
    {
      strcpy(d[num].name,"Idle");
      d[num].st = i;
      i++;
      idle = 1;
    }
    else if(fnd==1)
    {
      if(idle==1)
      {
        d[num].ct = i;
        num++;
        idle = 0;
      }
      strcpy(d[num].name,p[min].name);
      p[min].status =1;
      d[num].st = i;
      d[num].ct = i + p[min].bt;
      i = d[num].ct;
      p[min].ct = d[num].ct;
      p[min].tt = p[min].ct - p[min].at;
      p[min].wt = p[min].tt - p[min].bt;
      num++;
      ls++;
    }
    else
    {
      i++;
    }
  }
  printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
  for(i=0;i<n;i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].name,p[i].ct,p[i].wt,p[i].tt);
    twt+=p[i].wt;
    ttt+=p[i].tt;
  }
  printf("\n\nGANTT CHART ");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
    printf("|");
    printf("%s\t",d[i].name);
  }
  printf(" |");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
      printf("%d\t",d[i].st);
  }
  printf("%d\t\n",d[num-1].ct);
  printf("\nAVERAGE WAITING TIME : %f",(twt/n));
  printf("\nAVERAGE TURNAROUND TIME : %f\n",(ttt/n));
}

void sjf()
{
  int n,i,j,ls,min,fnd,num,idle;
  float twt=0.0,ttt=0.0;
  printf("ENTER THE NUMBER OF PROCESSES : ");
  scanf("%d",&n);
  for(i=0;i<n;i++)                         //Input process details
  {
    printf("\nENTER DETAILS OF PROCESS %d",i+1);
    printf("\nPROCESS NAME : ");
    scanf(" %s",p[i].name);
    printf("ARRIVAL TIME : ");
    scanf("%d",&p[i].at);
    printf("BURST TIME : ");
    scanf("%d",&p[i].bt);
    p[i].status = 0;
  }
  for(i=0,ls=0,num=0,idle=0;ls<n;)
  {
    for(j=0,fnd=0;j<n;j++)
    {
      if(i>=p[j].at && p[j].status==0)
      {
        if(fnd==0)
        {
          min = j;
          fnd = 1;
        }
        else if(fnd!=0 && p[min].bt>p[j].bt)
        {
          min = j;
        }
      }
    }
    if(idle==0 && fnd==0)
    {
      strcpy(d[num].name,"Idle");
      d[num].st = i;
      i++;
      idle = 1;
    }
    else if(fnd==1)
    {
      if(idle==1)
      {
        d[num].ct = i;
        num++;
        idle = 0;
      }
      strcpy(d[num].name,p[min].name);
      p[min].status =1;
      d[num].st = i;
      d[num].ct = i + p[min].bt;
      i = d[num].ct;
      p[min].ct = d[num].ct;
      p[min].tt = p[min].ct - p[min].at;
      p[min].wt = p[min].tt - p[min].bt;
      num++;
      ls++;
    }
    else
    {
      i++;
    }
  }
  printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
  for(i=0;i<n;i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].name,p[i].ct,p[i].wt,p[i].tt);
    twt+=p[i].wt;
    ttt+=p[i].tt;
  }
  printf("\n\nGANTT CHART ");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
    printf("|");
    printf("%s\t",d[i].name);
  }
  printf(" |");
  printf("\n\t--------------------------------------------------------------------\n\t");
  for(i=0;i<num;i++)
  {
      printf("%d\t",d[i].st);
  }
  printf("%d\t\n",d[num-1].ct);
  printf("\nAVERAGE WAITING TIME : %f",(twt/n));
  printf("\nAVERAGE TURNAROUND TIME : %f\n",(ttt/n));
}

void fcfs()
{
  int i,j,n,num,idle=0;
  float avwt=0;
  float avtt=0;
  printf("ENTER THE NUMBER OF PROCESSES : ");
  scanf("%d",&n);
  for(i=0;i<n;i++)                         //Input process details
  {
    printf("\nENTER DETAILS OF PROCESS %d",i+1);
    printf("\nPROCESS NAME : ");
    scanf(" %s",p[i].name);
    printf("ARRIVAL TIME : ");
    scanf("%d",&p[i].at);
    printf("BURST TIME : ");
    scanf("%d",&p[i].bt);
    p[i].status = 0;
  }
  for(i=0;i<n;i++)                       //Sorting based on at
  {
    for(j=0;j<n-i-1;j++)
    {
      if(p[j].at > p[j+1].at)
      {
        temp = p[j];
        p[j] = p[j+1];
        p[j+1] = temp;
      }
    }
  }
  for(i=0,j=0,num=0;j<n;)              //Calculations
  {
    if(p[j].at<=i && p[j].status==0)
    {
      if(idle==1)
      {
        d[num].ct=i;
        num++;
        idle = 0;
      }
      strcpy(d[num].name,p[j].name);
      d[num].st = i;
      d[num].ct = i + p[j].bt;
      p[j].wt = d[num].st - p[j].at;
      p[j].tt = p[j].wt + p[j].bt;
      p[j].ct = d[num].ct;
      i = d[num].ct;
      p[j].status = 1;
      j++;
      num++;

    }
    else if(idle == 0)
    {
      strcpy(d[num].name,"Idle");
      d[num].st = i;
      i++;
      idle = 1;
    }
    else
    {
      i++;
    }
  }
  printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n");
  for(int i=0;i<n;i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n",p[i].name,p[i].ct,p[i].wt,p[i].tt);
    avwt+=p[i].wt;
    avtt+=p[i].tt;
  }
  printf("\n\nGANTT CHART ");
  printf("\n----------------------------------------------------------\n");
      for(i=0;i<num;i++)
      {
          printf("|");
          printf("   %s\t",d[i].name);
       }
       printf(" |");
       printf("\n----------------------------------------------------------\n");
       for(i=0;i<num;i++)
       {
          printf("%d\t",d[i].st);
       }
       printf("%d\t",d[num-1].ct);
  printf("\n\nAVERAGE WAITING TIME : %f",(avwt/n));
  printf("\nAVERAGE TURNAROUND TIME : %f\n",(avtt/n));
}

int main(){
    int choice;
    while(choice!=5){
        printf("\n--Menu--\n");
        printf("1.FCFS   2.SJF   3.Priority   4.Round Robin   5.Exit\nEnter choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1: fcfs();break;
            case 2: sjf();break;
            case 3: priority();break;
            case 4: roundrobin();break;
            case 5: break;
            default: printf("\nInvalid Choice\n");break;
        }
    }
}
