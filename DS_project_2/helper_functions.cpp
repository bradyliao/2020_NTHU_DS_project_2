#include <iostream>
#include <fstream>

using namespace std ;



int **fileInput(string fileName, int &row, int &column, int &battery)
{
   char temp ;
   
   ifstream input(fileName) ;
   
   input >> row >> column >> battery;
   
   if (row > 1000 || row <= 0 || column > 1000 || column <= 0)
      throw invalid_argument("Row or Column of the floor map is not valid.") ;
   
   int **floor ;
   floor = new int *[row] ;
   for (int i = 0; i < row; i++)
   {
      floor[i] = new int[column] ;
      for (int j = 0; j < column; j++)
      {
         input >> temp ;
         if (temp == '0')
            floor[i][j] = 0 ;
         if (temp == '1')
            floor[i][j] = 1 ;
         if (temp == 'R')
            floor[i][j] = 3 ;
      }
      //consume new line character
      input >> temp ;
   }
   return floor ;
}











