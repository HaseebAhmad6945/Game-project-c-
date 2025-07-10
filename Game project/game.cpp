#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string>
#include<iomanip>
using namespace std;
char maze[20][20]=
{
{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', 'x', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'e', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', ' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};
int playerX, playerY;
int score = 0;
int lives = 3;
struct Enemy
{
int x,y;
int direction;
bool active;
};
Enemy enemies[5];
int numEnemies =0;
int enemiesRemaining =0;
HANDLE hOutput;
CHAR_INFO *buffer;
COORD bufferSize = {20, 21};
COORD characterPos = {0, 0};
SMALL_RECT writeRegion = {0, 0, 19, 20};
void setupConsole();
void drawBuffer();
void updateBuffer();
void findPlayer();
void addEnemy(int y,int x);
void movePlayer(int newY,int newX);
void fire();
void moveEnemies();
void resetPlayerPosition();
int main()
{
system("CLS");
setupConsole();
findPlayer();
addEnemy(7, 3);
addEnemy(10, 9);
addEnemy(3, 18);
addEnemy(2, 3);
addEnemy(4, 18);
enemiesRemaining=numEnemies;
while(lives>0&&enemiesRemaining>0)
{
updateBuffer();
drawBuffer();
if(_kbhit())
{
char input=_getch();
switch(input)
{
case 72:
movePlayer(playerY-1,playerX);
break;
case 80:
movePlayer(playerY+1,playerX);
break;
case 77:
movePlayer(playerY,playerX+1);
break;
case 75:
movePlayer(playerY,playerX-1);
break;
case ' ':
fire();
break;
case 'q':
lives = 0;
break;
}
}
moveEnemies();
Sleep(150);
}
delete[] buffer;
system("CLS");
cout<<endl;
system("CLS");
cout<<endl;
if(enemiesRemaining ==0)
{
cout<<"Congratulations! All enemies defeated!"<<endl;
} else 
{
 cout<<"Game Over! You ran out of lives."<<endl;
}
cout<<"Final Score: "<<score<<endl;
return 0;
}
void setupConsole()
{
hOutput =GetStdHandle(STD_OUTPUT_HANDLE);
buffer =new CHAR_INFO[bufferSize.X *bufferSize.Y];
for(int i=0;i <bufferSize.X*bufferSize.Y;++i)
{
buffer[i].Char.AsciiChar = ' ';
buffer[i].Attributes=FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED;
}
}
void updateBuffer()
{
for(int i=0; i<bufferSize.X*bufferSize.Y;++i)
{
buffer[i].Char.AsciiChar =' ';
buffer[i].Attributes=FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED;
}
 for(int i=0;i<20;i++) 
{
 for(int j=0;j<20;j++) 
{ 
int bufferRow =i+1; 
int index =bufferRow*bufferSize.X +j;
buffer[index].Char.AsciiChar=maze[i][j];
buffer[index].Attributes=FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED; 
}
}
    int playerBufferY = playerY + 1; // Adjust player's buffer Y position
    int playerIndex = playerBufferY * bufferSize.X + playerX;
    buffer[playerIndex].Char.AsciiChar = 'P';
    buffer[playerIndex].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY; // Bright Red
    for (int i =0;i<numEnemies;++i)
    {
        if(enemies[i].active)
        { // Only draw active enemies
            int enemyBufferY = enemies[i].y + 1; // Adjust enemy's buffer Y position
            int enemyIndex = enemyBufferY * bufferSize.X + enemies[i].x;
            buffer[enemyIndex].Char.AsciiChar = 'e';
            buffer[enemyIndex].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY; // Bright Green
        }
    }
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(maze[i][j] == 'x')
            {
                int obstacleBufferY = i + 1; // Adjust obstacle's buffer Y position
                int obstacleIndex = obstacleBufferY * bufferSize.X + j;
                buffer[obstacleIndex].Char.AsciiChar = 'x';
                buffer[obstacleIndex].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY; // Bright Magenta
            }
        }
    }
    //Update score and lives display
    string scoreStr = "Score: " + to_string(score);
    string livesStr = "Lives: " + to_string(lives);   
    //Calculate total length of both strings
    int totalLen = scoreStr.length() + livesStr.length() + 1;    
    int startCol = bufferSize.X - totalLen; 
    //Write score string to the buffer
    for(int i=0;i<scoreStr.length();++i)
    {
        buffer[0 * bufferSize.X + startCol + i].Char.AsciiChar = scoreStr[i];
        buffer[0 * bufferSize.X + startCol + i].Attributes = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN; // Yellow color
    }    
    //Add a space between score and lives
    buffer[0 * bufferSize.X + startCol + scoreStr.length()].Char.AsciiChar = ' ';
    //Write lives string to the buffer at row 0, after the score and the space
    for (int i = 0; i < livesStr.length(); ++i) {
        buffer[0 * bufferSize.X + startCol + scoreStr.length() + 1 + i].Char.AsciiChar = livesStr[i];
        buffer[0 * bufferSize.X + startCol + scoreStr.length() + 1 + i].Attributes = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN; // Yellow color
    }
}
void drawBuffer() {
    WriteConsoleOutputA(hOutput, buffer, bufferSize, characterPos, &writeRegion);
}
void findPlayer()
{
    for(int i=0;i<20;i++)
    {
        for(int j =0;j<20;j++)
        {
            if(maze[i][j]=='P')
            {
                playerY = i;
                playerX = j;
                return; //Player found,exit function
            }
        }
    }
}
// Adds an enemy to the game at the specified coordinates.
void addEnemy(int y, int x)
{
    if (numEnemies < 5)
    {
        enemies[numEnemies].y = y;
        enemies[numEnemies].x = x;
        enemies[numEnemies].direction = 1;
        enemies[numEnemies].active = true;
        maze[y][x] = 'e'; 
        numEnemies++;
    }
}
void resetPlayerPosition() {
    maze[playerY][playerX] = ' ';
    playerY = 18; 
    playerX = 5; 
    maze[playerY][playerX] = 'P'; 
}
void movePlayer(int newY, int newX) 
{
    if(newY>=0&&newY<20&&newX>=0&&newX<20&&maze[newY][newX]!='#')
    {
        if (maze[newY][newX] == 'e') 
        {
            lives--;  // Lose a life when player directly collides with an enemey
            resetPlayerPosition(); //Reset player to start
            return;               //Player collided, no further movement
        }        
        maze[playerY][playerX] = ' ';
        playerY = newY;
        playerX = newX;       
        maze[playerY][playerX] = 'P';
    }
}
void fire() 
{
    int bulletX = playerX;
    int bulletY = playerY - 1;
    while (bulletY >= 0) 
    { 
        if(bulletY+1<20&&maze[bulletY+1][bulletX]=='.')
        {
            maze[bulletY + 1][bulletX] = ' ';
        }
        char charAtBulletPos = maze[bulletY][bulletX]; 
        if (charAtBulletPos == '#') 
        {
            break; 
        }
        if (charAtBulletPos == 'x') 
        {
            maze[bulletY][bulletX] = ' '; 
            score += 50;                  
            break;                    
        }
        bool hitEnemy = false;
        for(int i=0;i<numEnemies;++i)
        {
            if(enemies[i].active&&enemies[i].y==bulletY&&enemies[i].x==bulletX)
            {
                enemies[i].active = false;   
                enemiesRemaining--;          
                maze[bulletY][bulletX] = ' '; 
                score += 5;                  
                hitEnemy = true;
                break;                       
            }
        }
        if (hitEnemy) 
        {
            break;
        }
        maze[bulletY][bulletX] = '.';
        updateBuffer(); 
        drawBuffer();
        Sleep(50); //control bullet speed
        bulletY--; // Move bullet up one step
    }
    if (bulletY + 1 < 20) 
    { 
        if(maze[bulletY + 1][bulletX] == '.') 
        { 
            maze[bulletY+1][bulletX]=' '; 
        }
    }
}
void moveEnemies() 
{
    for(int i=0;i<numEnemies;++i)
    {
        if (!enemies[i].active) 
        {
            if (maze[enemies[i].y][enemies[i].x] == 'e') 
            {
                maze[enemies[i].y][enemies[i].x] = ' ';
            }
            continue; 
        }
        int currentY = enemies[i].y;
        int currentX = enemies[i].x;
        int nextY = currentY + enemies[i].direction;
        if (nextY >= 1 && nextY < 19 && maze[nextY][currentX] != '#') 
        {
            if (nextY == playerY && currentX == playerX) 
            {
                lives--;              // Lose a life
                resetPlayerPosition(); // Reset player to start
                enemies[i].direction *= -1; // Enemy reverses direction upon collision               
                maze[currentY][currentX] = ' ';
                continue;
            }
            bool hitAnotherEnemy = false;
            for (int k = 0; k < numEnemies; ++k) 
            {
                if (k != i && enemies[k].active && enemies[k].y == nextY && enemies[k].x == currentX) {
                    hitAnotherEnemy = true;
                    break;
                }
            }
            if (hitAnotherEnemy) 
            {
                enemies[i].direction *= -1; // Reverse direction if hitting another enemy
                continue;                  // Skip to the next enemy, this one just bounced
            }
            // Clear old enemy position in the maze array
            maze[currentY][currentX] = ' ';
            // Update enemy's position in the struct and maze array
            enemies[i].y = nextY;
            maze[nextY][currentX] = 'e';
        } else {
            // If hitting a wall or vertical boundary, reverse direction
            enemies[i].direction *= -1;
        }
    }
}