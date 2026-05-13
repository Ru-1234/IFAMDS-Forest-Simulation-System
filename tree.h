#ifndef TREE_H
#define TREE_H

#include "data.h"
#include <iostream>
using namespace std;

// BST node
struct TreeNode {
    DecisionData data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(DecisionData val) {
        data = val;
        left = right = NULL;
    }
};

// hierarchy node - used by T1, T2
struct ZoneNode {
    int zoneID;
    string label;
    ZoneNode* children[4];
    int childCount;

    ZoneNode(int id, string lbl) {
        zoneID = id;
        label = lbl;
        childCount = 0;
        for(int i=0;i<4;i++) children[i] = NULL;
    }
};

// T1: Zone Hierarchy Tree - Forest -> Zone A -> Zone A1
class ZoneHierarchyTree {
private:
    ZoneNode* root;
    void printTree(ZoneNode* node, int depth);
public:
    ZoneHierarchyTree();
    void build();
    void display();
};

// T2: Sub-Zone Decomposition Tree - each zone split into N, S, E, W
class SubZoneTree {
private:
    ZoneNode* root;
    void printTree(ZoneNode* node, int depth);
public:
    SubZoneTree();
    void build();
    void display();
};

// T3: Terrain Classification Tree - Terrain Risk = (slope + dryness + density) / 3
class TerrainTree {
private:
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, DecisionData val);
    void inorder(TreeNode* node);
public:
    TerrainTree();
    void insert(int zone, float slope, float dryness, float density);
    void display();
};

// T4: Water Resource Tree - Water Availability = available / required
class WaterTree {
private:
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, DecisionData val);
    void inorder(TreeNode* node);
public:
    WaterTree();
    void insert(int zone, float available, float required);
    void display();
};

// T5: Fire Control Resource Tree - tracks fire response tools per zone
class FireControlTree {
private:
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, DecisionData val);
    void inorder(TreeNode* node);
public:
    FireControlTree();
    void insert(int zone, float resourceLevel);
    void display();
};

// T6: Equipment Allocation Tree - Priority = Risk * Impact
class EquipmentTree {
private:
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, DecisionData val);
    void inorder(TreeNode* node);
public:
    EquipmentTree();
    void insert(int zone, float risk, float impact);
    void display();
};

// T7: Fire Classification Tree - Fire Level = alpha(Temp) + beta(Smoke)
class FireClassTree {
private:
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, DecisionData val);
    void inorder(TreeNode* node);
public:
    FireClassTree();
    void insert(int zone, float temperature, float smoke);
    void display();
};

// T8: Wildlife Activity Tree - detects animal movement patterns
class WildlifeTree {
private:
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, DecisionData val);
    void inorder(TreeNode* node);
public:
    WildlifeTree();
    void insert(int zone, float activityLevel);
    void display();
};

// T9: Human Activity Tree - Human Risk = Movement * RestrictedAreaFactor
class HumanActivityTree {
private:
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, DecisionData val);
    void inorder(TreeNode* node);
public:
    HumanActivityTree();
    void insert(int zone, float movement, float restrictedFactor);
    void display();
};

// T10: Local Decision Tree - Decision Score = w1(Fire) + w2(Smoke) + w3(Temp)
// Rule: if Risk > 0.6 => Activate Local Response
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

// T11: Regional Escalation Tree - if FireSpreadRate > 0.5 => escalate
class RegionalTree {
private:
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, DecisionData val);
    void inorder(TreeNode* node, float spreadThreshold);
public:
    RegionalTree();
    void insert(DecisionData val);
    void escalate(float spreadThreshold);
    void display();
};

// T12: Global Emergency Tree - if sum(Risk_zones) > threshold => Global Alert
class GlobalTree {
private:
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, DecisionData val);
    float sumRisk(TreeNode* node);
    void inorder(TreeNode* node);
public:
    GlobalTree();
    void insert(DecisionData val);
    void checkGlobalAlert(float threshold);
    void display();
};

#endif
