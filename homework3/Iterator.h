#pragma once

template<class T>

class Iterator
{
public:
    explicit Iterator(const T position = 0) : it(position) {}
    bool operator != (Iterator<T> const &other) const { return it != other.it; }
    bool operator == (Iterator<T> const &other) const { return it == other.it; }
    Iterator& operator ++ () { ++it; return *this; }
    T operator * () const { return it; }
    friend std::ostream& operator << (std::ostream &os, Iterator &it);
private:
    T it;
};

template<class T>
class Range
{
public:
    Range(T from, T to) : _from(from), _to(to){}
    Iterator<T> begin() const {return Iterator<T>(_from);}
    Iterator<T> end() const {return Iterator<T>(_to);}
private:
    T _from;
    T _to;
};
