#include<stdio.h>
int max[5][4],alloc[5][4],need[5][4],avail[4],np,nr;

main()
{
	int ch,i,j;
	printf("Enter how many processes and resources?");
	scanf("%d%d",&np,&nr);
	do
	{
		printf("\nPress \n1. Accept Available \n2.Accept Max and Allocation \n3. Display Need \n4. Display All \nEnter your choice : ");
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
			default:exit(0);
			}
	}while(1);
	
}
