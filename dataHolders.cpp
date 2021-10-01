#include "dataHolders.h"

//IntHolder
IntHolder::IntHolder(int k)
    : data(k){}


int32_t IntHolder::getData() {
    return data;
}

void IntHolder::setData(int32_t p) {
    data=p;
}

//CharArrayHolder
CharArrayHolder::CharArrayHolder(char* p) {
    //warnign - no check lenght p
    for(int i=0;i<10;i++) {
        data[i]=*(p+i);
    }
}

char* CharArrayHolder::getData() {
    return data;
}

void CharArrayHolder::setData(char *p) {
    //warnign - no check lenght p
    for(int i=0;i<10;i++) {
        data[i]=p[i];
    }
}

//DoubleHolder
DoubleHolder::DoubleHolder(double k)
    :data(k){}

double DoubleHolder::getData() {
    return data;
}

void DoubleHolder::setData(double p) {
    data=p;
}
