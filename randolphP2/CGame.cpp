/*******************************************************************************
* Assignment: Project 2 - ASCII Move and Match Game                            *
* Author: Bryce Randolph                                                       *
* Date: Fall 2017                                                              *
* File:CGame.cpp                                                               *
*                                                                              *
* Description: This file contains the implementation of the class member       *
* functions from the CGame class.                                              *
*******************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "CGame.h"

CGame savedGame;

/*******************************************************************************
* Function: CGame::CGameSquare::CGameSquare ()                                 *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will set several default values. It is the        *
* Parameterized Constructor for the CGameSquare Struct                         *
*******************************************************************************/

CGame::CGameSquare::CGameSquare ()
{
  what = BORDER;
  whichSymbol=0;
  matched = false;
  value = 0;
}

/*******************************************************************************
* Function: void CGame::CGameSquare::Display (ostream & outs)                  *
* Parameters: ostream & outs  (reference to output)                            *
* Return value: void(none)                                                     *
* Description: This function determines which symbol to display the current    *
* state of the game using ASCII characters.                                    *
*******************************************************************************/

void CGame::CGameSquare::Display (ostream & outs)
{
  string esc = "\033";
  string color = "";
  
  char achar = ' ';
  switch (what)
    {
    case BORDER:
      achar = '0';
      break;
    case ME:
      achar = 'X';
      break;
      
    case SYMBOL:
      if (whichSymbol == 1)
	{
	  achar = '*';
	  color = "[31m";
	}
      else if (whichSymbol == 2)
	{
	  achar = '$';
	  color = "[32m"; 
	}
      else if (whichSymbol == 3)
	{
	  achar = '@';
	  color = "[33m";
	}
      else if (whichSymbol == 4)
	{
	  achar = '=';
	  color = "[34m";
	}
      else if (whichSymbol == 5)
	{
	  achar = '#';
	  color = "[35m";
	}
      else if (whichSymbol == 6)
	{
	  achar = '%';
	  color = "[36m";
	}
      char ismatched;
      
      if(matched==true)
	ismatched= '-';
      
      else
	ismatched=' ';
      outs << ismatched << "\033" << color << achar << "\033"<<"[39;49m" <<ismatched;
      return;
      
    case EMPTY:
      achar = ' ';
      break;
    }
  
   outs<< " "<< achar<< " ";
 }

/*******************************************************************************
* Function: void CGame::CGameSquare::Fill ()                                   *
*                                                                              *
* Parameters: none                                                             *
* Return value: void(none)                                                     *
* Description: This function will generate random characters from a pool of 6  *
* for filling the grid.                                                        *
*******************************************************************************/

void CGame::CGameSquare::Fill ()
{
  int random = rand() % 6+1;
  whichSymbol= random;
  what=SYMBOL;
}

/********************************************************************************
 * Function: CGame::CGame ()                                                    *
                                                                                *
 * Parameters: None                                                             *
 * Return value:  None                                                          *
 * Description: This constructor sets intial values                             *
 *******************************************************************************/

CGame::CGame ()
{
  numRows = 1;
  numCols = 1;
  grid = new CGameSquare * [3];
  grid[0] = new CGameSquare [3];
  grid[1] = new CGameSquare [3];
  grid[2] = new CGameSquare [3];
  myRow = 0;
  myCol = 0;
  movesLeft = 0;
  score = 0;
  srand (time (NULL));
}

/********************************************************************************
 * Function: CGame::CGame (const CGame & other)                                 *
 *                                                                              *
 * Parameters:  const CGame & other,  const CGame reference object              *
 * Return value: None                                                           *
 * Description: Copy constructor                                                *
 *******************************************************************************/

CGame::CGame (const CGame & other)
{
  numRows = other.numRows;
  numCols = other.numCols;
  myRow = other.myRow;
  myCol = other.myCol;
  movesLeft = other.movesLeft;
  score = other.score;
  
  grid = new CGameSquare * [numRows+2];
  for (int r = 0; r <= numRows+1; r++)
    {
      grid[r] = new CGameSquare [numCols+2];
      
      for (int c= 0;c <= numCols+1;c++)
	grid[r][c] = other.grid[r][c];
    }
}

/********************************************************************************
 * Function: CGame::~CGame ()                                                   *
 *                                                                              *
 * Parameters:  none                                                            *
 * Return value: none                                                           *
 * Description: Destructor, frees up memory                                     *
 *******************************************************************************/

