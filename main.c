#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define xLen 4
#define yLen 4
#define zLen 4

//prints out the state of each cell
int visualize(bool cells[xLen][yLen][zLen]) {
    int cubesize = 4;
    for(int x = 0; x < cubesize; x++) {
        //printw("%d", x);
        for(int y = 0; y < cubesize; y++) {
            //printw("y");
            //printw("%d", y);
            for(int z = 0; z < cubesize; z++) {
                //printw(" z");
                //printw("%d", z);
                //printw(": ");
                if(cells[x][y][z]) {
                    printw("*");
                }
                else {
                    printw("-");
                }
            }
            printw("\n");
        }
        printw("\n");
    }
    printw("\n");
    
    return 0;
}

//chekc Cells surrounding given for num of alive cells
int checkSurround(int midX, int midY, int midZ, bool cells[][4][4])
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
bool*** nextState(bool x[][4][4]);

int main()
{
    //initizlize screen
    initscr();
    cbreak();
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
    cells[2][2][2] = true;
    for(int i = 0; i < 1; i++)
    {
        //visualize
        visualize(cells);
        memcpy(cells, nextState(cells), sizeof cells);
    }
    //end ncurses
    refresh();
    getch();
    endwin();
    return 0;
}
bool*** nextState(bool cells[][4][4]){
    bool*** outputArray = malloc(sizeof(bool**) * 4);
   //change cell based on neighbours
    for(int x = 1; x < xLen - 1; x++)
    {
        outputArray[x] = malloc(sizeof(bool**) * 4);
        for(int y = 1; y < yLen - 1; y++)
        {
            outputArray[x][y] = malloc(sizeof(bool**) * 4);
            for(int z = 1; z < zLen - 1; z++)
            {
                int neighbours = checkSurround(x, y, z, cells);
                if(cells[x][y][z])
                {
                  //true = false if neighbours < 9 || > 18
                    if(neighbours < 9 && neighbours > 18)
                    {
                        //printw("%d %d %d\n",x , y, z);
                        outputArray[x][y][z] = false;
                    }
                }
                else
                {
                  //false = true if neighbours > 9 || < 18
                    if(neighbours > 9 && neighbours < 18)
                    {
                        //printw("%d %d %d : %d\n",x , y, z, neighbours);
                        outputArray[x][y][z] = true;
                    }
                }
            }
        }
    }
   return outputArray;
}
