#ifndef SPGRAPHITERATOR_H
#define SPGRAPHITERATOR_H

#include"spvertex.h"

namespace spg {

template<typename T>
class SPGraphIterator
{
    std::list<SPVertex<T>*> m_list;
    size_t m_pos;
    typename std::list<SPVertex<T>*>::iterator m_iterator;
public:
    SPGraphIterator(const SPGraphIterator<T>& iterator);
    SPGraphIterator(const size_t pos, std::list<SPVertex<T>*> &list);
    SPGraphIterator<T>& operator ++();
    SPGraphIterator<T>& operator +=(const size_t o);
    SPGraphIterator<T>& operator --();
    SPGraphIterator<T>& operator -=(const size_t o);
    bool operator ==(const SPGraphIterator<T> &other);
    bool operator !=(const SPGraphIterator<T> &other);
    SPVertex<T>* operator *();
};

}

#endif // SPGRAPHITERATOR_H
