#include <iostream>
#include "TreeNode.h"

using namespace std;

class BinaryTree {

private:
    TreeNode *root;

public:

    int totalNodes;

    BinaryTree(){totalNodes = 0;}
    
    void insertNode(int newId, MyObject *ptrDir){
        root = insertNode(root, newId, ptrDir);
    }

    TreeNode* insertNode(TreeNode *root, int newId, MyObject *ptrDir){
        if (root == nullptr){
            root = new TreeNode(newId, ptrDir);
        
        } else if (root->id < newId){
            root->right = insertNode(root->right, newId, ptrDir);
            root->right->parent = root;
        
        } else {
            root->left = insertNode(root->left, newId, ptrDir);
            root->left->parent = root;
        }

        return root;

    }

    void traverseInOrder(bool phase){
        traverseInOrder(root, phase);
    }
    
    void traverseInOrder(TreeNode *node, bool phase){
        if (node != nullptr){
            traverseInOrder(node->left, phase);
            if (phase == true){
                node = markAux(node);
            } else {
                node = sweepAux(node);
            }
            cout << "Node: " << node->id << " marked: " << node->marked << endl;
            traverseInOrder(node->right, phase);
        }
    }

    TreeNode* markAux(TreeNode *node){
        if (!node->marked){
            node->marked = true;
        }
        return node;
    }

    TreeNode* sweepAux(TreeNode *node){
        if (node->marked){
            node->marked = false;
        } else {
            deleteNode(node->id);
        }
        return node;
    }

    int findSmallestId(TreeNode *node){
        return node->left == nullptr
            ? node->id
            : findSmallestId(node->left);
    }

    int findHighestId(TreeNode *node){
        return node->right == nullptr
            ? node->id
            : findHighestId(node->right);
    }

    void deleteNode(int idToDelete){
        deleteNode(root, idToDelete);
    }

    TreeNode* deleteNode(TreeNode *nodeToDelete, int idToDelete){
        if (nodeToDelete == nullptr){
            return nullptr;
        } 
        //if the node is found the function has to evaluate three cases
        if (nodeToDelete->id == idToDelete){
            
            //1. if the node has not any children
            if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) 
                return nullptr;
            
            //2. if one child is null: in this case left
            if (nodeToDelete->left == nullptr){
                return nodeToDelete->right;
            }

            //in this case right child null 
            if (nodeToDelete->right == nullptr){
                return nodeToDelete->left;

            //3. if it has both children
            } else {
                int smallestId = findSmallestId(nodeToDelete->right);
                nodeToDelete->id = smallestId;
                nodeToDelete->right = deleteNode(nodeToDelete->right, smallestId);
                return nodeToDelete;
            }
            
        }
        if (nodeToDelete->id > idToDelete){
            nodeToDelete->left = deleteNode(nodeToDelete->left, idToDelete);
            return nodeToDelete;
        }
        nodeToDelete->right = deleteNode(nodeToDelete->right, idToDelete);
        return nodeToDelete;
    }

    bool isIdNode(int idToFind){
        TreeNode *tmp = isIdNode(root, idToFind);
        return tmp != nullptr
            ? true
            : false;
    }

    TreeNode* isIdNode(TreeNode *node, int idToFind){
        if (node == nullptr){
            return nullptr;
        } 
        if (node->id == idToFind){
            return node;
        }
        return node->id > idToFind
            ? isIdNode(node->left, idToFind)
            : isIdNode(node->right, idToFind); 
    }

};


