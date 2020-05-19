#include "MyObject.h"
class TreeNode {

public:
    int id;
    bool marked;

    MyObject * ptrDir;

    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    TreeNode(int newId, MyObject * newPtrDir){
        this->id = newId;
        marked = false;
        ptrDir = newPtrDir; 
        right = nullptr;
        left = nullptr;
        parent = nullptr;
    }
};