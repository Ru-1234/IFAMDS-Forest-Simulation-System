#include "tree.h"

//T1: ZONE HIERARCHY TREE
// divides forest: Forest -> Zone A/B -> sub-zones
// Time Complexity: build O(1), printTree O(n), display O(n)
ZoneHierarchyTree::ZoneHierarchyTree() {
    root = NULL;
}

void ZoneHierarchyTree::build() {
    root = new ZoneNode(0, "Forest");

    ZoneNode* zA = new ZoneNode(1, "Zone-A");
    ZoneNode* zB = new ZoneNode(2, "Zone-B");

    zA->children[zA->childCount++] = new ZoneNode(3, "Zone-A1");
    zA->children[zA->childCount++] = new ZoneNode(4, "Zone-A2");
    zB->children[zB->childCount++] = new ZoneNode(5, "Zone-B1");
    zB->children[zB->childCount++] = new ZoneNode(6, "Zone-B2");

    root->children[root->childCount++] = zA;
    root->children[root->childCount++] = zB;

    cout << "T1: Zone Hierarchy Built" << endl;
}

void ZoneHierarchyTree::printTree(ZoneNode* node, int depth) {
    if(node == NULL) return;

    for(int i=0;i<depth;i++) cout << "  ";
    cout << "|-- " << node->label << " (ID:" << node->zoneID << ")" << endl;

    for(int i=0;i<node->childCount;i++)
        printTree(node->children[i], depth + 1);
}

void ZoneHierarchyTree::display() {
    cout << "T1: Zone Hierarchy:" << endl;
    printTree(root, 0);
}


// --- T2: SUB-ZONE DECOMPOSITION TREE ---
// each zone split into 4 directions: N, S, E, W
// Time Complexity: build O(1), printTree O(n), display O(n)

SubZoneTree::SubZoneTree() {
    root = NULL;
}

void SubZoneTree::build() {
    root = new ZoneNode(0, "Zone-Root");

    string dirs[] = {"North", "South", "East", "West"};
    for(int i=0;i<4;i++)
        root->children[root->childCount++] = new ZoneNode(i+1, dirs[i]);

    cout << "T2: Sub-Zone Tree Built" << endl;
}

void SubZoneTree::printTree(ZoneNode* node, int depth) {
    if(node == NULL) return;

    for(int i=0;i<depth;i++) cout << "  ";
    cout << "|-- " << node->label << " (ID:" << node->zoneID << ")" << endl;

    for(int i=0;i<node->childCount;i++)
        printTree(node->children[i], depth + 1);
}

void SubZoneTree::display() {
    cout << "T2: Sub-Zone Tree:" << endl;
    printTree(root, 0);
}


// --- T3: TERRAIN CLASSIFICATION TREE ---
// Terrain Risk = (slope + dryness + density) / 3
// Time Complexity: insert O(log n) avg, display O(n)

TerrainTree::TerrainTree() {
    root = NULL;
}

TreeNode* TerrainTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL) return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void TerrainTree::insert(int zone, float slope, float dryness, float density) {
    float risk = (slope + dryness + density) / 3.0f;
    root = insertRec(root, {zone, risk});
    cout << "T3: Terrain Zone " << zone << " Risk=" << risk << endl;
}

void TerrainTree::inorder(TreeNode* node) {
    if(node == NULL) return;
    inorder(node->left);
    cout << "Zone " << node->data.zone << " TerrainRisk=" << node->data.risk;
    if(node->data.risk > 0.7) cout << " [HIGH RISK]";
    cout << endl;
    inorder(node->right);
}

void TerrainTree::display() {
    cout << "T3: Terrain Classification:" << endl;
    inorder(root);
}


// --- T4: WATER RESOURCE TREE ---
// Water Availability = available / required
// Time Complexity: insert O(log n) avg, display O(n)

WaterTree::WaterTree() {
    root = NULL;
}

TreeNode* WaterTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL) return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void WaterTree::insert(int zone, float available, float required) {
    float avail = (required > 0) ? (available / required) : 0;
    root = insertRec(root, {zone, avail});
    cout << "T4: Water Zone " << zone << " Availability=" << avail << endl;
}

