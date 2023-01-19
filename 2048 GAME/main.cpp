#include <iostream>
#include<iomanip>
#include<ctime>
#include<cstdlib>

using namespace std;


int board[4][4];
int dirLine[] = {1, 0, -1, 0};
int dirColumn[]= {0, 1, 0, -1};

pair<int,int> generateUnoccupiedPosition()
{
    int occupied=1,line,column;
    while (occupied)
{
    line=rand()%4;
    column=rand()%4;
if(board[line][column]==0)
    occupied=0;
}
  return make_pair (line,column);
}
void addPiece()
{
    pair<int,int>pos= generateUnoccupiedPosition();
    board[pos.first][pos.second]=2;
}
void newGame ()
{
    for (int i=0; i<4; ++i)
    for(int j=0; j<4; ++j)
    board[i][j]=0;
    addPiece();
}
void printUI()
{
system("cls");
  for (int i=0; i<4; ++i)
  {
    for(int j=0; j<4; ++j)
       if (board[i][j]==0)
        cout<<setw(4)<< ".";
        else
        cout<<setw(4)<< board[i][j];
        cout<< "\n";
  }
  cout<<"n:new game, w: up, s: down, d: right, a: left, q: quit \n";
}
bool CanDoMove(int line, int column, int nextline, int nextcolumn )
{
if(nextline<0 || nextcolumn<0 || nextline>=4 || nextcolumn>=4 || (board[line][column]!=board[nextline][nextcolumn] && board[nextline][nextcolumn]!=0))
 return false;
 return true;
}

void applyMove (int direction)
{
   int startline=0, startcolumn=0, linestep=1, columnstep=1;

   if(direction==0)
    {
        startcolumn=3;
        linestep=-1;
    }
    if(direction==1)
    {
        startcolumn=3;
        columnstep=-1;
    }
  int movePossible , CanAddPiece =0;
  do {
      movePossible =0;
  for(int i=startline; i>=0 && i<4; i+=linestep)
  for(int j=startcolumn; j>0 && j<4; i+=columnstep)
  {
    int nextI= i+dirLine[direction], nextJ= j+dirColumn[direction];
      if(board[i][j] && CanDoMove (i, j, nextI, nextJ)) {
      board[nextI][nextJ]+=board[i][j];
      board[i][j]=0;
      movePossible = CanAddPiece =1;
  }
}   printUI();
  } while (movePossible);
  if (CanAddPiece)
    addPiece();
}
 int main()
{
    srand(time(0));
    char CommandToDir[128];
    CommandToDir['s']=0;
    CommandToDir['d']=1;
    CommandToDir['w']=2;
    CommandToDir['a']=3;

    newGame();
    while (true)
    {
        printUI();
        char command;
        cin>> command;
        if(command=='n')
        newGame();
        else if(command=='q')
        break;
    else
  {
       int currentDirection=CommandToDir[command];

       applyMove(currentDirection);
  }
    }
    return 0;
}
