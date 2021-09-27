#include "tree.h"

//cosntrs & destrs
treeNode::treeNode()    //allocation memory realized at treeNode::initBranchs()
    :branchCount(0) {}

treeNode::~treeNode() {
    if (!branchs.empty()) {
        for(int i=0;i<branchCount;i++) {
            delete branchs[i];
            branchs[i]=nullptr;
        }
        branchs.clear();
    }
}

//funcs
void treeNode::initHolder() {
    char* s=new char[10];                   //for init CharArrayHolder
    int initTypeHolder=rand()%3;
    //switch(initTypeHolder):
    if (initTypeHolder==0) {//INT
        holder=std::make_shared<IntHolder>();
        typeHolder=Holders::INT;
        (dynamic_cast<IntHolder&>(*holder)).setData(rand()%1000);
    }
    if (initTypeHolder==1) {//CHAR_ARR
        holder=std::make_shared<CharArrayHolder>();
        typeHolder=Holders::CHAR_ARR;
        for(int j=0;j<10;j++) {
           s[j]=97+rand()%27;
        }
        (dynamic_cast<CharArrayHolder&>(*holder)).setData(s);
    }
    if (initTypeHolder==2) {//DOUBLE
        holder=std::make_shared<DoubleHolder>();
        typeHolder=Holders::DOUBLE;
        (dynamic_cast<DoubleHolder&>(*holder)).setData((double)rand()/3);
    }
    delete[] s;
}

void treeNode::initBranchs() {
    branchCount=rand()%(MAX_BRANCHS+1);
    if(branchCount) {
        branchs.resize(branchCount);
        for(int i=0;i<branchCount;i++) {
            branchs[i]=new treeNode;        //manual alloc memory!!!
            branchs[i]->initHolder();
        }
    }
}

void CreateTree(treeNode* root) {
    static int tree_depth=0;
    tree_depth++;
    root->initBranchs();
    if(!root->branchs.empty())
    {
        if (tree_depth>=TREE_DEPTH) return;
        for(int i=0;i<root->branchCount;i++) {
            CreateTree(root->branchs[i]);
        }
    }
    tree_depth--;
}

void PrintTree(treeNode* node) {
    static int tab=0;                       //for depth tree visualization
    tab++;
    if (tab>TREE_DEPTH) return;
    if(!node->branchs.empty()) {
        for(int k=0;k<node->branchCount;k++) {
             for(int i=0;i<=tab;i++) std::cout<<' ';
             std::cout<<*node->branchs[k];
             PrintTree(node->branchs[k]);
             tab--;
        }
    }
}

void DeleteTree(treeNode** root)
{
    if(!(*root)->branchs.empty()) {
        for(int i=0;i<(*root)->branchCount;i++) {
            DeleteTree(&(*root)->branchs[i]);
        }
    }
    delete *root;
    *root=nullptr;
}

std::ostream& operator<<(std::ostream& out, treeNode& nod) {
    if(nod.typeHolder==Holders::INT) {
        out.precision(0);
        out<<(std::dec)<<(dynamic_cast<IntHolder&>(*nod.holder)).getData();
    }
    if(nod.typeHolder==Holders::CHAR_ARR) {
        out.precision(0);
        out<<(dynamic_cast<CharArrayHolder&>(*nod.holder)).getData();
    }
    if(nod.typeHolder==Holders::DOUBLE) {
        out.precision(3);
        out<<(dynamic_cast<DoubleHolder&>(*nod.holder)).getData();
    }
    out<<" / branchs count:"<<nod.branchCount<<std::endl;
    return out;
}


