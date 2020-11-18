#include <fstream>

using namespace std ;



char **fileInput(string fileName, int &row, int &column, int &battery)
{
   //string currentBlockType ;
   //int currentBlockInitialColumn, currentBlockLRmove, inputLine = 0 ;
   
   ifstream input(fileName) ;
   
   input >> row >> column >> battery;
   
   if (row > 1000 || row <= 0 || column > 1000 || column <= 0)
      throw invalid_argument("Row or Column of the floor map is not valid.") ;
   
   char **floor ;
   floor = new char *[row] ;
   for (int i = 0; i < row; i++)
      floor[i] = new char[column] ;
   
   
   
   
   return floor ;
}
