#ifndef TREE_H
#define TREE_H

#define MAX_BRANCHS 3
#define TREE_DEPTH 10

#include "dataHolders.h"
#include <vector>
#include <memory>
#include <iostream>
#include <ctime>     //arg TIME(NULL) for srand()
#include <stdlib.h>  // srand()

struct treeNode
{
    std::shared_ptr<BaseHolder> holder;
    Holders typeHolder;
    int branchCount;
    std::vector<treeNode*> branchs;
    treeNode();
    ~treeNode();
    friend std::ostream& operator<<(std::ostream& out, treeNode& nod);
    void initHolder();
    void initBranchs();
};

void CreateTree(treeNode* root);
void PrintTree(treeNode* node);
void DeleteTree(treeNode** node);



#endif // TREE_H
