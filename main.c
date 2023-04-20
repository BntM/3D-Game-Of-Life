#include <stdio.h>
#include <stdbool.h>

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

    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            for(int z = 0; z < 10; z++)
            {
                int neighbours = checkSurround(x, y, z, cells);
                if(cells[x][y][z])
                {
                    if(neighbours < 7 || neighbours > 20)
                    {
                        cells[x][y][z] = false;
                    }
                }
                else
                {
                    if(neighbours > 7 || neighbours < 20)
                    {
                        cells[x][y][z] = true;
                    }
                }
            }
        }
    }
    return 0;
}
