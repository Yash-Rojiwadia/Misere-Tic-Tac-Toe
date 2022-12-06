#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>


int board[3][3];	// board for gameplay
int turn;			// current move
int result;			// Result of the game
bool over;			// Is the game Over?
const float DEG2RAD = 3.14159/180;
int colourize=0;
/*
	Sets the board for Tic-Tac-Toe
*/
void Intialize()
{
	turn=1;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			board[i][j]=0;
	}
}
/*
	Called when any key from keyboard is pressed
*/
void OnKeyPress(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'y':
		if(over==true)
		{
			over=false;
			Intialize();
		}
		break;
	}
}

/*
	Called when Mouse is clicked
*/
void OnMouseClick(int button,int state,int x,int y)
{
	if(over==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if(turn==1)
		{
			if(board[(y-50)/100][x/100]==0)
			{
				board[(y-50)/100][x/100]=1;
				turn=2;
			}
		}
		else if(turn==2)
		{
			if(board[(y-50)/100][x/100]==0)
			{
				board[(y-50)/100][x/100]=2;
				turn=1;
			}
		}
	}
}

/*
	Utility function to draw string
*/
void DrawString(void *font,const char s[],float x,float y)
{
	unsigned int i;
	glRasterPos2f(x,y);
	for(i=0;i<strlen(s);i++)
	{
		glutBitmapCharacter(font,s[i]);
	}
}

/*
	Function to draw up the horizontal and vertical lines
*/
void DrawLines()
{
	glBegin(GL_LINES);
	if (colourize == 0)
		glColor3f(1,1,1);
	else if (colourize ==1)
		glColor3f(0,1,1);
	glVertex2f(100,50);
	glVertex2f(100,340);
	glVertex2f(200,340);
	glVertex2f(200,50);

	glVertex2f(0,150);
	glVertex2f(300,150);
	glVertex2f(0,250);
	glVertex2f(300,250);

	glEnd();
}

/*
	Utility function to draw the circle
	void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}
*/
void DrawCircle(float cx, float cy, float r)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <360; i++)
    {
        float degInRad = i*DEG2RAD;

        glVertex2f(cx+cos(degInRad)*r, cy+sin(degInRad)*r);
    }
    glEnd();
}

/*
	Function to draw the cross and circle of Tic-Tac-Toe
*/
void DrawXO()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==1)
			{
				glBegin(GL_LINES);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 - 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 - 25);
				glEnd();
			}
			else if(board[i][j]==2)
			{

				DrawCircle(50 + j*100 , 100 + i*100 , 25);
			}
		}
	}
}

/*
	Function to check if there is any winner
*/
bool CheckWinner()
{
	int row, col;
	// horizontal check
	for (row = 0; row < 3; row++)
	{
		for (col = 0; col < 3; col++)
		{
			if (board[row][0] != 0 && board[row][0] == board[row][col])
			{
				if (col == 2)
				{
					return true;
				}
			}
			else
				break;
		}
	}
	// vertical check
	for(row = 0; row < 3; row++)
	{
		for(col = 1; col < 3; col++)
		{
			if(board[0][row] != 0 && board[0][row] == board[col][row])
			{
				if(col == 2)
					return true;
			}
			else
				break;
		}
	}
	// Diagonal check
	if((board[0][0]!=0 && board[0][0]==board[1][1] && board[0][0]==board[2][2])
	|| (board[2][0]!=0 && board[2][0]==board[1][1] && board[2][0]==board[0][2]))
		return true;
	return false;
}


/*
	function to check if there is draw
*/
bool CheckIfDraw()
{
	int row, col;
	bool draw = true;
	for(row = 0; row < 3; row++)
	{
		for(col = 0; col < 3; col++)
		{
			if(board[row][col] == 0)
				draw = false;
		}
	}
	return draw;
}

void menu(int choice)
{
    switch (choice)
    {
    case 1:
    	colourize =0;
    	Intialize();
        break;
    case 2:
    	colourize = 1;
    	Intialize();
        break;
    case 3:
        exit(0);
        break;
    }
}

/*
	Function to display up everything
*/
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	if (colourize == 1)
			glColor3f(0, 1, 1);
	else if (colourize == 0 )
			glColor3f(0, 1, 1);
	if(turn == 1)
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player One (X)'s turn", 100, 30);
	else
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player Two (O)'s turn", 100, 30);

	DrawLines();
	DrawXO();

	if(CheckWinner() == true)
	{
		if(turn == 1)
		{
			over = true;
			result = 2;
		}
		else
		{
			over = true;
			result = 1;
		}
	}
	else if(CheckIfDraw() == true)
	{
		over = true;
		result = 0;
	}
	if(over == true)
	{
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);
		if(result == 0)
			DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 110, 185);
		if(result == 1)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player Two (O)'s wins", 95, 185);
		if(result == 2)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player One (X) wins", 95, 185);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (Y)", 40, 210);
	}
	glutSwapBuffers();
}

/*
	Function to reshape
*/
void Reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

/*
	Driver Function
*/
int main(int argc, char **argv)
{
	Intialize();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(550,200);
	glutInitWindowSize(300,350);
	glutCreateWindow("Tic-Tac-Toe");
	glutSetWindowTitle("Misere Tic-Tac-Toe");
	glutCreateMenu(menu);
	glutAddMenuEntry("Start Game", 1);
	glutAddMenuEntry("Jazz", 2);
	glutAddMenuEntry("Quit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyPress);
	glutMouseFunc(OnMouseClick);
	glutIdleFunc(Display);
    glutMainLoop();
    return 0;
}
