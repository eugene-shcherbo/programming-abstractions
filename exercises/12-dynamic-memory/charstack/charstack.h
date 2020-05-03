#ifndef CHARSTACK_H
#define CHARSTACK_H


class CharStack
{
public:
    CharStack();
    ~CharStack();
    CharStack(const CharStack& src);

    bool isEmpty() const;
    int size() const;
    char peek() const;
    void push(char ch);
    char pop();
    void clear();

    CharStack& operator=(const CharStack& src);

private:
    static const int INITIAL_CAPACITY = 10;

    char* items;
    int count;
    int capacity;

    void extendCapacity();
    void deepCopy(const CharStack& src);
};

#endif // CHARSTACK_H
