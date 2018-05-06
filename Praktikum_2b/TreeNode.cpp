#include "TreeNode.h"
#include <iostream>

using namespace std;

void TreeNode::printData()
{
    cout << "ID: " << NodeID << ", " << "Name: " <<  Name << ", " << "Alter: " << Alter
         << ", " << "Einkommen: " << Einkommen << ", " << "PLZ: " << PLZ << ", " << "Position: " << NodePosID << endl;
}
