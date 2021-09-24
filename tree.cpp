#include "tree.h"

//cosntructs
treeNode::treeNode()
    :branchCount(0)
{
   branchs.resize(branchCount);
   holder=std::make_shared<BaseHolder>();
}

treeNode::treeNode(int32_t val,int brCnt)
    :typeHolder(Holders::INT),branchCount(brCnt)
{
    branchs.resize(branchCount);
    holder=std::make_shared<IntHolder>();
    (dynamic_cast<IntHolder&>(*this->holder)).setData(val);
    for(int i=0;i<branchCount;i++) {
        branchs[i]=new treeNode();
    }
}

treeNode::treeNode(char* val,int brCnt)
    :typeHolder(Holders::CHAR_ARR),branchCount(brCnt)
{
    branchs.resize(branchCount);
    holder=std::make_shared<CharArrayHolder>();
    (dynamic_cast<CharArrayHolder&>(*this->holder)).setData(val);
    for(int i=0;i<branchCount;i++) {
        branchs[i]=new treeNode();
    }
}

treeNode::treeNode(double val,int brCnt)
    :typeHolder(Holders::DOUBLE),branchCount(brCnt)
{
    branchs.resize(branchCount);
    holder=std::make_shared<DoubleHolder>();
    (dynamic_cast<DoubleHolder&>(*this->holder)).setData(val);
    for(int i=0;i<branchCount;i++) {
        branchs[i]=new treeNode();
    }
}

//destruct
treeNode::~treeNode() {
    if (!branchCount) {
        return;
    }
    for(int i=0;i<branchCount;i++) {
        delete branchs[i];
    }
}

//func
void treeInitBranchs(treeNode* node) {
    node->branchCount=rand()%(MAX_BRANCHS+1);
    if (node->branchCount) {
        node->branchs.resize(node->branchCount);
        char* s=new char[10];//for init CharArrayHolder
        for(int i=0;i<node->branchCount;i++) {
            int initTypeHolder=rand()%3;
            //switch(initTypeHolder):
            node->branchs[i]=new treeNode();
            if (initTypeHolder==0) {//INT
                node->branchs[i]->holder=std::make_unique<IntHolder>();
                node->branchs[i]->typeHolder=Holders::INT;
                (dynamic_cast<IntHolder&>(*node->branchs[i]->holder)).setData(rand()%1000);
            }
            if (initTypeHolder==1) {//CHAR_ARR
                node->branchs[i]->holder=std::make_unique<CharArrayHolder>();
                node->branchs[i]->typeHolder=Holders::CHAR_ARR;
                for(int j=0;j<10;j++) {
                   s[j]=97+rand()%27;
                }
                (dynamic_cast<CharArrayHolder&>(*node->branchs[i]->holder)).setData(s);
            }
            if (initTypeHolder==2) {//DOUBLE
                node->branchs[i]->holder=std::make_unique<DoubleHolder>();
                node->branchs[i]->typeHolder=Holders::DOUBLE;
                (dynamic_cast<DoubleHolder&>(*node->branchs[i]->holder)).setData((double)rand()/3);
            }
        }
        delete[] s;
    }
}

void treeInitBranchsEx(treeNode* node) {
    static int tree_depth=0;
    tree_depth++;
    treeInitBranchs(node);
    if(node->branchCount)
    {
        if (tree_depth>=TREE_DEPTH) return;
        treeNode* n=new treeNode;
        for(int i=0;i<node->branchCount;i++) {
            n=node->branchs[i];
            treeInitBranchsEx(n);
        }

    }
    tree_depth--;
}

void treePrint(treeNode* root)
{
    static int tab=0;//for depth tree visualization
    tab++;
    if (tab>TREE_DEPTH) return;
    if(root->branchCount) {
        for(int k=0;k<root->branchCount;k++) {
             for(int i=0;i<=tab;i++) std::cout<<' ';
             std::cout<<*(root->branchs[k]);
             treePrint(root->branchs[k]);
             tab--;
        }
    }
}

void treeDelete(treeNode* root)
{
    if(root->branchs.empty()) {
        delete root;
    } else {
        for(int i=0;i<root->branchCount;i++) {
            treeDelete(root->branchs[i]);
        }
    }
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




