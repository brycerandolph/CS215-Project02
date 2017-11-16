/*******************************************************************************
* Assignment: Project 2 - ASCII Move and Match Game                            *
* Author: Bryce Randolph                                                       *
* Date: Fall 2017                                                              *
* File: Proj2app.cpp                                                           *
*                                                                              *
* Description: This file contains the main function that runs the game.        *
*******************************************************************************/

#include <iostream>
#include "SetLimits.h"
#include "CGame.h"
using namespace std;

/*******************************************************************************
* Function: int main()                                                         *
*                                                                              *
* Parameters: None                                                             *
* Return value: 0                                                              *
* Description: This function will run the game, and allows the user to exit    *
* or restart.                                                                  *
*******************************************************************************/

int main ()
{
  SetLimits();
  char play = 'y';
  CGame game;
  game.Instructions (cout, cin);
  while (tolower (play) == 'y')
    {
      game.Init(7,9, 10);
      game.Display (cout);
      bool finished = false, quitting = false;
      while (!finished && !quitting)
	{
	  char key;
	  cout << "Enter move (a = Left, w = Up, d = Right, s = Down)." << endl;
	  cout << "m = Match\nu = Update\nr = Restart\nq = Quit" << endl;
	  cout << "i = View instructions: ";
	  cin >> key;
	  if (key == 'q')
	    quitting = true;
	  else if (key == 'm')
	    game.Match ();
	  else if (key == 'u')
	    game.Update ();
	  else if (key == 'r')
	    game.Restart ();
	  else if (key == 'i')
	    game.Instructions (cout, cin);
	  else
	    game.Move(key);
	  finished = game.Done();
	  game.Display (cout);
	}
      game.Message (finished, cout);
      cout << "Would you like to play again (y/n)? ";
      cin >> play;
      cin.clear ();;
    }
  cout << endl;
  return 0;
}
