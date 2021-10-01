#include <iostream>
#include "tree.h"

int main()
{

    treeNode* root=new treeNode;
    treeNode* node=new treeNode;
    srand(time(NULL));
    std::cout<<"max branches of single node: "<<MAX_BRANCHS<<std::endl;
    std::cout<<"max depth of tree: "<<TREE_DEPTH<<std::endl;
    root->initHolder(Holders::INT);
    CreateTree(root);
    std::cout<<"\nroot: "<<*root;
    std::ofstream fout(TREE_FILENAME);  //no check for open filestream;
    SerializeTree(root, fout);
    PrintTree(root);
    fout.close();

    std::cout<<"\nDeserialized data(not in TREE format, single nodes):\n";
    DeserializeTree(node);


    DeleteTree(&root);
    std::cout<<"\nfinish\n";
    /*char user_command;
    std::cin>>user_command;*/
    return 0;
}


