#include "Ringpuffer.h"
#include <iostream>

void Ringpuffer::addNode(string pDescr, string pData)
{
    RingNode* newNode = new RingNode(pDescr, pData);
    if(Anker == nullptr)
    {
        Anker = newNode;
        newNode->setNext(newNode);
        size++;
        return;
    }
    else if(size < 6)
    {
        newNode->setNext(Anker->getNext());
        Anker->setNext(newNode);
        Anker = newNode;
        incrAge();
        size++;
    }
    else
    {
        newNode->setNext(Anker->getNext()->getNext());
        delete Anker->getNext();
        Anker->setNext(newNode);
        Anker = newNode;
        incrAge();
    }
}


void Ringpuffer::incrAge()
{
    RingNode* tmp = Anker->getNext();
    while(tmp != Anker)
    {
        tmp->setAge(tmp->getAge() + 1);
        tmp = tmp->getNext();
    }
}

RingNode* Ringpuffer::search(string pData)
{
    if(Anker->getData() == pData) return Anker;
    RingNode* tmp = Anker->getNext();
    while(tmp != Anker)
    {
        if(tmp->getData() == pData) return tmp;
        tmp = tmp->getNext();
    }
    return nullptr;
}

void Ringpuffer::print(RingNode* pAnker)
{

    if(pAnker != Anker) print(pAnker->getNext());
    cout << "OldAge: " << pAnker->getAge() << ", Descr: " << pAnker->getDescription() << ", Data: " << pAnker->getData() << endl;
}

/*
void Ringpuffer::print()
{
    RingNode* tmp = Anker;
    if(size == 0) cout << "Keine Backups vorhanden.\n";
    for(int i = 0; i < size; i++)
    {
        cout << "OldAge: " << tmp->getAge() << ", Descr: " << tmp->getDescription() << ", Data: " << tmp->getData() << endl;
        if (i < 5) cout << "-------------------------------\n";
        for(int j = 1; j < size; j++) tmp = tmp->getNext();
    }

}
*/