
#ifndef _intarray_h_
#define _intarray_h_

class IntArray {
public:
    IntArray(unsigned long n);
    IntArray(const IntArray& other);
    ~IntArray();

    unsigned long size();
    int get(unsigned long k);
    void put(unsigned long k, int val);

    int& operator[](unsigned long k);
    IntArray& operator=(const IntArray& other);

private:
    unsigned long capacity_;
    int* array_;
    bool inBounds(unsigned long pos);
    void deepCopy(const IntArray& other);
};

#endif