void WaterTree::inorder(TreeNode* node) {
    if(node == NULL) return;
    inorder(node->left);
    cout << "Zone " << node->data.zone << " Water=" << node->data.risk;
    if(node->data.risk < 0.5) cout << " [LOW WATER]";
    else cout << " [OK]";
    cout << endl;
    inorder(node->right);
}

void WaterTree::display() {
    cout << "T4: Water Resource Tree:" << endl;
    inorder(root);
}


// --- T5: FIRE CONTROL RESOURCE TREE ---
// tracks fire response tools per zone (0 = none, 1 = fully equipped)
// Time Complexity: insert O(log n) avg, display O(n)

FireControlTree::FireControlTree() {
    root = NULL;
}

TreeNode* FireControlTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL) return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void FireControlTree::insert(int zone, float resourceLevel) {
    root = insertRec(root, {zone, resourceLevel});
    cout << "T5: FireControl Zone " << zone << " Resources=" << resourceLevel << endl;
}

void FireControlTree::inorder(TreeNode* node) {
    if(node == NULL) return;
    inorder(node->left);
    cout << "Zone " << node->data.zone << " Resources=" << node->data.risk;
    if(node->data.risk < 0.3) cout << " [INSUFFICIENT]";
    else cout << " [ADEQUATE]";
    cout << endl;
    inorder(node->right);
}

void FireControlTree::display() {
    cout << "T5: Fire Control Resources:" << endl;
    inorder(root);
}


// --- T6: EQUIPMENT ALLOCATION TREE ---
// Priority = Risk * Impact
// Time Complexity: insert O(log n) avg, display O(n)

EquipmentTree::EquipmentTree() {
    root = NULL;
}

TreeNode* EquipmentTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL) return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void EquipmentTree::insert(int zone, float risk, float impact) {
    float priority = risk * impact;
    root = insertRec(root, {zone, priority});
    cout << "T6: Equipment Zone " << zone << " Priority=" << priority << endl;
}

void EquipmentTree::inorder(TreeNode* node) {
    if(node == NULL) return;
    inorder(node->left);
    cout << "Zone " << node->data.zone << " Priority=" << node->data.risk;
    if(node->data.risk > 0.6) cout << " [ALLOCATE NOW]";
    cout << endl;
    inorder(node->right);
}

void EquipmentTree::display() {
    cout << "T6: Equipment Allocation:" << endl;
    inorder(root);
}


// --- T7: FIRE CLASSIFICATION TREE ---
// Fire Level = alpha(Temp/100) + beta(Smoke/100), alpha=0.5 beta=0.5
// Time Complexity: insert O(log n) avg, display O(n)

FireClassTree::FireClassTree() {
    root = NULL;
}

TreeNode* FireClassTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL) return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void FireClassTree::insert(int zone, float temperature, float smoke) {
    float fireLevel = 0.5f * (temperature / 100.0f) + 0.5f * (smoke / 100.0f);
    root = insertRec(root, {zone, fireLevel});
    cout << "T7: Fire Zone " << zone << " Level=" << fireLevel << endl;
}

void FireClassTree::inorder(TreeNode* node) {
    if(node == NULL) return;
    inorder(node->left);
    cout << "Zone " << node->data.zone << " FireLevel=" << node->data.risk;
    if(node->data.risk > 0.7)      cout << " [MAJOR FIRE]";
    else if(node->data.risk > 0.4) cout << " [MODERATE]";
    else                           cout << " [LOW]";
    cout << endl;
    inorder(node->right);
}

void FireClassTree::display() {
    cout << "T7: Fire Classification:" << endl;
    inorder(root);
}


// --- T8: WILDLIFE ACTIVITY TREE ---
// high activity during fire = wildlife fleeing
// Time Complexity: insert O(log n) avg, display O(n)

WildlifeTree::WildlifeTree() {
    root = NULL;
}

TreeNode* WildlifeTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL) return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void WildlifeTree::insert(int zone, float activityLevel) {
    root = insertRec(root, {zone, activityLevel});
    cout << "T8: Wildlife Zone " << zone << " Activity=" << activityLevel << endl;
}

void WildlifeTree::inorder(TreeNode* node) {
    if(node == NULL) return;
    inorder(node->left);
    cout << "Zone " << node->data.zone << " Activity=" << node->data.risk;
    if(node->data.risk > 0.7) cout << " [FLEEING - FIRE LIKELY]";
    cout << endl;
    inorder(node->right);
}

