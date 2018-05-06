#include "Tree.h"
#include <iostream>
#include <iomanip>
#include <fstream>

void Tree::add(int pAlter, double pEinkommen, int pPLZ, std::string pName)
{
    TreeNode* newNode = new TreeNode(pAlter, pEinkommen, pPLZ, pName, nextID);
    nextID++;

    if(Anker == nullptr) Anker = newNode;
    else
    {
        TreeNode* tmp = whereToPut(Anker, newNode->getNodePosID());
        newNode->setParent(tmp);
        if(tmp->getNodePosID() < newNode->getNodePosID()) tmp->setRight(newNode);
        else tmp->setLeft(newNode);
    }
}

TreeNode* Tree::whereToPut(TreeNode* pAnker, int pPos) //rekursiv
{
    if(pAnker->getNodePosID() < pPos)
    {
        if(pAnker->getRight() != nullptr) whereToPut(pAnker->getRight(), pPos);
        else return pAnker;
    }
    else
    {
        if(pAnker->getLeft() != nullptr) whereToPut(pAnker->getLeft(), pPos);
        else return pAnker;
    }
}

TreeNode* Tree::search(TreeNode *pAnker, int pPos)//rekursiv
{
    if(pAnker->getNodePosID() == pPos) return pAnker;
    if(pAnker->getNodePosID() < pPos) search(pAnker->getRight(), pPos);
    else search(pAnker->getLeft(), pPos);
}

bool Tree::searchAndPrint(TreeNode* pAnker, std::string pName) //rekursiv
{
    bool found = false;
    if(pAnker->getLeft() != nullptr) searchAndPrint(pAnker->getLeft(), pName);
    if(pAnker->getRight() != nullptr) searchAndPrint(pAnker->getRight(), pName);
    if(pAnker->getName() == pName)
    {
        pAnker->printData();
        found = true;
    }
    return found;
}

void Tree::del(int pPos)
{
    if(Anker->getNodePosID() == pPos)
    {
        if(Anker->getLeft() == nullptr && Anker->getRight() == nullptr) Anker = nullptr;
        else if(Anker->getLeft() == nullptr)
        {
            Anker->getRight()->setParent(nullptr);
            Anker = Anker->getRight();
        }
        else if(Anker->getRight() == nullptr)
        {
            Anker->getLeft()->setParent(nullptr);
            Anker = Anker->getLeft();
        }
        else
        {
            TreeNode* tmp = Anker->getRight();
            if(tmp->getLeft() == nullptr)
            {
                Anker->getLeft()->setParent(tmp);
                tmp->setParent(nullptr);
                tmp->setLeft(Anker->getLeft());
                Anker = tmp;
                return;
            }
            while(tmp->getLeft() != nullptr) tmp = tmp->getLeft();
            Anker->getLeft()->setParent(tmp);
            Anker->getRight()->setParent(tmp);
            if(tmp->getRight() != nullptr)
            {
                tmp->getRight()->setParent(tmp->getParent());
                tmp->getParent()->setLeft(tmp->getRight());
            }
            tmp->setLeft(Anker->getLeft());
            tmp->setRight(Anker->getRight());
            tmp->setParent(nullptr);
            Anker = tmp;
        }
    }
    else
    {
        TreeNode* tmp = search(Anker, pPos);
        if(tmp->getRight() == nullptr && tmp->getLeft() == nullptr)
        {
            if(tmp->getParent()->getNodePosID() < pPos)
            {
                tmp->getParent()->setRight(nullptr);
            }
            else
            {
                tmp->getParent()->setLeft(nullptr);
            }
            delete tmp;
            return;
        }
        else if(tmp->getRight() == nullptr)
        {
            if(tmp->getParent()->getNodePosID() < pPos)
            {
                tmp->getParent()->setRight(tmp->getLeft());
            }
            else
            {
                tmp->getParent()->setLeft(tmp->getLeft());
            }
            tmp->getLeft()->setParent(tmp->getParent());
            delete tmp;
            return;
        }
        else if(tmp->getLeft() == nullptr)
        {
            if(tmp->getParent()->getNodePosID() < pPos)
            {
                tmp->getParent()->setRight(tmp->getRight());
            }
            else
            {
                tmp->getParent()->setLeft(tmp->getRight());
            }
            tmp->getRight()->setParent(tmp->getParent());
            delete tmp;
            return;
        }
        else
        {
            TreeNode* tmp2 = tmp->getRight();
            tmp2->setParent(tmp->getParent());
            while(tmp2->getLeft() != nullptr) tmp2 = tmp2->getLeft();
            tmp->getLeft()->setParent(tmp2);
            tmp2->setLeft(tmp->getLeft());
            if(tmp->getParent()->getNodePosID() < pPos)
            {
                tmp->getParent()->setRight(tmp->getRight());
            }
            else
            {
                tmp->getParent()->setLeft(tmp->getRight());
            }
            tmp->getRight()->setParent(tmp->getParent());
            delete tmp;
            return;
        }
    }
}

void Tree::print(TreeNode* pAnker)
{
    std::cout << std::setw(3) << pAnker->getNodeID() << "|"
              << std::setw(12) <<  pAnker->getName() << "|"
              << std::setw(7) << pAnker->getAlter() << "|"
              << std::setw(11) << pAnker->getEinkommen() << "|"
              << std::setw(7) << pAnker->getPLZ() << "|"
              << std::setw(6) << pAnker->getNodePosID() << std::endl;

    if(pAnker->getLeft() != nullptr) print(pAnker->getLeft());
    if(pAnker->getRight() != nullptr) print(pAnker->getRight());
}

void Tree::import()
{
    std::ifstream userdata;
    if(userdata.is_open()) return;
    std::string alter, einkommen, plz, name;
    userdata.open("/home/david/CLionProjects/Praktikum_2b/ExportZielanalyse.csv", std::ios::in);
    for(int i = 0; i < 8; i++)
    {
        getline(userdata, name, ';');
        getline(userdata, alter, ';');
        getline(userdata, einkommen, ';');
        getline(userdata, plz, '\n');
        int intAlter = std::stoi(alter);
        double doubleEinkommen = std::stod(einkommen);
        int intPlz = std::stoi(plz);
        add(intAlter, doubleEinkommen, intPlz, name);
    }
    userdata.close();
}