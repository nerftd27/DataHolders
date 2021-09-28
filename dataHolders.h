#ifndef DATAHOLDERS_H
#define DATAHOLDERS_H

#include <stdint.h>

enum class Holders {
    BASE,INT,CHAR_ARR,DOUBLE
};

union union_data {
    int32_t i;
    double d;
    char intToChar[sizeof (int32_t)/sizeof (char)];     //by the right its need roundUp dividing
    double doubleToChar[sizeof(double)/sizeof(char)];
};

class BaseHolder
{
    //void* data;
public:
    BaseHolder()=default;
    virtual ~BaseHolder()=default;
    //void* getData();
    //void setData(void* p);
};

class IntHolder:public BaseHolder
{
    int32_t data;
public:
    IntHolder(int32_t k=255);
    ~IntHolder()=default;
    int32_t getData();
    void setData(int32_t p);
};

class CharArrayHolder:public BaseHolder
{
    char data[10];
public:
    CharArrayHolder(char* p="0123456789");//warning - no control length p
    ~CharArrayHolder()=default;
    char* getData();
    void setData(char* p);
};

class DoubleHolder:public BaseHolder
{
    double data;
public:
    DoubleHolder(double k=0.1);
    ~DoubleHolder()=default;
    double getData();
    void setData(double p);

};

#endif // DATAHOLDERS_H

