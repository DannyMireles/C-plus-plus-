#include <iostream>
#include "functions.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
  int nRows, nCols, nMines, row, col;
  struct minePosition **mineMatrix;
  bool goOn = true,   // verify if the game is over
       winner = true;

  do{
    cout << "Enter #rows and #columns: ";
    cin >> nRows >> nCols;
  }
  while (nRows <= 0 || nCols <= 0);

  mineMatrix = createMatrix (nRows, nCols);
  if (!mineMatrix){
    cout << "Problems allocating game matrix" << endl;
    return(0);
  }

  do{
    cout << "Enter #mines: ";
    cin >> nMines;
  } while (nMines < 0 || nMines > nRows * nCols);

  initializeMineMatrix(mineMatrix, nRows, nCols, nMines);
  printMineMatrix (mineMatrix, nRows, nCols, nMines);

  while(goOn){
    do{
      cout << "Enter row and column: ";
      cin >> row >> col;

      if (row < 0 || row >= nRows || col < 0 || col >= nCols)
      {
        cout << "Entered value out of range. Enter again." << endl;
      }
    }
    while (row < 0 || row >= nRows || col < 0 || col >= nCols);

    // open the position chosen by the user
    if (openPosition(mineMatrix, nRows, nCols, row, col) == MINE){
      // user chooses a MINE position
      winner = false;
      goOn = false;
    }
    if (countClosedPositions (mineMatrix, nRows, nCols) == nMines){
      // all closed positions contain a MINE
      goOn = false;
    }
    printMineMatrix (mineMatrix, nRows, nCols, nMines);
  }

  if (winner){
    cout << "Congratulations!" << endl;
  }

  return (0);
}