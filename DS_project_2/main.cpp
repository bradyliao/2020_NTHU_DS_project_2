#include <iostream>
#include <fstream>
#include <vector>

using namespace std ;







int **fileInput(string fileName, int &rows, int &columns, int &battery, int &chargerRow, int &chargerColumn)
{
   char temp ;
   
   ifstream input(fileName) ;
   
   input >> rows >> columns >> battery;
   
   if (rows > 1000 || rows <= 0 || columns > 1000 || columns <= 0)
      throw invalid_argument("Row or Column of the floor map is not valid.") ;
   
   int **floor ;
   floor = new int *[rows] ;
   for (int i = 0; i < rows; i++)
   {
      floor[i] = new int[columns] ;
      for (int j = 0; j < columns; j++)
      {
         input >> temp ;
         if (temp == '0')
         {
            floor[i][j] = 0 ;
         }
         if (temp == '1')
         {
            floor[i][j] = 1 ;
         
         
         
         }
         if (temp == 'R')
         {
            floor[i][j] = 3 ;
            chargerRow = i ;
            chargerColumn = j ;
         
         
         
         
         }
      }
      //consume new line character
      input >> temp ;
   }
   return floor ;
}




// classs for each node
class Node
{
public:
   Node(int row, int column, int status)
   {
      this->row = row ;
      this->column = column ;
      this->status = status ;
   }
   
// private data of a block

   int row, column, status ;
   
};



/*
void buildNodes(vector<vector<Node>> &floorNodes, int **floorOriginal, int rows, int columns)
{
   for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
         floorNodes[i][j] = Node(i, j, floorOriginal[i][j]) ;
}
*/





int main(int argc, const char * argv[])
{
   int rows, columns, battery, chargerRow, chargerColumn ;
   int **floorOriginal ;
   
   
   if (argc == 2)
      floorOriginal = fileInput(argv[1], rows, columns, battery, chargerRow, chargerColumn) ;
   else
      return 1 ;
   


   //buildNodes
   vector<vector<Node>> floorNodes(rows);
   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < columns; j++)
      {
         Node temp(i, j, floorOriginal[i][j]) ;
         floorNodes[i].push_back(temp) ;
      }
   }
   
   
   // adjacentNodes / connectNodes (BFS)
   
   
   
   
   return 0;
}