CGame::~CGame ()
{
  for (int r = 0; r < numRows+2; r++)
    delete [] grid[r];
  
  delete [] grid;
}

/********************************************************************************
 * Function:  CGame & CGame::operator = (const CGame & other)                   *
 *                                                                              *                                                                    
 * Parameters: const CGame & other, Cgame value used to set other               *
 * Return value: none                                                           *
 * Description: Similar in content to copy constructor, however this allows     *
 * the comparisin of two class objects using =                                  *
 *******************************************************************************/

CGame & CGame::operator = (const CGame & other)
{
  if(this == & other) 
    return * this;
  
  for (int r = 0; r < numRows+2; r++)
    delete [] grid[r];
  delete [] grid;
  
  numRows = other.numRows;
  numCols = other.numCols;
  myRow = other.myRow;
  myCol = other.myCol;
  movesLeft = other.movesLeft;
  score = other.score;
  
  grid = new CGameSquare * [numRows+2];
  for (int r = 0; r <= numRows+1; r++)
    {
      grid[r] = new CGameSquare [numCols+2];
      
      for (int c= 0;c <= numCols+1;c++)
	grid[r][c] = other.grid[r][c];
    }
}

/*******************************************************************************
* Function: void CGame::Init (int R, int C, int M)                             *
*                                                                              *
* Parameters:  int R, int C, int M, all passed from Proj2app.cpp               *
* Return value: none                                                           *
* Description: This function will  intialize the game and save a state of it   *
*******************************************************************************/

void CGame::Init (int R, int C, int M)
{
  numRows = R;
  numCols = C;
  grid = new CGameSquare * [numRows+2];
  for (int r = 0; r < numRows+2; r++)
    grid[r] = new CGameSquare [numCols+2];
  
  FillIn ();
  
  myRow = 1+ rand() % numRows;
  myCol = 1+ rand() % numCols;
  
  grid [myRow][myCol].what = ME;
  grid [myRow][myCol].whichSymbol = 0;
  movesLeft = M;
  score = 0;
  savedGame = *this;
}

/*******************************************************************************
* Function:  void CGame::Instructions (ostream & outs, istream & ins)          *
*                                                                              *
* Parameters: ostream & outs, istream & ins                                    *
* Return value: void(none)                                                     *
* Description: This function will output instructions                          *
*******************************************************************************/

void CGame::Instructions (ostream & outs, istream & ins)
{
  string message = "Welcome to Matchy Match\n\n";  
  string instructions = "The goal of this game is to accumulate points by\nmoving the 'X' to create matches of 3 or more\nsquares with the same symbol in a row or column.\n\nEnter 'w', 'a', 's', or 'd' to move the 'X'\nup, left, down, and right respectively.\n\nEnter 'm' to identify matches.\nEnter 'u' to remove the current matches and\nupdate the tiles.\nEnter 'r' to restart the game.\n";
    outs << message << instructions << endl;
}

/*******************************************************************************
* Function: void CGame::Display (ostream & outs)                               *
*                                                                              *
* Parameters: ostream & outs                                                   *
* Return value: void(none)                                                     *
* Description: This function will actually draw the grid and the characters    *
* within that formatted grid                                                   *
*******************************************************************************/

void CGame::Display (ostream & outs)
{
  int r, c;
  outs << endl << "Score: " << score<< " points";
  outs << "     Moves Left: " << movesLeft << "\n\n";
  for (r = 1; r <= numRows; r++)
    {
      outs<< "+";
      for(int i =1; i<=numCols;i++)
	outs<<"---+";
      outs<<"\n";
      
      for (c = 1; c <= numCols; c++)
	{
	  outs<<"|" ;
	  grid [r][c].Display (outs);
	}
      
      outs<<"|";
      outs << "\n";
    }
  outs<< "+";
  for(int i =1; i<=numCols;i++)
    outs<<"---+";
  
  outs<<"\n";
  outs << "\n";
}
/*******************************************************************************
* Function: void CGame::Move (char direction)                                  *
*                                                                              *
* Parameters:  char direction, directional input from user                     *
* Return value: void(none)                                                     *
* Description: This function will move the X character within the grid         *
*******************************************************************************/

