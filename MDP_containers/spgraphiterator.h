#ifndef SPGRAPHITERATOR_H
#define SPGRAPHITERATOR_H

#include"spvertex.h"
#include"spgexception.h"

namespace spg {

template<typename T> class SPVertex;

template<typename T>
class SPGraphIterator
{
    std::list<SPVertex<T>*>* m_list;
    int m_pos;
    typename std::list<SPVertex<T>*>::iterator m_iterator;
public:
    SPGraphIterator(const SPGraphIterator<T>& iterator);
    SPGraphIterator(const int pos, std::list<SPVertex<T> *>* list);
    SPGraphIterator<T>& operator ++();
    SPGraphIterator<T>& operator ++(int o);
    SPGraphIterator<T>& operator +=(const int o);
    SPGraphIterator<T>& operator --();
    SPGraphIterator<T>& operator --(int o);
    SPGraphIterator<T>& operator -=(const int o);
    bool operator ==(const SPGraphIterator<T> &other);
    bool operator !=(const SPGraphIterator<T> &other);
    SPVertex<T>* operator *();

};


template<typename T>
SPGraphIterator<T>::SPGraphIterator(const SPGraphIterator<T> &iterator)
{
    m_list = iterator.m_list;
    m_pos = iterator.m_pos;
    m_iterator = iterator.m_iterator;
}

template<typename T>
SPGraphIterator<T>::SPGraphIterator(const int pos, std::list<SPVertex<T> *> *list)
{
    m_list = list;
    m_iterator = m_list->begin();
    m_pos = pos;
    for(int i = 0; i < m_pos; i++){
        m_iterator++;
    }
}

template<typename T>
SPGraphIterator<T>& SPGraphIterator<T>::operator ++()
{
    int s = m_list->size();
    if(s < m_pos+1){
        THROW_SPG_ITERATOR_EXCEPTION(this,"Increment is going out of bonds",T);
        return* this;
    }

    m_pos++;
    m_iterator++;
    return* this;
}

template<typename T>
SPGraphIterator<T> &SPGraphIterator<T>::operator ++(int o)
{
    int s = m_list->size();
    if(s < m_pos+o+1){
        THROW_SPG_ITERATOR_EXCEPTION(this,"Increment is going out of bonds",T);
        return* this;
    }

    m_pos++;
    m_iterator++;
    return* this;
}

template<typename T>
SPGraphIterator<T> &SPGraphIterator<T>::operator +=(const int o)
{
    int s = m_list->size();
    if(s < m_pos+o){
        THROW_SPG_ITERATOR_EXCEPTION(this,"Increment is going out of bonds",T);
        return* this;
    }

    m_pos += o;
    for(int i = 0; i < o; i++){
        m_iterator++;
    }
    return* this;
}

template<typename T>
SPGraphIterator<T> &SPGraphIterator<T>::operator --()
{
    if(0 > m_pos-1){
        THROW_SPG_ITERATOR_EXCEPTION(this,"Decrement is going out of bonds",T);
        return* this;
    }

    m_pos--;
    m_iterator--;
    return* this;
}

template<typename T>
SPGraphIterator<T> &SPGraphIterator<T>::operator --(int o)
{
    if(0 > m_pos-o-1){
        THROW_SPG_ITERATOR_EXCEPTION(this,"Decrement is going out of bonds",T);
        return* this;
    }

    m_pos -= o;
    for(int i = 0; i < o; i++){
        m_iterator--;
    }
    return* this;
}

template<typename T>
SPGraphIterator<T> &SPGraphIterator<T>::operator -=(const int o)
{
    if(0 > m_pos-o){
        THROW_SPG_ITERATOR_EXCEPTION(this,"Decrement is going out of bonds",T);
        return* this;
    }

    m_pos --;
    m_iterator--;

    return* this;
}

template<typename T>
bool SPGraphIterator<T>::operator ==(const SPGraphIterator<T> &other)
{
    return((m_pos == other.m_pos) && (m_list == other.m_list));
}

template<typename T>
bool SPGraphIterator<T>::operator !=(const SPGraphIterator<T> &other)
{
    return(m_iterator != other.m_iterator);
}

template<typename T>
SPVertex<T> *SPGraphIterator<T>::operator *()
{
    if(m_pos == m_list->size()){
        THROW_SPG_ITERATOR_EXCEPTION((this),"Iterator points on NULL",T);
        return NULL;
    }

    return *m_iterator;
}

}

#endif // SPGRAPHITERATOR_H
