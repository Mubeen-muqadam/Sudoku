#include<stdio.h>
int grid[9][9]= {     {0, 0, 5, 3, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 2, 0},
        {0, 7, 0, 0, 1, 0, 5, 0, 0},
        {4, 0, 0, 0, 0, 5, 3, 0, 0},
        {0, 1, 0, 0, 7, 0, 0, 0, 6},
        {0, 0, 3, 2, 0, 0, 0, 8, 0},
        {0, 6, 0, 5, 0, 0, 0, 0, 9},
        {0, 0, 4, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 9, 7, 0, 0}
        };
void printGrid();


int main()
{
	printGrid();
}


void printGrid()
{

 int i =0;
 int j=0;

 printf("\t-------------------------\n");
 for(i=0;i<9;i++)
 {
    printf("\t");
    for(j=0;j<9;j++)
	{
       if(j==0)
           printf("| ");
       if(grid[i][j]==0)
             printf(". ");
       else
             printf("%d ",grid[i][j]);
       if((j+1)%3==0 )
            printf("| ");
    }

    if((i+1)%3==0 )
       printf("\n\t-------------------------");

   printf("\n");
  }
 }
