#include "Ringpuffer.h"
#include <iostream>
#include <vector>

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

vector<RingNode*> Ringpuffer::search2(string pData)
{
    vector<RingNode*> result;
    int i = 0;
    if(Anker->getData() == pData) result[i] = Anker; i++;
    RingNode* tmp = Anker->getNext();

    for(;i < 6; i++)
    {
        if(tmp->getData() == pData) result[i] = tmp;
        tmp = tmp->getNext();
    }
    return result;
}

void Ringpuffer::search(string pData)
{
    if(Anker->getData() == pData) cout << "Gefunden in Backup: OldAge " << Anker->getAge() << ", Beschreibung: ";
    cout << Anker->getDescription() << ", Daten: " << Anker->getData() << endl;;
    RingNode* tmp = Anker->getNext();
    while(tmp != Anker)
    {
        if(tmp->getData() == pData) cout << "Gefunden in Backup: OldAge " << tmp->getAge() << ", Beschreibung: ";
        cout << tmp->getDescription() << ", Daten: " << tmp->getData() << endl;;
        tmp = tmp->getNext();
    }
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