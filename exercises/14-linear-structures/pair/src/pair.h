#ifndef _pair_h_
#define _pair_h_

template <typename T1, typename T2>
class Pair {

public:
    Pair();
    Pair(T1 first, T2 second);

    T1 first() const;
    T2 second() const;

private:
    T1 first_;
    T2 second_;
};

template <typename T1, typename T2>
Pair<T1, T2>::Pair() {
    first_ = T1();
    second_ = T2();
}

template <typename T1, typename T2>
Pair<T1, T2>::Pair(T1 first, T2 second) {
    first_ = first;
    second_ = second;
}

template <typename T1, typename T2>
T1 Pair<T1, T2>::first() const {
    return first_;
}

template <typename T1, typename T2>
T2 Pair<T1, T2>::second() const {
    return second_;
}

#endif
