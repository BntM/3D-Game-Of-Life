#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define xLen 5
#define yLen 10
#define zLen 10

struct node
{
    bool cells[5][10][10];
    struct node *next;
    struct node *previous;
};


//x coordinate drawing cells
int xCoordinate, yCoordinate;

//prints out the state of each cell
int visualize(bool cells[xLen][yLen][zLen]) {
    yCoordinate = 0;
    xCoordinate = 0;
    move(yCoordinate, xCoordinate);
    int cubesize = 10;
    for(int x = 1; x < 4; x++) {
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

//return number of live neighbouring cells given cell coordinate
int checkSurround(int midX, int midY, int midZ, bool cells[][10][10])
{
    int count = 0;
    for(int x = midX - 1; x <= midX + 1; x++)
    {
        for(int y = midY - 1; y <= midY + 1; y++)
        {
            for(int z = midZ - 1; z <= midZ + 1; z++)
            {
            if(!(x == midX && y == midY && z == midZ) && cells[x][y][z]){
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
    bool cells[5][10][10];
    bool outputArray[5][10][10];
    for(int x = 0; x < 5; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            for(int z = 0; z < 10; z++)
            {
                cells[x][y][z] = false;
            }
        }
    }
    int cursorX = 0;
    int cursorY = 0;
    int c = ' ';
    int* cellLoc;

    //pointers for double linked list
    struct node *head = NULL;
    struct node *first = NULL;
    struct node *temp = NULL;
    struct node *tail = NULL;
    //get initial state of cells
    while(c != 'q')
    {
        clear();
        visualize(cells);
        switch(c)
        {
            case KEY_UP:
                if(cursorY > 0)
                {
                    cursorY = cursorY - 1;
                }
            break;
            case KEY_DOWN:
                cursorY = cursorY + 1;
            break;
            case KEY_RIGHT:
                cursorX = cursorX + 2;
            break;
            case KEY_LEFT:
                if(cursorX > 0)
                {
                    cursorX = cursorX - 2;
                }
            break;
            //set cell at cursor to true or false
            case ',':
                cells[cellLoc[2]][cellLoc[1]][cellLoc[0]] = true;
                memcpy(cells, cells, sizeof cells);
                printw("%s", cells[cellLoc[0]][cellLoc[1]][cellLoc[2]]?"true":"false");
                break;
            case '.':
                cells[cellLoc[2]][cellLoc[1]][cellLoc[0]] = false;
                memcpy(cells, cells, sizeof cells);
                printw("%s", cells[cellLoc[0]][cellLoc[1]][cellLoc[2]]?"true":"false");
                break;
        }
        visualize(cells);
        printw("(%d, %d)", cursorY, cursorX);
        int j[] = {cursorX, cursorY};
        cellLoc = cursorToCoordinate(j);
        printw(" (%d, %d, %d)" ,cellLoc[1], cellLoc[0], cellLoc[2] - 1);
        int neighbours = checkSurround(cellLoc[2], cellLoc[1], cellLoc[0], cells);
        printw("|%d", neighbours);
        move(cursorY, cursorX);
        c=getch();
        refresh();
    }
    c = getch();
    while(c != 'q')
    {
        clear();
        //change cell based on neighbours
        for(int x = 1; x < xLen - 1; x++)
        {
            for(int y = 1; y < yLen - 1; y++)
            {
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
        struct node *current = (struct node*) malloc(sizeof(struct node));
        memcpy(cells, outputArray, sizeof cells);
        memcpy(&current->cells, outputArray, sizeof cells);
        //double linked list to navigate to differnet states(in progress)
        if(head == NULL)
        {
            head = current;
            first = head;
            tail = head;
        }
        temp = current;
        first->next = temp;
        temp->previous = first;
        first = temp;
        tail = temp;

        visualize(outputArray);
        //print 2d coordinates
        printw("(%d, %d)", cursorY, cursorX);
        int j[] = {cursorX, cursorY};
        cellLoc = cursorToCoordinate(j);
        //print cell location
        printw(" (%d, %d, %d)" ,cellLoc[1], cellLoc[0], cellLoc[2] - 1);
        //get new input
        c=getch();
        refresh();
    }
    //end ncurses
    endwin();
    return 0;
}
//takes cursor location and returns cell location
int* cursorToCoordinate(int cursor[])
{
    int* outputArray = malloc(sizeof(int*) * 5);
    //x coordinate
    outputArray[0] = (cursor[0]%22)/2;
    //y coordinate
    outputArray[1] = cursor[1];
    // z coordinate
    outputArray[2]= cursor[0]/22 + 1;
    return outputArray;
}

//return next state of of cells based on previous cells
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
