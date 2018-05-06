#ifndef PRAKTIKUM2TREE_TREENODE_H
#define PRAKTIKUM2TREE_TREENODE_H
#include <string>

class TreeNode
{
private:
    int NodePosID, NodeID;
    int Alter, PLZ;
    double Einkommen;
    std::string Name;
    TreeNode *links = nullptr, *rechts = nullptr, *parent = nullptr;

public:
    TreeNode() = default;
    TreeNode(int pAlter, double pEinkommen, int pPLZ, std::string pName, int pID) : Alter(pAlter), Einkommen(pEinkommen), PLZ(pPLZ), Name(pName), NodeID(pID) { NodePosID = pAlter + pEinkommen + pPLZ; }
    std::string getName() { return Name; }
    int getAlter() { return Alter; }
    int getPLZ() { return PLZ; }
    int getNodePosID() { return NodePosID; }
    int getNodeID() { return NodeID; }
    double getEinkommen() { return Einkommen; }
    TreeNode* getLeft() { return links; }
    TreeNode* getRight() { return rechts; }
    TreeNode* getParent() { return parent; }
    void setName(std::string pName) { Name = pName; }
    void setAlter(int pAlter) { Alter = pAlter; }
    void setPLZ(int pPLZ) { PLZ = pPLZ; }
    void setEinkommen(double pEinkommen) { Einkommen = pEinkommen; }
    void setLeft(TreeNode* pLeft) { links = pLeft; }
    void setRight(TreeNode* pRight) { rechts = pRight; }
    void setParent(TreeNode* pParent) { parent = pParent; }
    void printData();
};

#endif //PRAKTIKUM2TREE_TREENODE_H
