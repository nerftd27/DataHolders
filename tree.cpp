#include "tree.h"

//treeNode cosntrs & destrs
treeNode::treeNode()    //allocation memory realized at treeNode::initBranchs()
    :branchCount(0) {}

treeNode::~treeNode() {
    if (!branchs.empty()) {
        for(int i=0;i<branchs.size();i++) {
            delete branchs[i];
            branchs[i]=nullptr;
        }
        branchs.clear();
    }
}

//treeNode::funcs
void treeNode::initHolder(Holders th) {
    int initTypeHolder;
    if (th==Holders::BASE) {                //random init type holder or by arg
        initTypeHolder=rand()%3;
    } else {
        initTypeHolder=(int)th-1;
    }
    char* s=new char[10];                   //for init CharArrayHolder
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
           *(s+j)=65+rand()%26;
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

void treeNode::initBranchs(int brCount) {
    if (brCount==-1) {                      //random init branches count or by arg
        branchCount=rand()%(MAX_BRANCHS+1);
    } else {
        branchCount=brCount;
    }

    if(branchCount) {
        branchs.resize(branchCount);
        for(int i=0;i<branchCount;i++) {
            branchs[i]=new treeNode;        //manual alloc memory!!!
            branchs[i]->initHolder();
        }
    }
}

//Tree funcs
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

void SerializeTree(treeNode* root, std::ofstream& out) {
    out<<*root;
    if(!root->branchs.empty()) {
        for(int k=0;k<root->branchCount;k++) {
             //out<<*root->branchs[k];
             SerializeTree(root->branchs[k], out);
        }
    }
}

void DeserializeTree(treeNode* root) {
    std::vector<std::string>v=ReadTreeFromFile();


    for(int i=0;i<v.size();i++) {
        GetNodeFromString(v[i]);
    }
}

std::vector<std::string> ReadTreeFromFile() {
    std::vector<std::string> res;
    std::ifstream in(TREE_FILENAME);
    if (!in.is_open()) return res;
    std::string s;
    for (;!in.eof();) {
        in>>s;
        res.push_back(s);
    }
    res.pop_back();     //last element duplicated, remove it
    in.close();
    return res;
}

treeNode* GetNodeFromString(std::string s) {
    treeNode* node=new treeNode;
    char tHolder=s[0];
    size_t pos=s.find_last_of(';');
    char chBranchCnt=s[pos+1];
    //set holder type and value
    std::string strData=s.substr(2,pos-2);
    if(tHolder==48) {
        node->initHolder(Holders::INT);
        (dynamic_cast<IntHolder&>(*node->holder)).setData(std::stoi(strData));
    }
    if(tHolder==49) {
        node->initHolder(Holders::CHAR_ARR);
        char* charData=new char[10];        //buffer need to limit char count at 10. Otherwise in result have additional garbage. wtf?!
        charData=const_cast<char*>(strData.c_str());
        (dynamic_cast<CharArrayHolder&>(*node->holder)).setData(charData);
    }
    if(tHolder==50) {
        node->initHolder(Holders::DOUBLE);
        (dynamic_cast<DoubleHolder&>(*node->holder)).setData(std::stod(strData));
    }
    node->initBranchs(chBranchCnt-'0');

    std::cout<<*node;
    return  node;
}


// input/output operators override
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

std::ofstream& operator<<(std::ofstream& out, treeNode& nod) {
    if(nod.typeHolder==Holders::INT) {
        out<<0<<DELIM;
        out<<(dynamic_cast<IntHolder&>(*nod.holder)).getData()<<DELIM;
    }
    if(nod.typeHolder==Holders::CHAR_ARR) {
        out<<1<<DELIM;
        out<<(dynamic_cast<CharArrayHolder&>(*nod.holder)).getData()<<DELIM;
    }
    if(nod.typeHolder==Holders::DOUBLE) {
        out<<2<<DELIM;
        out<<(dynamic_cast<DoubleHolder&>(*nod.holder)).getData()<<DELIM;
    }
    out<<nod.branchCount<<' ';;
    return out;
}

/*std::ifstream& operator>>(std::ifstream& in, treeNode& nod)
{
    int tHolder,brCnt;
    char delim;
    in>>tHolder>>delim;
    if(tHolder==0) {
        int32_t data;
        in>>data>>delim;
        nod.initHolder(Holders::INT);
        (dynamic_cast<IntHolder&>(*nod.holder)).setData(data);
    }
    if(tHolder==1) {
        char* data=new char[10];
        in.read(data,sizeof (char)*10);
        nod.initHolder(Holders::CHAR_ARR);
        (dynamic_cast<CharArrayHolder&>(*nod.holder)).setData(data);
        delete[] data;
    }
    if(tHolder==2) {
        double data;
        in>>data>>delim;
        nod.initHolder(Holders::DOUBLE);
        (dynamic_cast<DoubleHolder&>(*nod.holder)).setData(data);
    }
    in>>brCnt;
    nod.initBranchs(brCnt);
    return in;
}*/


