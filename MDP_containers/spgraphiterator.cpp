#include "spgraphiterator.h"

namespace spg {

template<typename T>
SPGraphIterator<T>::SPGraphIterator(const SPGraphIterator<T> &iterator)
{
    m_list = iterator.m_list;
    m_pos = iterator.m_pos;
    m_iterator = iterator.m_iterator;
}

template<typename T>
SPGraphIterator<T>::SPGraphIterator(const size_t pos, std::list<SPVertex<T> *> &list)
{
    m_list = list;
    m_iterator = m_list.iterator;
    m_pos = pos;
    for(size_t i = 0; i <m_pos; i++){
        m_iterator++;
    }
}

template<typename T>
SPGraphIterator<T> &SPGraphIterator<T>::operator ++()
{
    if(m_list.size() < m_pos+1){
        //exception
        return* this;
    }

    m_pos++;
    m_iterator++;
    return* this;
}

template<typename T>
SPGraphIterator<T> &SPGraphIterator<T>::operator +=(const size_t o)
{
    if(m_list.size() < m_pos+o){
        //exception
        return* this;
    }

    m_pos += o;
    for(size_t i = 0; i < o; i++){
        m_iterator++;
    }
    return* this;
}

template<typename T>
SPGraphIterator<T> &SPGraphIterator<T>::operator --()
{
    if(0 > m_pos-1){
        //exception
        return* this;
    }

    m_pos--;
    m_iterator--;
    return* this;
}

template<typename T>
SPGraphIterator<T> &SPGraphIterator<T>::operator -=(const size_t o)
{
    if(0 > m_pos-o){
        //exception
        return* this;
    }

    m_pos -= o;
    for(size_t i = 0; i < o; i++){
        m_iterator--;
    }
    return* this;
}

template<typename T>
bool SPGraphIterator<T>::operator ==(const SPGraphIterator<T> &other)
{
    return(m_iterator == other.m_iterator);
}

template<typename T>
bool SPGraphIterator<T>::operator !=(const SPGraphIterator<T> &other)
{
    return(m_iterator != other.m_iterator);
}

template<typename T>
SPVertex<T> *SPGraphIterator<T>::operator *()
{
    if(m_pos == m_list.size()){
        //exception
        return NULL;
    }

    return *m_iterator;
}



}
