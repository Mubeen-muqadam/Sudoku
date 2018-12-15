#include<stdio.h>

#define BIT_RESET(_BITMAP_, _BIT_)   (_BITMAP_= _BITMAP_& (~(1<<(_BIT_-1))))

// if only bit is set BITMAP & BITMAP-1 will always be 0
#define TEST_ONLY_BIT_SET(_BITMAP_) (_BITMAP_ && ! (_BITMAP_ & _BITMAP_-1))

int grid[9][9]= {     
        {0, 7, 6,  0, 5, 0, 1, 4,0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
        {8, 3, 0, 7, 0, 6, 0 , 5, 9},
        {0, 8, 4, 0, 0, 0,  7, 3, 0},
        {0, 0, 0, 3, 0, 8, 0, 0, 0},
        {0, 9, 3, 0, 0, 0, 5, 2, 0},
        {3, 1, 0, 5, 0, 2, 0, 9, 6},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 9, 0, 7, 0, 8, 1, 0}
        };
		
int gridBitMap[9][9];
int subGridMap[3][3];
int rowBitMap[9];
int columnBitmap[9];		
		
		
void printGrid(int *);
void buildRowBitMap(int * grid);
void buildColumnBitMap(int * grid);
void buildSubGridBitMap(int *grid);
void buildGridBitMap(int * grid);
void scanAndPopulate();

int getDigitfromBitmask( int mask)
{
	switch(mask)
	{
		case 1: return 1;
		case 2: return 2;
		case 4: return 3;
		case 8: return 4;
		case 16: return 5;
		case 32: return 6;
		case 64: return 7;
		case 128: return 8;
		case  256: return 9;
		default: return -1;
	}
}

int main()
{

	printGrid((int *)grid);
    buildGridBitMap((int *) grid);
	scanAndPopulate();
}


void buildSubGridBitMap(int *grid)
{
    int i=0, j=0;
	
	for(i=0;i<3;i++)
	{
	    for(j=0;j<3;j++)
	    {
		     subGridMap[i][j]=0x1FF;
		}
	}	
    for(i=0;i<9;i++)
	    for(j=0;j<9;j++) 
		{
			       BIT_RESET(subGridMap[i/3][j/3], *(grid+(i*9)+j));	
		}  
}


void buildRowBitMap(int * grid)
{
   int i=0;
   int j=0;
	//for each row in the grid
	for(i=0; i < 9; i++)
	{	
	     //set all 9 bits to true in rowBitMap
		 rowBitMap[i] = 0x1FF;
		 
     	//scan the cells, reset the bit for which number is found
		for(j=0; j< 9; j++)
		{
		      BIT_RESET(rowBitMap[i], *(grid+(i*9)+j));	
		} 
//		printf("row num %d,  bitmap 0x%x\n", i, rowBitMap[i]);
    }	
}

void buildColumnBitMap(int * grid)
{
   int i=0;
   int j=0;
	
	//for each column in the grid
	for(i=0; i < 9; i++)
	{	
	     //set all 9 bits to true in columnBitmap
		 columnBitmap[i] = 0x1FF;
		 
     	//scan the cells, reset the bit for which number is found
		for(j=0; j< 9; j++)
		{
		      BIT_RESET(columnBitmap[i], *(grid+i+(j*9)));	
		} 
	//	printf("colmun num %d,  bitmap 0x%x\n", i, columnBitmap[i]);
    }
}

void buildGridBitMap(int *pgrid)
{
	int i=0;
    int j=0;
	
	buildRowBitMap(pgrid);
	buildColumnBitMap(pgrid);
	buildSubGridBitMap(pgrid);
	
	for(i=0; i < 9; i++)
	{	
		for(j=0; j< 9; j++)
		{
		      if(*(pgrid+(i*9)+j))
			       gridBitMap[i][j] = 0;
              else
			  {
				   gridBitMap[i][j] = rowBitMap[i] & columnBitmap[j] & subGridMap[i/3][j/3];	
			   }
		} 
    }
	
}
void scanAndPopulate()
{
    int i=0;
    int j=0;
	int copygrid[9][9];
	int resultFound=0;
	int count=0;
	for(i=0; i < 9; i++)
	{	
	    for(j=0; j< 9; j++)
	    {
             copygrid[i][j]=grid[i][j];		     
	    }
	}
	
	//repeat until we are not making progress
    do
    {
	     resultFound=0;
	     for(i=0; i < 9; i++)
	     {	
		     for(j=0; j< 9; j++)
		     {
			     if (!copygrid[i][j] && TEST_ONLY_BIT_SET(gridBitMap[i][j]))
			     {

				     // cell (i,j) has confirmed digit at this point, we should populate this and update respective row and column Bitmaps
					 copygrid[i][j]=getDigitfromBitmask( gridBitMap[i][j]);
					 buildGridBitMap((int *) copygrid);
					 resultFound=1;
					 //printGrid((int *) copygrid);
			     }
		    } 
        }
		count++;
	}while(resultFound);
    
	printGrid((int *) copygrid);
	printf("took %d count", count);
}

void printGrid(int * ppgrid)
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
			   
           if(*(ppgrid+(i*9)+j)==0)
               printf(". ");
          else
             printf("%d ",*(ppgrid+(i*9)+j));
        
	       if((j+1)%3==0 )
              printf("| ");
        }

        if((i+1)%3==0 )
             printf("\n\t-------------------------");

        printf("\n");
    }
 }
