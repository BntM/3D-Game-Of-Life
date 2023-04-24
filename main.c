#include <stdio.h>
#include <stdbool.h>

//Prints out the state of each cell
int visualize(bool cells[10][10][10]) {
    int cubeSize = 10;
    for(int x = 0; x < cubeSize; x++) {
        printf("X");
        printf("%d", x);
        printf("\n");
        for(int y = 0; y < cubeSize; y++) {
            printf("Y");
            printf("%d", y);
            for(int z = 0; z < cubeSize; z++) {
                printf(" Z");
                printf("%d", z);
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
int checkSurround(int midX, int midY, int midZ, bool cells[10][10][10])
   {
      int count = 0;
      for(int x = midX - 1; x <= midX + 1; x++)
      {
         for(int y = midY - 1; y <= midY + 1; y++)
         {
             for(int z = midZ - 1; y <= midZ + 1; z++)
             {
               if(!(x == midX && y == midY && z == midZ) && cells[x][y][z]){
                  count++;
               }
             }
         }
      }
      return count;
    }

int main()
{
    printf("Hello World\n");
    //initialize cells
    bool cells[10][10][10];
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            for(int z = 0; z < 10; z++)
            {
                cells[x][y][z] = false;
            }
        }
    }
    visualize(cells);
   //change cell based on neighbours
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            for(int z = 0; z < 10; z++)
            {
                int neighbours = checkSurround(x, y, z, cells);
                if(cells[x][y][z])
                {
                  //true = false if neighbours < 9 || > 18
                    if(neighbours < 9 || neighbours > 18)
                    {
                        cells[x][y][z] = false;
                    }
                }
                else
                {
                  //false = true if neighbours > 9 || < 18
                    if(neighbours > 9 || neighbours < 18)
                    {
                        cells[x][y][z] = true;
                    }
                }
            }
        }
    }
    return 0;
}