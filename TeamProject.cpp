// TeamProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//  main.cpp
//  Zillow_Final_Project
//
//  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Copyright � 2018 s. All rights reserved.
//


//#include "pch.h"

#include <iostream>
#include <iomanip>
#include <string>
#include "House.h"
//#include <minmax.h>
#include "FileOperations.h"
#include "HeadNode.h"



/*
* get an int from cin with validation
* @return { T } userInput
*/
template <class T>
T getUserInput() {
    T userInput;

    do {
        if (!cin) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << endl << "Your input is invalid!" << endl;
            cout << "Retry: ";
        }

        cin >> userInput;
    } while (!cin);

    return userInput;
}

/*
This function checks if the house number provided is within the limits of the house numbers stored in the file.

*/


int validHouseNo()
{
    bool validHouseNo = false;
    int house_no;
    while (!validHouseNo)
    {
        house_no = getUserInput<int>();
        if ((house_no < 1) || (house_no > 99999)) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "Please enter a valid house number" << endl;
            validHouseNo = false;
        }
        else
        {
            validHouseNo = true;
        }
    
    }
    return house_no;
    
}

/*
This function is responsible for dynamically allocating a new House object that will be used by the data structures.

Return: the House object that has been created.


*/
House& newHouseEntry()
{

    cout << "new entry to housing database" << endl;
    House* h = new House();
    int count = 0;
    while (count < 6)
    {

        switch (count)
        {
        case 0:
        {
            cout << "House Number: " << endl;
            h->setHouseNo(validHouseNo());
            break;
        }
        case 1:
        {
            cout << "Street Address: " << endl;
            string add;
            getline(cin, add, '\n');
            h->setAddress(add);
            break;
        }
        case 2:
        {
            cout << "Number of Bedrooms: " << endl;
            int beds;
            while (!(cin >> beds) || (beds < 1) || (beds > 20)) {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "Please enter a valid number of bedrooms" << endl;
            }
            h->setBedrooms(beds);
            break;
        }
        case 3:
        {
            cout << "Number of Bathrooms: " << endl;
            float baths;
            while (!(cin >> baths) || (baths < 1) || (baths > 10)) {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "Please enter a valid number of bathrooms" << endl;
            }
            h->setBathrooms(baths);
            break;
        }
        case 4:
        {
            cout << "Sale Price: " << endl;
            int pr;
            while (!(cin >> pr) || (pr < 1) || (pr > 200000000)) {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "Please enter a valid  sale price" << endl;
            }
            h->setPrice(pr);
            break;
        }
        case 5:
        {
            cout << "Square Footage: " << endl;
            int sq_ft;
            while (!(cin >> sq_ft) || (sq_ft < 1) || (sq_ft > 100000)) {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "Please enter a valid square footage" << endl;
            }
            h->setSquareFootage(sq_ft);
            break;
        }
        }
        count++;
        cin.clear();
        cin.ignore(1024, '\n');
    }

    return *h;


}

/*
 print efficiency menu
*/
void printEfficiencyMenu()
{
    cout
        << "VIEW EFFICIENCY (Please Select an Option): " << endl
        << "\t [1] Hash Table Efficiency" << endl
        << "\t [2] Price Binary Search Tree Efficiency" << endl
        << "\t [3] Square Footage Binary Search Tree Efficiency" << endl;
}

/**
* print user menu
*/
void printMenu() {
    cout
        << "Please select one of the options: " << endl
        << "\t [1] Add a House entry" << endl
        << "\t [2] Delete a House Entry" << endl
        << "\t [3] Find a Home by House Number" << endl
        << "\t [4] List Houses in Hash Table Sequence" << endl
        << "\t [5] List Houses by House Number" << endl
        << "\t [6] Print indented tree" << endl
        << "\t [7] View Hash Table and Binary Search Tree Efficiencies" << endl
        << "\t [8] PRICE COMPARISON" << endl
        << "\t [9] Price Filter" << endl
        << "\t [10] Square Footage Filter" << endl
        << "\t [11] exit" << endl;
}

using namespace std;

