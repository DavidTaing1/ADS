//
// Created by david on 25.04.18.
//

#ifndef ADS_PRAKTIKUM2_RINGPUFFER_H
#define ADS_PRAKTIKUM2_RINGPUFFER_H

#include "RingNode.h"
#include <vector>


class Ringpuffer
{

private:
    RingNode* Anker = nullptr;
    int size = 0;

public:
    Ringpuffer(){}
    RingNode* getAnker() { return Anker;}
    void addNode(string pDescr, string pData);
    void search(string pData);
    std::vector<RingNode*> search2(string pData);
    void print(RingNode* pAnker);
    void incrAge();
};
#endif //ADS_PRAKTIKUM2_RINGPUFFER_H
