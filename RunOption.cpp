
/*********************************
funtion declarition for RunOption.
**********************************/

#include "RunOption.h"
#include <cstdlib>

/************************************************
 diaplay function, will be passed in parameter.
*************************************************/
 void RunOption::display(Website& web)
{
   cout << web << endl;
}

/************************************************
 main function for runOption.
It will display the menu and build trees and hash table.
*************************************************/
void RunOption::run()
{
   // build the hash table off the input file
   getData();
   
   // build trees
   uniqueTree = new BinarySearchTree;
   secondaryKeyTree = new BinarySearchTree;
   buildTrees(hashTable);
   
   char choice;
   bool quit = false;
   cout << "Welcome! Our program is about the popular websites all around the world." << endl;
   
   do {
      cout << "Please input the letter corresponding to the function you'd like to use from the list below." << endl;
      cout << "A - Add New Website\n"
      << "D - Delete Website\n"
      << "S - Search for Website(s)\n"
      << "L - List Websites\n"
      << "W - Write data into file\n"
      << "H - Statistics\n"
      << "Q - Quit\n";

      cin >> choice;
      choice = toupper(choice);
      cout << endl;

      switch (choice)
      {
         case 'A': // add
            caseAdd();
            break;
         case 'D': // delete
            caseDelete();
            break;
         case 'S': // search
            caseSearch();
            break;
         case 'L': // list
            caseList();
            break;
         case 'W': // write to file
            caseWriteFile();
            break;
         case 'H': // Statistic
            caseStatistic();
            break;
         case 'Q': // quit
            quit = true;
            break;
         default:
            cout << "Invalid input.\n";
      }
   } while (!quit);

   if (choice == 'Q')
   {
      cout << "Thank you for using our program. Have a nice day!" << endl;
   }
}

/*************************************************
// build trees functions, passed the hash table in.
*************************************************/
void RunOption::buildTrees(Hash_Table* hashTable)
{
   Website* hashTableItem;
   for (int i = 0; i < hashTable->getTableSize(); ++i)
   {
      for (int j = 0; j < hashTable->getBucketSize(); ++i)
      {
         hashTableItem = hashTable->getHashItem(i, j);
         uniqueTree->insert(hashTableItem->getName(), *hashTableItem);
         secondaryKeyTree->insert(hashTableItem->getNationality(), *hashTableItem);
      }
   }
}

/*************************************************
functionality for menu driven function.
*************************************************/
void RunOption::caseAdd()
{
   cout << "Please enter the name of the website that you want to add:";
   string newWebString;
   cin >> newWebString;
   cout << "Please enter the nationality of the website:";
   string newCopuntryString;
   cin >> newCopuntryString;
   getline(cin, newCopuntryString);
   cout << "Please enter the rank of the website no bigger than " << uniqueTree->getCount() << " :";
   unsigned int newRankString;
   cin >> newRankString;
   cout << "Please enter the average time that visiter spend on this website(round it to sharp minute):";
   unsigned int newSpendTimeString;
   cin >> newSpendTimeString;
   cout << "Please enter the company name of the website:";
   string newCompanyNameString;
   cin.ignore();
   getline(cin, newCompanyNameString);
   cout << "Please neter the average daily view per visitor(round it to one decimal place):";
   float newDailyViewString;
   cin >> newDailyViewString;

   Website addWebsite(newWebString, newCopuntryString, newRankString, newSpendTimeString, newCompanyNameString, newDailyViewString);

   // insert to the hash table
   hashTable->insert(addWebsite);
   
   // insert to the unique tree
   uniqueTree->insert(newWebString, addWebsite);
   
   // insert to secondary tree
   secondaryKeyTree->insert(newCopuntryString, addWebsite);
   cout << "Inserting done!" << endl;
   
   // call run fuction again
   run();

}

/*************************************************
 functionality for delete case.
*************************************************/
void RunOption::caseDelete()
{
   // call tree delete function
   cout << "Do you want to remove the data by name or nationality? N for name, T for nationality:";
   char deleteChoice;
   cin >> deleteChoice;
   if (toupper(deleteChoice == 'N'))
   {
      cout << "Please enter the name of the website:";
      string deleteWebName;
      cin >> deleteWebName;
      Website deleteWeb;
      uniqueTree->removeAll(deleteWebName);
      cout << "Delete done!" << endl;
   }

   else if (toupper(deleteChoice == 'T'))
   {
      cout << "Please enter the nationality of the website:";
      string deleteWebNationality;
      cin >> deleteWebNationality;
      Website deleteWeb(deleteWebNationality);
      secondaryKeyTree->removeAll(deleteWebNationality);

      cout << "Delete done!" << endl;
   }

   else
   {
      cout << "Invalid input!" << endl;
   }

   run();
}

/*************************************************
 functionality for statistic case.
 *************************************************/
void RunOption::caseStatistic()
{
   hashTable->showStatistics();
   
   // call run fuction again
   run();
}

/*************************************************
save the tree into output file
*************************************************/
void RunOption::caseWriteFile()
{
   cout << "Do you want ot write the file by its name or nationality? N for name and T for nationality:";
   char writeFileChar;
   cin >> writeFileChar;
   if (toupper(writeFileChar) == 'N')
   {
      // Open output file
      ofstream outputFileByUnique;
      if (!outputFileValidation(outputFileByUnique))
      {
         return;
      }

   // write output file***********************TODO:
   // unique tree
   cout << "Out put file Web_Data_Out.txt done!" << endl;
      
   }
   else if (toupper(writeFileChar == 'T'))
   {
      // Open output file
      ofstream outputFileBySecondary;
      if(!outputFileValidation(outputFileBySecondary))
      {
         return;
      }

      // secondary tree *****************TODO:
      cout << "Out put file Web_Data_Out.txt done!" << endl;

   }
   else
   {
      cout << "Invalid input!" << endl;
   }
   run();
}

