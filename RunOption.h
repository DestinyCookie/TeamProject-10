
// This function will run the main menu and the function followed by the menu options.
#ifndef RUNOPTION_H
#define RUNOPTION_H

#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.h"
#include "Hash_Table.h"

using namespace std;

class RunOption
{
private:
   string fileName;
   BinarySearchTree* uniqueTree;
   BinarySearchTree* secondaryKeyTree;
   Hash_Table* hashTable;
   void getData();
   void caseSearch();
   void caseList();
   void caseAdd();
   void caseDelete();
   void caseWriteFile();
   void caseStatistic();
public:
   // default consturctor
   RunOption(){uniqueTree = 0; secondaryKeyTree = 0; fileName = "";}
   
   // print function
   static void display(Website &web);

   // constructor
   RunOption(string inputFileName){uniqueTree = 0; secondaryKeyTree = 0; fileName = inputFileName;}

   // build binary unique key and secondary key tree
   void buildTrees(Hash_Table* hashTable);

   // Destructor. Calls tree delete.
   ~RunOption(){uniqueTree->clear(); delete uniqueTree; delete hashTable;}

   // Runs the main functionality of RunOption
   void run();
   
   // output file validation
   bool outputFileValidation(ofstream &outputFile);
   
};

#endif