void WildlifeTree::display() {
    cout << "T8: Wildlife Activity:" << endl;
    inorder(root);
}


// --- T9: HUMAN ACTIVITY TREE ---
// Human Risk = Movement * RestrictedAreaFactor
// Time Complexity: insert O(log n) avg, display O(n)

HumanActivityTree::HumanActivityTree() {
    root = NULL;
}

TreeNode* HumanActivityTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL) return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void HumanActivityTree::insert(int zone, float movement, float restrictedFactor) {
    float humanRisk = movement * restrictedFactor;
    root = insertRec(root, {zone, humanRisk});
    cout << "T9: Human Zone " << zone << " Risk=" << humanRisk << endl;
}

void HumanActivityTree::inorder(TreeNode* node) {
    if(node == NULL) return;
    inorder(node->left);
    cout << "Zone " << node->data.zone << " HumanRisk=" << node->data.risk;
    if(node->data.risk > 0.5) cout << " [INTRUSION DETECTED]";
    cout << endl;
    inorder(node->right);
}

void HumanActivityTree::display() {
    cout << "T9: Human Activity:" << endl;
    inorder(root);
}


// --- T10: LOCAL DECISION TREE ---
// Decision Score = w1(Fire) + w2(Smoke) + w3(Temp)
// Rule: Risk > 0.6 => EMERGENCY
// Time Complexity: insert O(log n) avg, display O(n)

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


// --- T11: REGIONAL ESCALATION TREE ---
// if FireSpreadRate > 0.5 => escalate to nearby zones
// Time Complexity: insert O(log n) avg, escalate O(n)

RegionalTree::RegionalTree() {
    root = NULL;
}

TreeNode* RegionalTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL) return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void RegionalTree::insert(DecisionData val) {
    root = insertRec(root, val);
    cout << "T11: Regional Node Zone " << val.zone << endl;
}

void RegionalTree::inorder(TreeNode* node, float spreadThreshold) {
    if(node == NULL) return;
    inorder(node->left, spreadThreshold);

    if(node->data.risk > spreadThreshold)
        cout << "T11: ESCALATE Zone " << node->data.zone << " (spread=" << node->data.risk << ")" << endl;
    else
        cout << "T11: Zone " << node->data.zone << " -> Normal" << endl;

    inorder(node->right, spreadThreshold);
}

void RegionalTree::escalate(float spreadThreshold) {
    cout << "T11: Regional Escalation:" << endl;
    inorder(root, spreadThreshold);
}

void RegionalTree::display() {
    escalate(0.5f);
}


// --- T12: GLOBAL EMERGENCY TREE ---
// Global condition: sum(Risk_all_zones) > threshold => Global Alert
// Time Complexity: insert O(log n) avg, checkGlobalAlert O(n)

GlobalTree::GlobalTree() {
    root = NULL;
}

TreeNode* GlobalTree::insertRec(TreeNode* node, DecisionData val) {
    if(node == NULL) return new TreeNode(val);

    if(val.risk < node->data.risk)
        node->left = insertRec(node->left, val);
    else
        node->right = insertRec(node->right, val);

    return node;
}

void GlobalTree::insert(DecisionData val) {
    root = insertRec(root, val);
    cout << "T12: Global Node Zone " << val.zone << endl;
}

float GlobalTree::sumRisk(TreeNode* node) {                                // O(n) - time complexity
    if(node == NULL) return 0;
    return node->data.risk + sumRisk(node->left) + sumRisk(node->right);
}

void GlobalTree::checkGlobalAlert(float threshold) {
    float total = sumRisk(root);
    cout << "T12: Total Risk = " << total << endl;

    if(total > threshold)
        cout << "T12: GLOBAL EMERGENCY ACTIVATED!" << endl;
    else
        cout << "T12: System stable." << endl;
}

void GlobalTree::inorder(TreeNode* node) {                                            // O(n) - time complexity
    if(node == NULL) return;
    inorder(node->left);
    cout << "Zone " << node->data.zone << " Risk=" << node->data.risk << endl;
    inorder(node->right);
}

void GlobalTree::display() {
    cout << "T12: Global Emergency Tree:" << endl;
    inorder(root);
}
