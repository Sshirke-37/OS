#include<stdio.h>
int max[5][4],alloc[5][4],need[5][4],avail[4],np,nr;
int finish[5],safeseq[5],k=0;

void safety_algo()
{
	int i,j,b,cnt=0,flag=0;
	do
	{
	
		for(i=0;i<np;i++)
		{
			if(finish[i]==1)
			{
				continue;
			}
			for(j=0;j<nr;j++)
			{
				if(need[i][j]>avail[j])
				{
					break;
				}
			}
			if(j>=nr)
			{
				finish[i]=1;
				safeseq[k++]=i;
				for(b=0;b<nr;b++)
				{
					avail[b]=avail[b]+alloc[i][b];
				}
			}
		}
		cnt++;
	}while(cnt<=2);
	
	for(i=0;i<np;i++)
	{
		if(finish[i]==0)
			flag=1;
	}
	
	if(flag==1)
	{
		printf("System is in unsafe state ");
	}
	else
	{
		printf("System is in safe state and safe sequence is \n");
		for(i=0;i<np;i++)
		{
			printf("p%d ",safeseq[i]);
		}
	}
	
}

main()
{
	int ch,i,j;
	printf("Enter how many processes and resources?");
	scanf("%d%d",&np,&nr);
	
	for(i=0;i<np;i++)
	{
		finish[i]=0;
		safeseq[i]=-1;
	}
	
	
	do
	{
		printf("\nPress \n1. Accept Available \n2.Accept Max and Allocation \n3. Display Need \n4. Display All \n5. Safe Sequence \nEnter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:printf("Enter Available :");
					for(i=0;i<nr;i++)
					{
						scanf("%d",&avail[i]);
					}
					break;
			case 2:
					printf("Enter max matrix:\n");
					for(i=0;i<np;i++)
					{
						for(j=0;j<nr;j++)
						{
							scanf("%d",&max[i][j]);
						}
					}
					printf("Enter Allocation matrix:\n");
					for(i=0;i<np;i++)
					{
						for(j=0;j<nr;j++)
						{
							scanf("%d",&alloc[i][j]);
						}
					}
					break;
			case 3: 
					for(i=0;i<np;i++)
					{
						for(j=0;j<nr;j++)
						{
							need[i][j]=max[i][j]-alloc[i][j];
						}
					}
					printf("Need is\n");
					for(i=0;i<np;i++)
					{
						for(j=0;j<nr;j++)
						{
							printf("%d ",need[i][j]);
						}
						printf("\n");
					}
					break;
			case 4:	
					printf("max is\n");
					for(i=0;i<np;i++)
					{
						for(j=0;j<nr;j++)
						{
							printf("%d ",max[i][j]);
						}
						printf("\n");
					}
					printf("\nAllocation is\n");
					for(i=0;i<np;i++)
					{
						for(j=0;j<nr;j++)
						{
							printf("%d ",alloc[i][j]);
						}
						printf("\n");
					}
					
					printf("\n Available is\n");
					for(i=0;i<nr;i++)
					{
						printf("%d ",avail[i]);
					
					}
					break;
			case 5:
						safety_algo();
						break;
			default:exit(0);
			}
	}while(1);
	
}

/*
nrclasses@localhost$]./a.out
Enter how many processes and resources?5 3

Press
1. Accept Available
2.Accept Max and Allocation
3. Display Need
4. Display All
5. Safe Sequence
Enter your choice : 1
Enter Available :3 3 2

Press
1. Accept Available
2.Accept Max and Allocation
3. Display Need
4. Display All
5. Safe Sequence
Enter your choice : 2
Enter max matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter Allocation matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Press
1. Accept Available
2.Accept Max and Allocation
3. Display Need
4. Display All
5. Safe Sequence
Enter your choice : 3
Need is
7 4 3
1 2 2
6 0 0
0 1 1
4 3 1

Press
1. Accept Available
2.Accept Max and Allocation
3. Display Need
4. Display All
5. Safe Sequence
Enter your choice : 4
max is
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Allocation is
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

 Available is
3 3 2
Press
1. Accept Available
2.Accept Max and Allocation
3. Display Need
4. Display All
5. Safe Sequence
Enter your choice : 5
System is in safe state and safe sequence is
p1 p3 p4 p0 p2
Press
1. Accept Available
2.Accept Max and Allocation
3. Display Need
4. Display All
5. Safe Sequence
Enter your choice :
*/
