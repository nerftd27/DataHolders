#include <iostream>
#include "tree.h"
int main()
{
    srand(time(NULL));
    treeNode* root=new treeNode(444,3);
    treeInitBranchsEx(root);
    std::cout<<"max branchs of single node:"<<MAX_BRANCHS<<std::endl;
    std::cout<<"max depth of tree:"<<TREE_DEPTH<<std::endl;
    std::cout<<"root:"<<*root;
    treePrint(root);
    treeDelete(root);



    char user_command;
    std::cin>>user_command;
    return 0;
}
