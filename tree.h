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
    Holders typeHolder; //fixme
    int branchCount;
    std::vector<treeNode*> branchs;
    treeNode();
    treeNode(int32_t val,int brCnt=0);
    treeNode(char* val,int brCnt=0);
    treeNode(double val,int brCnt);
    ~treeNode();
    friend std::ostream& operator<<(std::ostream& out, treeNode& nod);
};

void treeInitBranchs(treeNode* node);   //init branchs 1 lvl
void treeInitBranchsEx(treeNode* node); //init branchs at TREE_DEPTH lvl
void treePrint(treeNode* root);
void treeDelete(treeNode* root);



#endif // TREE_H
