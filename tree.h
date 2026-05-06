#ifndef TREE_H
#define TREE_H

#include "data.h"
#include <iostream>
using namespace std;

struct TreeNode {
    DecisionData data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(DecisionData val) {
        data = val;
        left = right = NULL;
    }
};

class DecisionTree {
private:
    TreeNode* root;

public:
    DecisionTree();

    void insert(DecisionData val);
    TreeNode* insertRec(TreeNode* node, DecisionData val);

    void computeDecision(float threshold);

    void inorder(TreeNode* node);
    void displayTree();
};

#endif