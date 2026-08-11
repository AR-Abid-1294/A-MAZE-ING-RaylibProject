#include<stdio.h> //for printing and others
#include<stdlib.h> // for rand() & srand()
#include<time.h> // for time(NULL)
#define mazewidth 25 //a odd number (2*mazeboxesinwidth+1)
#define mazeheight 15 // another odd number()

int maze[mazeheight][mazewidth];
int dir[4][2] = {{2,0},{-2,0},{0,2},{0,-2}}; //down, up, right, left (i,j)=(y,x)

//To initially create every cell and wall as 1(wall)
void initialize_maze()
{
    for(int i=0; i<mazeheight;i++)
        for(int j=0; j<mazewidth;j++)
            maze[i][j]=1;
}

//To print maze at the end or whenever I feel like it
void print_maze()
{
    for(int i=0; i<mazeheight;i++)
    {
        for(int j=0; j<mazewidth;j++)
            if(maze[i][j]==1)
                printf("# "); // one space extra to be visually pleasing
            else
                printf("  "); // same logic here, net two space here

        printf("\n");
    }
}

void shuffle_dir(int dir[4][2])
{
    for(int i=0; i<4;i++)
    {
        int r = rand() % 4;
        int tempy = dir[i][0];
        int tempx = dir[i][1];
        dir[i][0] = dir[r][0];
        dir[i][1] = dir[r][1];
        dir[r][0] = tempy;
        dir[r][1] = tempx;
    }
}
int isvalid(int y, int x)
{
    if(y > 0 && y < mazeheight-1 && x > 0 && x < mazewidth-1) //to keep the room inside the maze
        return 1;
    return 0; // the room cannot be in the border or outside the border
    // though if we don't give shitty initial position of the room, it cannot get in the border, need to check!! ans:
    // Since we start at an odd coordinate and always move by 2,
    // the algorithm can only visit odd coordinates.
    // Therefore, the border (0 and mazewidth-1 / mazeheight-1)
    // cannot normally be reached.
    // Still, isvalid() protects us against invalid positions.
}
void generate_maze(int y, int x)
{
    maze[y][x] = 0; //starting the maze || getting the room checked

    shuffle_dir(dir);
    
    for(int i = 0; i<4; i++)
    {
        int newx = x + dir[i][1];
        int newy = y + dir[i][0];
        if(isvalid(newy, newx) && maze[newy][newx] == 1)
        {
            maze[y + dir[i][0] /2][x + dir[i][1]/2] = 0; //breaking the wall
            generate_maze(newy,newx);
        }
        
    }
}


int main()
{
    srand(time(NULL)); // Seeding random numbers
    initialize_maze(); // To keep every cell unchecked(1) and and every wall intact(1)  

    generate_maze(1,1);// Isn't it obvious?

    print_maze();// same here!!!

    return 0;
}