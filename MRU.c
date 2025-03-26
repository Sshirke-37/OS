//MRU Implementation

#include<stdio.h>

int ref_st[20],len_rs,frames[5][2],no_of_frames;
int page_fault=0,tm=0;

int searchpage(int p)
{
	int i;
	for(i=0;i<no_of_frames;i++)
	{
		if(p==frames[i][0])
		{
			frames[i][1]=++tm;
			return 0;
		}
	}
	return 1;
}

int MRU()
{
	int i,max=-1000,ind;
	for(i=0;i<no_of_frames;i++)
	{
		if(frames[i][1]>max)
		{
			max=frames[i][1];
			ind=i;
		}
	}
	return ind;
}

int findfreeframe()
{
	int i;
	for(i=0;i<no_of_frames;i++)
	{
		if(frames[i][0]==-2)
		{
			return i;
		}
	}
	i=MRU();
	return i;
}

void display()
{
	int i;
	for(i=0;i<no_of_frames;i++)
	{
		printf(" %d |",frames[i][0]);
	}
	printf("\n");
}

main()
{
	int i,s,ind;
	
	printf("Enter length of Reference String :");
	scanf("%d",&len_rs);
	printf("\n Enter Reference String :\n");
	for(i=0;i<len_rs;i++)
	{
		scanf("%d",&ref_st[i]);
	}
	printf("Enter number of frames :");
	scanf("%d",&no_of_frames);
	
	for(i=0;i<no_of_frames;i++)
	{
		frames[i][0]=-2;
		frames[i][1]=0;
	}
	
	for(i=0;i<len_rs;i++)
	{
		display();
		s=searchpage(ref_st[i]);
		if(s==1)
		{
			page_fault++;
			ind=findfreeframe();
			frames[ind][0]=ref_st[i];
			frames[ind][1]=++tm;
		}
	}
	printf("\n Total page faults are %d",page_fault);
	
}