bool RunOption::outputFileValidation(ofstream &outputFile)
{
   string outputFileName = "Web_Data_Out.txt";
   outputFile.open(outputFileName.c_str());
   if (!outputFile.is_open())
   {
      cout <<"Error opening out put file!" << endl;
      return false;
   }
   return true;
}

/*************************************************
 Functionality for case search
*************************************************/
void RunOption::caseSearch()
{
   
   // use hash table to search, faster.
   char subChoice;
   bool invalid;

   do {
      invalid = false;
      cout << "Please select a search type from the options below.\n" << endl
      << "N - Search website data for given domain name\n"
      << "C - Search websites by country\n"
      << "R - Return to previous menu\n" << endl;
      cin >> subChoice;
      subChoice = toupper(subChoice);
      cout << endl;

      switch (subChoice)
      {
         case 'N': // domain name
         {
            cout << "Please enter the name of the website you want to search: ";
            string primarykey;
            cin >> primarykey;
            Website targetWebsite;
            vector<Website> aquiredWebsite;
            
            uniqueTree->getEntry(primarykey, aquiredWebsite);
            
            // disply unique item
            display(aquiredWebsite[0]);
            cout << "Search done!" << endl;
            break;
         }
         case 'C': // by country
         {
            cout <<"Please enter the name of the country that you want ot search: ";
            string secondaryKey;
            cin >> secondaryKey;
            Website targetWebsite;
            vector<Website> aquiredWebsite;
            
            uniqueTree->getEntry(secondaryKey, aquiredWebsite);
            
            // idsplay all searched items
            for (int i = 0; i < aquiredWebsite.size(); ++i)
            {
               display(aquiredWebsite[i]);

            }
            cout << "Search done!" << endl;
            break;
         }
         case 'R': // previous
            invalid = true;
            run();
            break;
         default:
            invalid = true;
            cout << endl << "Invalid input. ";
            break;
      }
   } while (invalid);

   run();
}

/*************************************************
 Functionality for case list
*************************************************/
void RunOption::caseList()
{
   char subChoice;
   bool invalid;

   do {
      invalid = false;
      cout << "Please select how to display the website data from the options below.\n" << endl;
      cout << "U - display unsorted\n"
      << "P - display by domain name\n"
      << "O - display by countries\n"
      << "I - display special\n"
      << "R - Return to previous menu\n" << endl;
      cin >> subChoice;
      subChoice = toupper(subChoice);
      cout << endl;

      switch (subChoice)
      {
         case 'U': // unsorted
            cout << "Unsorted List as Followed:" << endl;
            // call shuffle in case the data has already been sorted.
            /*********************************TODO:
             make a vector and push all items in. shuffle the vector and print the vector
             ****************************/
            
            break;
         case 'P': // alphabetical
            cout << "Sorted by the name of the website:" << endl;
            // call printBST tree.
            uniqueTree->preOrder(display);
            break;
            
         case 'O': // countries
            cout << "Sorted by country:" << endl;
            // call print SecondaryTree function.
            secondaryKeyTree->inOrder(display);
            break;
            
         case 'I': // special
            cout << "Sorted tree indented list:" << endl;
            cout << "Sorted by name: " << endl;
            uniqueTree->indented();
            cout << endl;
            cout << "Sorted by nationality: " << endl;
            secondaryKeyTree->indented();
            cout << endl;
            break;
            
         case 'R': // previous
            invalid = true;
            run();
            break;
            
         default:
            invalid = true;
            cout << "Invalid input." << endl;
            break;
      }
   } while (invalid);

   run();
}

/*************************************************
HashTable getData function initialize the size of 
the hash table and read the data from the file.
*************************************************/
void RunOption::getData()
{
   // TODO**************************change name back
    ifstream input("/Users/TingtingWang/Documents/TeamProject-10/websiteData.txt");
    if(input.fail())
    {
        cout << "Cannot open websiteData.txt!" << endl;
        exit(EXIT_FAILURE);
    }

    int numOfData;
    input >> numOfData;
    input.ignore();

    //multiply the size of array by 2, and find the next prime number
    //this gonna be in a seperate function
    //there are 8 lines for each website
    //....

    //allocate the hashtable, size is 30 for now, with bucket size of 3
    hashTable = new Hash_Table(30,3);

    string holdData;

   for(int i = 0; i < numOfData; i++)
   {
        //get the name of the website
      Website webNode;
      getline(input, holdData);
      webNode.setName(holdData);

        //get the nationality of the website
      getline(input, holdData);
      webNode.setNationality(holdData);
        //get the globalrank of the website
      getline(input, holdData);
      webNode.setGlobalRank(atoi(holdData.data()));
        //get the average time that visitor on the website
      getline(input, holdData);
      webNode.setAvgTime_OnSite(atoi(holdData.data()));
        //get the owner of the website
      getline(input, holdData);
      webNode.setOwner(holdData);
        //get hte average amount of pages viewed by a visitor per day
      getline(input, holdData);
      webNode.setAvgview_perVisitor(atof(holdData.data()));

      hashTable->insert(webNode);
      getline(input, holdData);
   }
}
