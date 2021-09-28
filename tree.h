#ifndef TREE_H
#define TREE_H

#define MAX_BRANCHS 3
#define TREE_DEPTH 10
#define TREE_FILENAME "treeSerialization.txt"
#define DIVIDER ";"

#include "dataHolders.h"
#include <vector>
#include <memory>
#include <iostream>
#include <ctime>     //arg time(NULL) for srand()
#include <stdlib.h>  // srand()
#include <fstream>

struct treeNode
{
    std::shared_ptr<BaseHolder> holder;
    Holders typeHolder;
    int branchCount;
    std::vector<treeNode*> branchs;
    treeNode();
    ~treeNode();
    friend std::ostream& operator<<(std::ostream& out, treeNode& nod); //for std::cout
    friend std::ofstream& operator<<(std::ofstream& out, treeNode& nod); //for serialization to filestream
   // friend std::ifstream& operator>>(std::ifstream& in, treeNode& nod); //for unserialization from filestream
    void initHolder();
    void initBranchs();
};

void CreateTree(treeNode* root);
void PrintTree(treeNode* node, std::ofstream& out);
void DeleteTree(treeNode** node);



#endif // TREE_H
