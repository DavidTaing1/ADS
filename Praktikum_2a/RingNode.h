#ifndef ADS_PRAKTIKUM2_RINGNODE_H
#define ADS_PRAKTIKUM2_RINGNODE_H


#include <string>

using namespace std;


class RingNode
{
private:
    int OldAge;
    string description, SymbolicData;
    RingNode* next = nullptr;

public:
    RingNode(){}
    RingNode(string pDescription, string pSymbolicData) : description(pDescription), SymbolicData(pSymbolicData), OldAge(0) {}
    int getAge() { return OldAge; }
    void setAge(int pAge) { OldAge = pAge; }
    string getDescription() { return description; }
    void setDescription(string pDescription) { description = pDescription; }
    string getData() { return SymbolicData; }
    void setData(string pData) { SymbolicData = pData; }
    RingNode* getNext(){ return next; }
    void setNext(RingNode* pNext) { next = pNext; }
};
#endif //ADS_PRAKTIKUM2_RINGNODE_H
