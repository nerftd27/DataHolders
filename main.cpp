#include <iostream>
#include "tree.h"

int main()
{

    treeNode* root=new treeNode;
    srand(time(NULL));
    std::cout<<"max branches of single node: "<<MAX_BRANCHS<<std::endl;
    std::cout<<"max depth of tree: "<<TREE_DEPTH<<std::endl;
    root->initHolder();
    CreateTree(root);
    std::cout<<"root: "<<*root;
    std::ofstream fout(TREE_FILENAME);
    PrintTree(root,fout);







    DeleteTree(&root);
    std::cout<<"\nfinish\n";
    char user_command;
    std::cin>>user_command;
    return 0;
}