void CGame::Move (char direction)
{
  int row = myRow;
  int col = myCol;
  switch (direction)
    {
    case 'a':// moving left
      if(col!=1)
	{
	  swap(grid[row][col],grid[row][col-1]);
	  movesLeft--;
	  col--;
	}
      break;
      
    case 'w': // moving up
      if(row!=1)
	{
	  swap(grid[row][col],grid[row-1][col]);
	  movesLeft--;
	  row--;
	}
      break;
      
    case 'd': // moving right
      if(col!=numCols)
	{
	  swap(grid[row][col],grid[row][col+1]);
	  movesLeft--;
	  col++;
	}
      break;
      
    case 's': // moving down
      if(row!=numRows)
	{
	  swap(grid[row][col],grid[row+1][col]);
	  movesLeft--;
	  row++;
	}
      break;
    }
  myRow = row;
  myCol = col;
}

/*******************************************************************************
* Function: void CGame::Match ()                                               *
*                                                                              *
* Parameters: none                                                             *
* Return value: void(none)                                                     *
* Description: This will find matches, mark them as matched, and add to score  *
*******************************************************************************/

void CGame::Match ()
{
  for(int r = 1;r <= numRows;r++)
    {
      for(int c = 1;c <= numCols;c++)
	{
	  if(grid[r][c].matched==false && c > 1 && c < numCols && grid[r][c-1].whichSymbol==grid[r][c].whichSymbol && grid[r][c+1].whichSymbol==grid[r][c].whichSymbol)
	    {
	      grid[r][c].matched=true;
	      grid[r][c-1].matched=true;
	      grid[r][c+1].matched=true;
	      
	      int movesright=2;
	      
	      while(c+movesright<numCols && grid[r][c+movesright].matched==false && grid[r][c+movesright].whichSymbol==grid[r][c].whichSymbol)
		{
		  grid[r][c+movesright].matched=true;
		  movesright++;
		   
		}
	    }
	  if(grid[r][c].matched==false && r > 1 && r < numRows && grid[r-1][c].whichSymbol==grid[r][c].whichSymbol && grid[r+1][c].whichSymbol==grid[r][c].whichSymbol)
	    {
	      grid[r][c].matched=true;
	      grid[r-1][c].matched=true;
	      grid[r+1][c].matched=true;
	      
	      int movesdown=2;
	      
	      while(r+movesdown<numRows && grid[r+movesdown][c].matched==false && grid[r+movesdown][c].whichSymbol==grid[r][c].whichSymbol)
		{
		  grid[r+movesdown][c].matched=true;
		  movesdown++;
		} 
	    }
	}
    }
}  
/*******************************************************************************
* Function: void CGame::Update ()                                              *
*                                                                              *
* Parameters: none                                                             *
* Return value: void(none)                                                     *
* Description: This function will replace any symbol marked as matched with    *
* a new random symbol and mark them as unmatched                               *
*******************************************************************************/

void CGame::Update ()
{
  for(int r=1; r<=numRows;r++)
    {
      for(int c=1; c<=numCols;c++)
	{
	  if(grid[r][c].matched==true)
	    {
	      score++;
	      grid[r][c].Fill();
	      grid[r][c].matched=false;
	    }
	}
    } 
}

/*******************************************************************************
* Function: void CGame::Restart ()                                             *
*                                                                              *
* Parameters: none                                                             *
* Return value: void(none)                                                     *
* Description: This function will load the saved state of the game             *
*******************************************************************************/

void CGame::Restart ()
{
  *this = savedGame;
}

/*******************************************************************************
* Function:  void CGame::Message (bool done, ostream & outs)                   *
*                                                                              *
* Parameters: bool done, ostream & outs, bool value and output stream          *
* Return value: void(none)                                                     *
* Description: This function will display the ending message and final score   *
*******************************************************************************/

void CGame::Message (bool done, ostream & outs)
{
  char buffer [30];
  sprintf (buffer, "Your score is: %d", score);
  string message = "Thanks for playing!\n" + string(buffer);
  outs << message << endl;
}

/*******************************************************************************
* Function: bool CGame::Done ()                                                *
*                                                                              *
* Parameters: none                                                             *
* Return value: bool value, true or false for use in CGame::Message            *
* Description: This function returns false if movesLeft is zero                *
*******************************************************************************/

bool CGame::Done () 
{
   if(movesLeft==0)
     return true;
   else if (movesLeft>0)
     return false;
}


/*******************************************************************************
* Function:  void CGame::FillIn ()                                             *
*                                                                              *
* Parameters: none                                                             *
* Return value: void(none)                                                     *
* Description: This function will fill the entire grid, used in CGame:: Init   *
*******************************************************************************/

void CGame::FillIn ()
{
  for (int r = 1; r <= numRows+1; r++)
    for (int c = 0; c <= numCols+1; c++)
      grid[r][c].Fill();
}
