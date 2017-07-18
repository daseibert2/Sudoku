#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define CELLS 81
#define RC 9

int find_unassigned(int grid[RC][RC], int *r, int *c)   //finds locations that equal 0
{
	for (*r=0;*r<RC;(*r)++)
    {
		for (*c=0;*c<RC;(*c)++)
		{
			if (grid[*r][*c]==0)
			{
				return 1;
			}
		}
	}
	return 0;
}

int checkRow(int grid[RC][RC],int r, int num)           //checks all #s in row
{
    int c;

    for(c=0;c<RC;c++)
    {
        if(grid[r][c]==num)
        {
            return 1;
        }
    }
    return 0;
}

int checkCol(int grid[RC][RC],int c, int num)           //checks all #s in column
{
    int r;

    for(r=0;r<RC;r++)
    {
        if(grid[r][c]==num)
        {
            return 1;
        }
    }
    return 0;
}

int checkBox(int grid[RC][RC],int start_r,int start_c, int num)    //checks all #s in box area
{
    int r,c;

    for(r=0;r<RC/3;r++)
    {
       for(c=0;c<RC/3;c++)
       {
            if(grid[r+start_r][c+start_c]==num)
            {
                return 1;
            }
        }
    }
    return 0;
}

int goodNum(int grid[RC][RC],int r,int c,int num)
{
    return !checkRow(grid,r,num)                    //checks all #s in row
        &&!checkCol(grid,c,num)                     //checks all #s in column
        &&!checkBox(grid,r-(r%3),c-(c%3),num);      //checks all #s in box area
}

void printGrid(int grid[9][9])
{
    int i, j;

    printf("-------------------------------\n");
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 10; j++)
        {

            if(j == 9)
                printf("\n");
            else if(j == 0) {
                if(grid[i][j] == 0)
                    printf("| .  ");
                else
                printf("| %d  ", grid[i][j]);
            }
            else if(j == 2 || j == 5 || j == 8) {
                if(grid[i][j] == 0)
                    printf(". | ");
                else
                    printf("%d | ", grid[i][j]);
            }
            else
            {
                if(grid[i][j] == 0)
                    printf(".  ");
                else
                    printf("%d  ", grid[i][j]);
            }
            if((i == 2 && j == 9)||(i == 5 && j == 9))
                printf("-------------------------------\n");

        }
    }
    printf("-------------------------------\n");
}

int solve(int grid[RC][RC])             //runs all checking functions
{
    int r,c,num;

    if (!find_unassigned(grid, &r, &c)) //finds locations that equal 0
    {
		return 1;
	}
	for(num=1;num<=RC;num++)            //goes through every possible # -> 1-9
    {
        if(goodNum(grid,r,c,num))       //runs all location-based checking function
        {
            grid[r][c]=num;             //reassigns location's value

            if(solve(grid))             //recursion
            {
                return 1;
            }

            grid[r][c]= 0;
        }
    }
    return 0;
}

int main()
{
    int grid[9][9]=             //creating sudoku board
    {
        {0,0,5,3,0,0,0,0,0},
        {8,0,0,0,0,0,0,2,0},
        {0,7,0,0,1,0,5,0,0},
        {4,0,0,0,0,5,3,0,0},
        {0,1,0,0,7,0,0,0,6},
        {0,0,3,2,0,0,0,8,0},
        {0,6,0,5,0,0,0,0,9},
        {0,0,4,0,0,0,0,3,0},
        {0,0,0,0,0,9,7,0,0}
    };

    /*int grid[9][9]=
    {
        {0,5,4,0,0,0,0,8,0},
        {0,0,0,8,4,0,0,2,6},
        {0,8,0,0,0,0,4,0,0},
        {0,0,6,3,0,0,5,0,0},
        {1,0,0,0,0,0,0,0,3},
        {0,0,8,0,0,2,9,0,0},
        {0,0,3,5,0,0,0,1,0},
        {8,2,0,0,7,1,0,0,0},
        {0,4,0,0,0,0,6,5,0}
    };*/

    printf("\nUnsolved Puzzle:\n\n");
    printGrid(grid);
    printf("\n\n\n");

    if(solve(grid))
    {
        printf("Solved Puzzle:\n\n");
        printGrid(grid);
    }
    else
    {
        printf("No Solution");
    }

    return 0;
}
