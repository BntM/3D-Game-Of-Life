#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define xLen 3
#define yLen 10
#define zLen 10

//x coordinate drawing cells
int xCoordinate, yCoordinate;

//prints out the state of each cell
int visualize(bool cells[xLen][yLen][zLen]) {
    yCoordinate = 0;
    xCoordinate = 0;
    move(yCoordinate, xCoordinate);
    int cubesize = 10;
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < cubesize; y++) {
            for(int z = 0; z < cubesize; z++) {
                if(cells[x][y][z]) {
                    printw("* ");
                }
                else {
                    printw("- ");
                }
            }
            yCoordinate++;
            move(yCoordinate, xCoordinate);
        }
        yCoordinate = 0;
        xCoordinate += 22;
        move(yCoordinate, xCoordinate);
    }
    return 0;
}

//check Cells surrounding given for num of alive cells
int checkSurround(int midX, int midY, int midZ, bool cells[][10][10])
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

bool*** nextState(bool x[][10][10]);
int* cursorToCoordinate(int x[]);

int main()
{
    //initizlize screen
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    //initialize cells
    bool cells[3][10][10];
    for(int x = 0; x < 3; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            for(int z = 0; z < 10; z++)
            {
                cells[x][y][z] = false;
            }
        }
    }
    cells[2][2][2] = true;
    int c = getch();
    int cursorX = 0;
    int cursorY = 0;
    //get new state while input is not q
    while((c=getch()) != 'q')
    {
        clear();
        //visualize
        visualize(cells);
        memcpy(cells, nextState(cells), sizeof cells);
        int cursorx = cursorX/2;
        printw("%d, %d", cursorY, cursorX);
        int j[] = {cursorX, cursorY};
        int* cellLoc = cursorToCoordinate(j);
        printw(" %d, %d, %d" ,cellLoc[0], cellLoc[1], cellLoc[2]);
        //move cursor based on key input
        switch(c)
        {
            case KEY_UP:
                if(cursorY > 0)
                {
                    cursorY = cursorY - 1;
                    move(cursorY, cursorX);    
                    refresh();
                }
                break;
            case KEY_DOWN:
                cursorY = cursorY + 1;
                move(cursorY, cursorX);    
                refresh();
                break;
            case KEY_RIGHT:
                cursorX = cursorX + 2;
                move(cursorY, cursorX);    
                refresh();
                break;
            case KEY_LEFT:
                if(cursorX > 0)
                {
                    cursorX = cursorX - 2;
                    move(cursorY, cursorX);    
                    refresh();
                }
                break;
            //set cell at cursor to true or false
            case ',':
                move(10, 10);
                refresh();
                /*/cells[cellLoc[0]][cellLoc[1]][cellLoc[2]] = false;
                visualize(cells);
                break;*/
                break;
            case '.':
                cells[cellLoc[0]][cellLoc[1]][cellLoc[2]] = true;
                visualize(cells);
                break;
        }
    }
    //end ncurses
    getch();
    endwin();
    return 0;
}
//takes cursor location and returns cell location
int* cursorToCoordinate(int cursor[])
{
    int* outputArray = malloc(sizeof(int*) * 3);
    //x coordinate
    outputArray[0] = cursor[0]%11;
    //y coordinate
    outputArray[1] = 10 - cursor[1];
    // z coordinate
    outputArray[2]= cursor[0]/22;
    return outputArray;
}

bool*** nextState(bool cells[][10][10]){
    bool*** outputArray = malloc(sizeof(bool**) * 10);
    //change cell based on neighbours
    for(int x = 1; x < xLen - 1; x++)
    {
        outputArray[x] = malloc(sizeof(bool**) * 10);
        for(int y = 1; y < yLen - 1; y++)
        {
            outputArray[x][y] = malloc(sizeof(bool**) * 10);
            for(int z = 1; z < zLen - 1; z++)
            {
                int neighbours = checkSurround(x, y, z, cells);
                if(cells[x][y][z])
                {
                  //true = false if neighbours < 9 || > 18
                    if(neighbours < 9 && neighbours > 18)
                    {
                        outputArray[x][y][z] = false;
                    }
                }
                else
                {
                    //false = true if neighbours > 9 || < 18
                    if(neighbours > 9 && neighbours < 18)
                    {
                        outputArray[x][y][z] = true;
                    }
                }
            }
        }
    }
   return outputArray;
}
