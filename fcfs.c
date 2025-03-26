#include<stdio.h>
#include<string.h>
struct node
{
	char pname[10];
	int at,bt,st,ct,tat,wt;
};

int gantt_chart[10];
void accept(struct node a[],int n)
{
	int i;
	printf("Enter Process Name , Arrival Time & Burst Time :\n");
	for(i=0;i<n;i++)
	{
		scanf("%s%d%d",&a[i].pname,&a[i].at,&a[i].bt);
	}
	
}
void sort(struct node a[],int n)
{
	int i,j;
	struct node temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j].at>a[j+1].at)
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}
void fcfs(struct node a[],int n)
{
	
	int completed[10]={0},i,j=0,ft=0;
	int n1=0,id=-1;
	while(n1!=n)
	{
	
		for(i=0;i<n;i++)
		{
			if(completed[i]==0)
			{
				id=i;
				break;
			}
		}
		if(id>=0)
		{
			a[id].st=ft;
			a[id].ct=ft+a[id].bt;
			ft=a[id].ct;
			a[id].tat=a[id].ct-a[id].at;
			a[id].wt=a[id].tat-a[id].bt;
			completed[id]=1;
			gantt_chart[j]=id;
			j++;
			n1++;		
		}
		else
			ft++;
	
	}
}
void display(struct node a[],int n)
{
	float sum_tat=0,sum_wt=0;
	int i;
	printf("\nTable \n\nProcess\tAT\tBT\tST\tFT\tTAT\tWT\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",a[i].pname,a[i].at,a[i].bt,a[i].st,a[i].ct,a[i].tat,a[i].wt);
		sum_tat+=a[i].tat;
		sum_wt+=a[i].wt;
	}
	printf("\nAvg TAT=%f\nAvg WT=%f\n",sum_tat/n,sum_wt/n);

	printf("\nGantt chart \n");
	for(i=0;i<n;i++)
	{
		printf("%d| %s  |%d\n",a[gantt_chart[i]].st,a[gantt_chart[i]].pname,a[gantt_chart[i]].ct);	
	}	
}
main()
{
	struct node a[10];
	int n;
	printf("Enter how many processes :");
	scanf("%d",&n);
	accept(a,n);
	sort(a,n);
	fcfs(a,n);
	display(a,n);
}

/*
Enter how many processes :4
Enter Process Name , Arrival Time & Burst Time :
p1 3 8
p2 2 4
p3 0 9
p4 1 5

Table

Process AT      BT      ST      FT      TAT     WT
p3      0       9       0       9       9       0
p4      1       5       9       14      13      8
p2      2       4       14      18      16      12
p1      3       8       18      26      23      15

Avg TAT=15.250000
Avg WT=8.750000

Gantt chart
0| p3  |9
9| p4  |14
14| p2  |18
18| p1  |26
*/
