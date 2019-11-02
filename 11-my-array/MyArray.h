#ifndef __JJC__MYARRAY__H__
#define __JJC__MYARRAY__H__

// double array
// size(MyArray)

class MyArray {
private:

    int sz;       // 4 bytes
    double* data; // 8 bytes

public:

    MyArray(int sz = 16);
    ~MyArray(void);

    void setAt(double d, int index);
    double getAt(int index);

};

double MyArray::getAt(int index) {
    if(index < 0 || index >= this->sz) {
        std::cout << "MyArray::getAt : invalid index";
        exit(1);
    }

    return this->data[index];
}

void MyArray::setAt(double d, int index) {
    if(index < 0 || index >= this->sz) {
        std::cout << "MyArray::setAt : invalid index";
        exit(1);
    }

    // if we got to this point, we have a safe index
    this->data[index] = d;
}

MyArray::MyArray(int sz) {
    this->data = new double[sz];
    this->sz = sz;
}

MyArray::~MyArray(void) {
    delete[] this->data;
}

#endif // __JJC__MYARRAY__H__
