#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define xLen 4
#define yLen 4
#define zLen 4

//https://github.com/3DSage/OpenGL-Starter_v1

//Prints out the state of each cell
int visualize(bool cells[4][4][4]) {
    int cubeSize = 4;
    for(int x = 0; x < cubeSize; x++) {
        printf("X");
        printf("%d", x);
        printf("\n");
        for(int y = 0; y < cubeSize; y++) {
            printf("Y");
            printf("%d", y);
            for(int z = 0; z < cubeSize; z++) {
                //printf(" Z");
                //printf("%d", z);
                printf(": ");
                if(cells[x][y][z]) {
                    printf("1");
                }
                else {
                    printf("0");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}

//chekc Cells surrounding given for num of alive cells
int checkSurround(int midX, int midY, int midZ, bool* cells)
{
    int count = 0;
    for(int x = midX - 1; x <= midX + 1; x++)
    {
        for(int y = midY - 1; y <= midY + 1; y++)
        {
            for(int z = midZ - 1; z <= midZ + 1; z++)
            {
            if(!(x == midX && y == midY && z == midZ) && cells[(x * xLen) + (y * yLen) + z]){
                count++;
            }
            }
        }
    }
    return count;
}
bool* nextState(bool* cells);

int main()
{
    printf("Hello World\n");
    //initialize cells
    bool cells[4][4][4];
    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            for(int z = 0; z < 4; z++)
            {
                cells[x][y][z] = false;
            }
        }
    }
    for(int i = 0; i < 3; i++)
    {
        visualize(cells);
        nextState(*cells[0]);
    }
    return 0;
}
bool* nextState(bool* cells)
{
   //change cell based on neighbours
    for(int x = 1; x < xLen - 1; x++)
    {
        for(int y = 1; y < yLen - 1; y++)
        {
            for(int z = 1; z < zLen - 1; z++)
            {
                int neighbours = checkSurround(x, y, z, cells);
                if(cells[(x * xLen) + (y * yLen) + z])
                {
                  //true = false if neighbours < 9 || > 18
                    if(neighbours < 9 && neighbours > 18)
                    {
                        printf("%d %d %d\n",x , y, z);
                        cells[(x * xLen) + (y * yLen) + z] = false;
                    }
                }
                else
                {
                  //false = true if neighbours > 9 || < 18
                    if(neighbours > 9 && neighbours < 18)
                    {
                        printf("%d %d %d : %d\n",x , y, z, neighbours);
                        cells[(x * xLen) + (y * yLen) + z] = true;
                    }
                }
            }
        }
    }
   return cells;
}
