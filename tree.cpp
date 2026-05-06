
#include "tree.h"

DecisionTree::DecisionTree() {
    root = NULL;
}

void DecisionTree::insert(DecisionData val) {
    root = insertRec(root, val);
    cout << "T: Decision Node Inserted (Zone " << val.zone << ")" << endl;
}

TreeNode* DecisionTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL)
        return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void DecisionTree::computeDecision(float threshold) {
    cout << "T: Computing Decisions..." << endl;
    inorder(root);
}

void DecisionTree::inorder(TreeNode* node) {
    if(node == NULL) return;

    inorder(node->left);

    if(node->data.risk > 0.6)
        cout << "T: ZONE " << node->data.zone << " -> EMERGENCY (Risk: " << node->data.risk << ")" << endl;
    else
        cout << "T: ZONE " << node->data.zone << " -> NORMAL (Risk: " << node->data.risk << ")" << endl;

    inorder(node->right);
}

void DecisionTree::displayTree() {
    cout << "T: Decision Tree State:" << endl;
    inorder(root);
}