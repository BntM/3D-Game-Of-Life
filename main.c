#include <stdio.h>
#include <stdbool.h>
int main()
{
    printf("Hello World\n");
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
               if(cells[x][y][z]) 
               {
                
               }
               else
               {

               }
            }
        }
    }
    return 0;
}
int checkSurround(int row, int col)
   {  
      int count = 0;
      for(int x = row - 1; x <= row + 1; x++)
      {
         for(int y = col - 1; y <= col + 1; y++)
         {
            for(int z = )
            if([x][y][z]){
               if(!(r == row && c == col)){
                  count++;
               }
            }
         }
        
      }
      return count;
   }