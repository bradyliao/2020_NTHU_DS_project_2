#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std ;




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
   
   
   int row, column, status ;
   vector<Node*> adjacentNodes ;
   vector<Node*> ups ;
   vector<Node*> downs ;
   vector<Node*> backs ;
   int backSteps ;
};








int main(int argc, const char * argv[])
{
   int rows, columns, battery, chargerRow, chargerColumn ;
   int **floorOriginal={}, **floorMapping={} ;
   
   
   if (argc == 2)
   {
      //fileInput(argv[1], floorOriginal, rows, columns, battery, chargerRow, chargerColumn) ;
      char temp ;

      ifstream infile(argv[1]) ;
      
      if (!infile)
      {
         cout << "fail to open file" ;
      }
      
      infile >> rows >> columns >> battery ;
      infile.get() ;
      cout << rows << " " << columns << " " << battery << endl ;
      
      
      floorOriginal = new int*[rows] ;

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
               chargerRow = i ;
               chargerColumn = j ;
            }
         }
         infile.get() ;
      }

   }
   else
      return 1 ;
   
   
   //test
   //cout << chargerRow << " " << chargerColumn << endl  ;
   
   //array for mapping floor
   floorMapping = new int *[rows] ;
   
   for (int i = 0; i < rows; i++)
   {
      floorMapping[i] = new int[columns] ;
      
      for (int j = 0; j < columns; j++)
      {
         floorMapping[i][j] = floorOriginal[i][j] ;
         //cout << floorOriginal[i][j] ;
         //cout << floorMapping[i][j] ;
      }
      //cout << endl ;
   }
   
   
   

   //array for floor nodes
   Node ***floorNodes ;
   
   floorNodes = new Node**[rows] ;
   for (int i = 0; i < rows; i++)
   {
      floorNodes[i] = new Node*[columns] ;
      for (int j = 0; j < columns; j++)
      {
         if (floorOriginal[i][j] != 1)
         {
            //Node *temp = new Node(i, j, floorOriginal[i][j]) ;
            //floorNodes[i][j] = temp ;
            floorNodes[i][j] = new Node(i, j, floorOriginal[i][j]) ;
         }
         else
         {
            floorNodes[i][j] = NULL ;
         }
      }
   }
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   //
   
   
   
   
   
   
   
   
   
   // root
   Node *root ;
   root = floorNodes[chargerRow][chargerColumn] ;
   root->status = 0 ;
   //cout << root->row << endl ;
   floorMapping[chargerRow][chargerColumn] = 4 ;

   
   

   //map nodes
   queue<Node*> expendQueue ;
   expendQueue.push(root) ;
   

   Node *current, *next ;
   while (!expendQueue.empty())
   {
      current = expendQueue.front() ;
      
      //check for the left node
      if (current->column - 1 >= 0)
      {
         next = floorNodes[current->row][current->column - 1] ;

         
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
            
            // flag for done mapping (dont need it ?)
            //floorMapping[current->row][current->column - 1] = 4 ;
         }
         
         
         if (floorMapping[current->row][current->column - 1] == 0)
         {
            (current->downs).push_back(next) ;
            (next->ups).push_back(current) ;
            (next->backs).push_back(current) ;
            (next->backSteps) = current->backSteps + 1 ;
            (current->adjacentNodes).push_back(next) ;
            (next->adjacentNodes).push_back(current) ;

            // flag for done mapping
            floorMapping[current->row][current->column - 1] = 4 ;
            //push to queue for leter check for next node
            expendQueue.push(next) ;
         }
      }
      
      
      
      
      
      //check for the up node
      if (current->row - 1 >= 0)
      {
         next = floorNodes[current->row - 1][current->column] ;

         
         if (floorMapping[current->row - 1][current->column] == 4)
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
            
            // flag for done mapping (dont need it ?)
            //floorMapping[current->row][current->column - 1] = 4 ;
         }
         
         
         if (floorMapping[current->row - 1][current->column] == 0)
         {
            (current->downs).push_back(next) ;
            (next->ups).push_back(current) ;
            (next->backs).push_back(current) ;
            (next->backSteps) = current->backSteps + 1 ;
            (current->adjacentNodes).push_back(next) ;
            (next->adjacentNodes).push_back(current) ;

            // flag for done mapping
            floorMapping[current->row - 1][current->column] = 4 ;
            //push to queue for leter check for next node
            expendQueue.push(next) ;
         }
      }
      
      
      //check for the right node
      if (current->column + 1 >= 0)
      {
         next = floorNodes[current->row][current->column + 1] ;

         
         if (floorMapping[current->row][current->column + 1] == 4)
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
            
            // flag for done mapping (dont need it ?)
            //floorMapping[current->row][current->column - 1] = 4 ;
         }
         
         
         if (floorMapping[current->row][current->column + 1] == 0)
         {
            (current->downs).push_back(next) ;
            (next->ups).push_back(current) ;
            (next->backs).push_back(current) ;
            (next->backSteps) = current->backSteps + 1 ;
            (current->adjacentNodes).push_back(next) ;
            (next->adjacentNodes).push_back(current) ;

            // flag for done mapping
            floorMapping[current->row][current->column + 1] = 4 ;
            //push to queue for leter check for next node
            expendQueue.push(next) ;
         }
      }
      
      
      //check for the down node
      if (current->row + 1 >= 0)
      {
         next = floorNodes[current->row + 1][current->column] ;

         
         if (floorMapping[current->row + 1][current->column] == 4)
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
            
            // flag for done mapping (dont need it ?)
            //floorMapping[current->row][current->column - 1] = 4 ;
         }
         
         
         if (floorMapping[current->row + 1][current->column] == 0)
         {
            (current->downs).push_back(next) ;
            (next->ups).push_back(current) ;
            (next->backs).push_back(current) ;
            (next->backSteps) = current->backSteps + 1 ;
            (current->adjacentNodes).push_back(next) ;
            (next->adjacentNodes).push_back(current) ;

            // flag for done mapping
            floorMapping[current->row + 1][current->column] = 4 ;
            //push to queue for leter check for next node
            expendQueue.push(next) ;
         }
      }
      
      
      
      
      
      
      //done checking around this node, pop out of the queue
      expendQueue.pop() ;
   }
   
   
   
   
   
   
   
   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < columns; j++)
      {
         current = floorNodes[i][j] ;
         
         if (current)
         {
            cout << current << " " ;
         }
         else
         {
            cout << "               " ;
         }
         
      }
      cout << '\n' ;
   }
   
   
   
   
   
   
   
   
   

   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < columns; j++)
      {
         current = floorNodes[i][j] ;
         
         if (current)
         {
            if(current->backs.size() > 0)
            {
               cout << current->backs.front() << " "  ;
               //cout << current->backSteps << "  "  ;
            }
            else
            {
               cout << "               " ;
            }
         }
         else
         {
            cout << "               " ;
         }
         
      }
      cout << '\n' ;
   }
   
   
   
   
   return 0;
}










 

 
 
 
 



