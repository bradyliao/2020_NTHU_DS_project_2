#include <iostream>
#include "helper_functions.cpp"
#include "NodeClass.cpp"

using namespace std ;


int main(int argc, const char * argv[])
{
   int row, column, battery ;
   int **floorOriginal ;
   
   
   if (argc == 2)
      floorOriginal = fileInput(argv[1], row, column, battery) ;
   else
      return 1 ;
   
   
   //buildNodes / adjacentNodes
   
   //connectNodes (BFS)
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   return 0;
}