int main() {

    bool keepGoing = true;
    int choice;
    int prevChoice = 0;
    string path = "/Users/mihika/Desktop/ConsoleZillow/ConsoleZillow/housedata.txt";


    FileOperations fileObj(path);
    HeadNode* node = new HeadNode();

    fileObj.readFromFile(node);
    node->resetTreeEfficiencies();
    node->resetHashCollisions();

    while (keepGoing != false)
    {
        printMenu();

        while (!(cin >> choice) || (choice < 1) || (choice > 11)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a choice on the menu" << endl;
        }

        cin.clear();
        cin.ignore(1024, '\n');
        


        switch (choice)
        {
        case 1:
        {
            cout << "ADDING NEW ENTRY" << endl;
            prevChoice = choice;
            House& newHouse = newHouseEntry();
            try {
                node->findHouse(newHouse.getHouseNo());
                cout << "Sorry, a house already exists at this address." << endl;
            }
            catch (int e)
            {
                fileObj.addToFile(newHouse);
                node->addNewHouseEntry(newHouse);
            }
            
            /*
            newHouse is a pointer to the house. use it to add the house to the hash table by house number and create new BST node and add to tree.

            */
            break;
        }
        case 2:
        {
            bool deleteValid = false;
            while (!deleteValid)
            {
                prevChoice = choice;
                cout << "DELETING ENTRY" << endl;
                cout << "Please enter the house number:" << endl;
                int h_no = validHouseNo();

                deleteValid = node->deleteHouse(h_no);


                fileObj.deleteFromFile(h_no);
                if (deleteValid)
                {
                    cout << "House successfully deleted" << endl;
                }

                cout << "Delete another entry?" << endl;
                cout << "(1) yes (2) no" << endl;
                int continueDelete = getUserInput<int>();
                while ((continueDelete < 1) || (continueDelete > 2))
                {
                    cout << "Please enter a valid menu option" << endl;
                    continueDelete = getUserInput<int>();
                }
                if (continueDelete == 1)
                {
                    deleteValid = false;
                }
                else if (continueDelete == 2)
                {
                    deleteValid = true;
                }

            }

            break;

        }
        case 3:
        {
            bool findValid = false;
            while (!findValid)
            {
                prevChoice = choice;
                cout << "FINDING HOUSE ENTRY" << endl;
                cout << "Please enter the house number:" << endl;
                int h_no = validHouseNo();
                try {
                    cout << "Your search resulted in: " << endl;
                    cout << node->findHouse(h_no) << endl;
                    findValid = true;
                }
                catch (int e)
                {
                    findValid = false;
                    cout << "Find another entry?" << endl;
                    cout << "(1) yes (2) no" << endl;
                    int continueFind = getUserInput<int>();
                    while ((continueFind < 1) || (continueFind > 2))
                    {
                        cout << "Please enter a valid menu option" << endl;
                        continueFind = getUserInput<int>();
                    }
                    if (continueFind == 1)
                    {
                        findValid = false;
                    }
                    else if (continueFind == 2)
                    {
                        findValid = true;
                    }

                }
            }
            //FIND A HOME USING HOUSE NUMBER AS KEY (from hash table).
            break;
        }
        case 4:
        {
            prevChoice = choice;
            node->listbyHash();
            break;
            //LIST HOUSES IN HASH TABLE (iterating through all linked list)
        }
        case 5:
        {
            //LIST HOUSES IN KEY SEQUENCE (inorder traversal of binary search tree?)
            prevChoice = choice;
            node->displayArray();
            break;
        }
        case 6:
        {
            // PRINT TREE NODE BY KEY. SET WIDTH ACCORDINGLY. HOW MANY KEYS (house numbers) PER LINE?
            prevChoice = choice;
            cout
                << "PRINT INDENTED TREE (Please Select an Option): " << endl
                << "\t [1] Price Tree" << endl
                << "\t [2] Square Footage Tree" << endl;
            int treetype;
            do
            {
                treetype = getUserInput<int>();
                if (treetype == 1)
                    node->printPriceTree();
                else if (treetype == 2)
                    node->printSqFtTree();
                else
                    cout << "Invalid input, please select an option from the menu." << endl;
            } while (treetype < 1 || treetype > 2);
            break;
        }
        case 7:
        {
            /* EFFICIENCY
            1) Hash Tables - Load Factor and after each INSERT
            2) BST - efficiency of searches / insertion

            */
            string array[3];
            array[0] = "Efficiency of Add Operation:";
            array[1] = "Efficiency of Remove Operation";
            array[2] = "Efficiency of Retrieval Operation";
            /*
            
            

            if ((prevChoice == 0) || (prevChoice > 3))
            {
                cout << "No Operation With An Efficiency Has Been Performed" << endl;
                break;
            }
            */
            if (prevChoice == 0)
            {
                cout << "Adding from Database resulted in: " << node->getHashCollisions() << " collisions" << endl;
                node->resetHashCollisions();
                cout << "Length of the Longest Chain: " << node->getHashLongestChain() << endl;
                break;
            }

            if (prevChoice > 3)
            {
                cout << "No Operation With An Efficiency Has Been Performed" << endl;
                break;
            }



            bool validEfficiency = false;
            while (!validEfficiency)
            {
                printEfficiencyMenu();
                int whichEfficiency = getUserInput<int>();
                while ((whichEfficiency < 1) || (whichEfficiency > 3))
                {
                    cout << "Please enter a valid menu option" << endl;
                    whichEfficiency = getUserInput<int>();
                }

                try {
                    string efficiencyoption = array[prevChoice - 1];
                    cout << efficiencyoption << endl;



                    if (whichEfficiency == 1) // hash table efficiency chosen
                    {

                        validEfficiency = true;

                        if (prevChoice == 1)
                        {
                            node->hashEfficiency(prevChoice); //add/delete/find (add = 1) delete=2 (find=3)
                            cout << "Number of Collisions: " << node->getHashCollisions() << endl;
                            node->resetHashCollisions();

                            cout << "Length of the Longest Chain: " << node->getHashLongestChain() << endl;
                        }
                        else if (prevChoice == 2)
                        {
                            cout << "the Efficiency for this removal operation was ";
                            node->hashEfficiency(prevChoice);
                            cout << "Length of the Longest Chain: " << node->getHashLongestChain() << endl;

                        }
                        else if (prevChoice == 3)
                        {
                            cout << "the load factor for this search operation was ";
                            node->hashEfficiency(prevChoice);
                            cout << "Length of the Longest Chain: " << node->getHashLongestChain() << endl;
                        }
                        //node->hashEfficiency(prevChoice); //add/delete/find (add = 1) delete=2 (find=3)
                    }
                    else if (whichEfficiency == 2)
                    {
                        validEfficiency = true;
                        cout << "The number of comparisons the PriceTree made during the previous operation made was " << node->priceTreeEfficiency() << endl;
                    }
                    else if (whichEfficiency == 3)
                    {
                        validEfficiency = true;
                        cout << "The number of comparisons the Square Foot Tree made during the previous operation made was " << node->sqFtTreeEfficiency() << endl;

                    }
                }
                catch (exception& e)
                {
                    validEfficiency = false;
                    cout << "Please first perform an operation for which an efficiency can be calculated" << endl;
                }

            }
            break;
        }
        case 8:
        {
            /* SPECIAL FEATURE: PRICE COMPARSION
            user can choose two house numbers. program will return house/attributes of cheaper house.
            */
            prevChoice = choice;
            bool validKeys = false;
            while (validKeys != true)
            {
                try {
                    cout << "Please enter the first house number:" << endl;
                    int h_no1 = validHouseNo();
                    cout << "Please enter the second house number:" << endl;
                    int h_no2 = validHouseNo();
                    node->priceComparison(h_no1, h_no2);
                    validKeys = true;

                }
                catch (int e)
                {
                    validKeys = false;
                }
            }

            break;

        }
        case 9:
        {
            prevChoice = choice;
            cout << "Price Filter" << endl;
            int min, max;

            cout << "Please enter a minimum price: ";
            min = getUserInput<int>();
            cout << "Please enter a maximum price: ";
            max = getUserInput<int>();

            cout << "Here are all the houses that matched your search range:" << endl << endl;
            cout << "HOUSES BETWEEN $" << min << " and $" << max << endl;
            cout << "---------------------------------" << endl;
            node->priceFilter(min, max);
            break;
        }
        case 10:
        {
            prevChoice = choice;
            cout << "Square Feet Filter" << endl;
            int min, max;

            cout << "Please enter a minimum square footage: ";
            min = getUserInput<int>();
            cout << "Please enter a maximum square footage: ";
            max = getUserInput<int>();

            cout << "Here are all the houses that matched your search range:" << endl << endl;
            cout << "HOUSES BETWEEN " << min << " and " << max <<" square feet." << endl;
            cout << "---------------------------------" << endl;
            node->squareFtFilter(min, max);
            break;

        }
        case 11:
        {
            cout << "Exiting Program" << endl;
            cout << "thank you" << endl;
            keepGoing = false;
            break;
        }


        }
    }
    system("pause");
    return 0;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
