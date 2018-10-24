// Author:       Mariana Acosta
// Assignment:       project 4
// File:       Tree
// Instructor:       Reza Sanati
// Class:       CSIS 2420  Section: 001
// Date Written:   June 2, 2018
// Description: get data from file, then construct an avl tree, in order recursevely and pre order non recursevely

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<vector>
#include "Tree.h"
#include <stdexcept>
using namespace std;


//----------------------MAIN-------------------------
int main() {
    string filename;
    ifstream file;
    string command;
    //int i;
    int data;
 
    cout << "Mariana Acosta Zermeno" << endl;
    cout << "CS2420 Section 1" << endl;
    cout << "Program 2: Linked Lists" << endl;
    
    cout << "Enter the file name you would like to use:" << endl;
    cin >> filename;
    file.open(filename);
    //create avl tree 
    Tree *AVL = new Tree(); 
    //while there is data in the file pass it to data in function
    while(file >> data) {
      AVL->DataIn(AVL->root, data);
		}
    //output the InOrder function for the first part 
    cout << "\nIn-Order" << endl;
    AVL->InOrder(AVL->root);
    //output the PreOrder function for the second part 
    cout << "\nPre-Order" << endl;
    AVL->PreOrder(AVL->root);
    

}