#pragma once
#ifndef PRAKTIKUM2TREE_TREE_H
#define PRAKTIKUM2TREE_TREE_H

#include <string>
#include "TreeNode.h"

class Tree
{
private:
    TreeNode* Anker = nullptr;
    int nextID = 0;

public:
    Tree() = default;
    TreeNode* getAnker() { return Anker; }
    void add(int pAlter, double pEinkommen, int pPLZ, std::string pName);
    TreeNode* search(TreeNode* pAnker, int pPos);
    bool searchAndPrint(TreeNode* pAnker, std::string pName);
    void del(int pPos);
    void print(TreeNode* pAnker);
    TreeNode* whereToPut(TreeNode* pAnker, int pPos);
    void import();
};

#endif //PRAKTIKUM2TREE_TREE_H
