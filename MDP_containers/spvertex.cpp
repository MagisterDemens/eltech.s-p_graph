#include "spvertex.h"

namespace spg{

template<typename T>
SPVertex<T>::SPVertex(T data)
{
    this->m_data = data;
}


template<typename T>
void SPVertex<T>::setBonds(std::list<SPVertex<T> *> v_list, bool out)
{
    if(out){
        m_out = v_list;
    }
    else{
        m_in = v_list;
    }
}

template<typename T>
void SPVertex<T>::addBondVertex(SPVertex<T> *vertex, bool out)
{
    if(out){
        auto pos = std::find(m_out.begin(), m_out.end(), vertex);
        if(pos != m_out.end()){
            //exception
            return;
        }
        m_out.push_back(vertex);
    }
    else{
        auto pos = std::find(m_in.begin(), m_in.end(), vertex);
        if(pos != m_in.end()){
            //exception
            return;
        }
        m_in.push_back(vertex);
    }
}

template<typename T>
void SPVertex<T>::deleteBondVertex(SPVertex<T> *vertex, bool out)
{
    if(out){
        auto pos = std::find(m_out.begin(), m_out.end(), vertex);
        if(pos == m_out.end()){
            //exception
            return;
        }
        m_out.erase(pos);
    }
    else{
        auto pos = std::find(m_in.begin(), m_in.end(), vertex);
        if(pos == m_in.end()){
            //exception
            return;
        }
        m_in.erase(pos);
    }
}

template<typename T>
void SPVertex<T>::clearBonds(bool out)
{
    if(out){
        m_out.clear();
    }
    else{
        m_in.clear();
    }
}

template<typename T>
unsigned int SPVertex<T>::countBonds(bool out)
{
    if(out){
        return m_out.size();
    }
    else{
        return m_in.size();
    }
}

template<typename T>
const std::list<SPVertex<T> *> SPVertex<T>::getBonds(bool out)
{
    if(out){
        return m_out;
    }
    else{
        return m_in;
    }
}

template<typename T>
void SPVertex<T>::setData(T data)
{
    this->m_data = data;
}

template<typename T>
T SPVertex<T>::getData()
{
    return m_data;
}

template<typename T>
SPVertex<T>::~SPVertex()
{
    this->clearBonds();
    this->clearBonds(true);
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const SPVertex<T> *spvertex)
{
    return os;
}

template<typename T>
std::istream& operator>>(std::istream &is, SPGraph<T> *spvertex)
{
    return is;
}

}
