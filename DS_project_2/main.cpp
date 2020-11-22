#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std ;





void **fileInput(string fileName, int **floorOriginal, int &rows, int &columns, int &battery, int &chargerRow, int &chargerColumn)
{
   char temp ;

   ifstream infile(fileName) ;
   
   
   
   if (!infile) {
      cout << "fail to open file" ;
   }
   
   infile >> rows >> columns >> battery;
   cout << rows << " " << columns << " " << battery << endl ;
   
   
   
   floorOriginal = new int*[rows] ;
   for (int i = 0; i < rows; i++) {
      floorOriginal[i] = new int[columns] ;
   }
   
   
   int i = 0 , j=0 ;
   
   while (infile)
   {
      infile >> temp ;
      
      if (temp == '\n')
      {
         i++ ;
         j = 0 ;
      }
      
      if (temp == '0')
      {
         floorOriginal[i][j] = 0 ;
         j++ ;
      }
      if (temp == '1')
      {
         floorOriginal[i][j] = 1 ;
         j++ ;
      }
      if (temp == 'R')
      {
         floorOriginal[i][j] = 3 ;
         chargerRow = i ;
         chargerColumn = j ;
         j++ ;
      }
      
   }
   
   
   
   /*
   
   for (int i = 0; i < rows ; i++)
   {
      floorOriginal[i] = new int[columns] ;
      for (int j = 0; j < columns; j++)
      {
         infile >> temp ;
         if (temp == '0')
         {
            floorOriginal[i][j] = 0 ;
         }
         if (temp == '1')
         {
            floorOriginal[i][j] = 1 ;
         }
         if (temp == 'R')
         {
            floorOriginal[i][j] = 3 ;
            //chargerRow = i ;
            //chargerColumn = j ;
         }
      }
      cout << endl ;
      for (int j = 0; j < columns; j++)
      cout << floorOriginal[i][j] ;
      
   }
    
    */
   
   cout << "end file input" << endl ;
   
   
   
   return 0 ;
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
   vector<Node*> adjacentNodes ;
   vector<Node*> ups ;
   vector<Node*> downs ;
   vector<Node*> backs ;
   int backSteps ;
};


/*
//build nodes
void buildNodes(int **floorOriginal, int rows, int columns, int chargerRow, int chargerColumn, Node *root)
{

   
}
*/





int main(int argc, const char * argv[])
{
   int rows, columns, battery, chargerRow, chargerColumn ;
   int **floorOriginal ;
   
   
   if (argc == 2)
   {
      fileInput(argv[1], floorOriginal, rows, columns, battery, chargerRow, chargerColumn) ;

      
      /*
      cout << "input module" << endl ;
      cout << argv[1] << endl;
      
      
      ifstream infile ;
      infile.open(argv[1], ios::in) ;
      
      if (!infile) {
         cout << "fail to open file" ;
      }
      
      */
      
      
      
      
      
      
      
      
      
   }
   else
      return 1 ;
   

   /*
   
   //test
   cout << chargerRow << " " << columns ;
   
   
   
   
   
   //array for mapping floor
   int **floorMapping = new int *[rows] ;
   for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
         floorMapping[i][j] = floorOriginal[i][j] ;

   
   //array for floor nodes
   Node ***floorNodes ;
   
   floorNodes = new Node**[rows] ;
   for (int i = 0; i < rows; i++)
   {
      floorNodes[i] = new Node*[columns] ;
      for (int j = 0; j < 0; j++)
      {
         if (floorOriginal[i][j] != 1)
         {
            Node temp = Node(i, j, floorOriginal[i][j]) ;
            floorNodes[i][j] = &temp ;
         }
         else
         {
            floorNodes[i][j] = NULL ;
         }
      }
   }
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   // root
   Node *root = floorNodes[chargerRow][chargerColumn] ;
   root->backSteps = 0 ;
   floorMapping[chargerRow][chargerColumn] = 4 ;


   //map nodes
   queue<Node*> expendQueue ;
   expendQueue.push(root) ;
   

   Node *current, *next ;
   while (!expendQueue.empty())
   {
      current = expendQueue.front() ;
      
      
      if (current->column - 1 >= 0)
      {
         next = floorNodes[current->row][current->column - 1] ;

         if (floorMapping[current->row][current->column - 1] == 0)
         {
            current->downs.push_back(next) ;
            next->ups.push_back(current) ;
            next->backs.push_back(current) ;
            next->backSteps = current->backSteps + 1 ;
            current->adjacentNodes.push_back(next) ;
            next->adjacentNodes.push_back(current) ;
            
            // flag for done mapping
            floorMapping[current->row][current->column - 1] = 4 ;
            //push to queue for leter check for next node
            expendQueue.push(next) ;
         }
         
         if (floorMapping[current->row][current->column - 1] == 4)
         {
            current->downs.push_back(next) ;
            next->ups.push_back(current) ;
            
            // should consider 2 ways
            if (next->backSteps > current->backSteps + 1)
            {
               next->backSteps = current->backSteps + 1 ;
               next->backs.clear() ;
               next->backs.push_back(current) ;
            }
            
            if (next->backSteps == current->backSteps + 1)
            {
               next->backs.push_back(current) ;
            }
            
            if (next->backSteps < current->backSteps + 1)
            {
               //do nothing
            }
            
            current->adjacentNodes.push_back(next) ;
            next->adjacentNodes.push_back(current) ;
            
            // flag for done mapping
            floorMapping[current->row][current->column - 1] = 4 ;
         }
         
      }
      
      
      
      
      
      
      
      
      
      
      
      
      //done checking around this node, pop out of the queue
      expendQueue.pop() ;
   }
   
   
   

   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < 0; j++)
      {
         if(floorNodes[i][j])
         {
            cout << floorNodes[i][j]->status << " " ;
         }
         else
         {
            cout << " " ;
         }
         
      }
      cout << '\n' ;
   }
   
   
   */
   
   return 0;
}










 

 
 
 
 



