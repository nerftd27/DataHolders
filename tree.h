#ifndef TREE_H
#define TREE_H

#define MAX_BRANCHS 3
#define TREE_DEPTH 10
#define TREE_FILENAME "treeSerialization.txt"
#define DELIM ";" //for user-friendly view of filestream

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
    //friend std::ifstream& operator>>(std::ifstream& in, treeNode& nod); //for deserialization from filestream.No branchs init! Only count
    void initHolder(Holders typeHold=Holders::BASE);
    void initBranchs(int brCount=-1);
};

void CreateTree(treeNode* root);
void PrintTree(treeNode* node);
void DeleteTree(treeNode** node);
void SerializeTree(treeNode* root,std::ofstream& out);
void DeserializeTree(treeNode* root);
std::vector<std::string> ReadTreeFromFile();
treeNode* GetNodeFromString(std::string s);


#endif // TREE_H
