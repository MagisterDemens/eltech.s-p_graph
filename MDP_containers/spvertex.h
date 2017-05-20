#ifndef SPVERTEX_H
#define SPVERTEX_H

#include<list>
#include<algorithm>
#include"spgexception.h"
#include"spmanipulator.h"

namespace spg {

template<typename T> class SPGraph;
//template<typename T> class SPGraphManipulator;

enum VertexBondType{
    VertexStartSingle,
    VertexStartFull,
    VertexEndSingle,
    VertexEndFull,
    VertexMidSingle,
    VertexMidFull,
    VertexMidLeft,
    VertexMidRight,
    VertexNonCorrect
};

template<typename T>
class SPVertex
{
    friend class SPGraph<T>;
    //friend class SPGraphManipulator<T>;

    T m_data;
    std::list<SPVertex<T>*> m_in;
    std::list<SPVertex<T>*> m_out;

    void setBond(std::list<SPVertex<T>*> list, bool out = false);
    std::list<SPVertex<T>*> getBond(bool out = false);
    void clearBond(bool out = false);
    void addBondVertex(SPVertex<T>* vertex, bool out = false);
    void deleteBondVertex(SPVertex<T>* vertex, bool out = false);

public:
    SPVertex(T data);

    void setData(T data);
    T getData() const;

    size_t bondCount(bool out = false) const;
    VertexBondType BondType() const;
/*
    void setBond(std::list<SPVertex<T>*> list, bool out = false);
    std::list<SPVertex<T>*> getBond(bool out = false);*/

    template<typename I>
    friend std::ostream& operator << (std::ostream& os, const SPVertex<I>* vertex);
    template<typename O>
    friend std::istream& operator >> (std::istream& is, SPVertex<O>* vertex);

    ~SPVertex();

};

template<typename T>
void SPVertex<T>::setBond(std::list<SPVertex<T> *> list, bool out)
{
    if(out){
        m_out = list;
    }
    else{
        m_in = list;
    }
}

template<typename T>
std::list<SPVertex<T> *> SPVertex<T>::getBond(bool out)
{
    if(out){
        return m_out;
    }
    else{
        return m_in;
    }
}

template<typename T>
void SPVertex<T>::clearBond(bool out)
{
    if(out){
        m_out.clear();
    }
    else{
        m_in.clear();
    }
}

template<typename T>
void SPVertex<T>::addBondVertex(SPVertex<T> *vertex, bool out)
{
    if(vertex == NULL){
        THROW_SPG_NULL_POINTER_EXCEPTION("NULL pointer");
        return;
    }


    if(out){
        auto pos = std::find(m_out.begin(), m_out.end(), vertex);
        if(pos != m_out.end()){
            THROW_SPG_VERTEX_EXCEPTION("Vertex already in bond");
            return;
        }
        m_out.push_back(vertex);
    }
    else{
        auto pos = std::find(m_in.begin(), m_in.end(), vertex);
        if(pos != m_in.end()){
            THROW_SPG_VERTEX_EXCEPTION("Vertex already in bond");
            return;
        }
        m_in.push_back(vertex);
    }
}

template<typename T>
void SPVertex<T>::deleteBondVertex(SPVertex<T> *vertex, bool out)
{
    if(vertex == NULL){
        THROW_SPG_NULL_POINTER_EXCEPTION("NULL pointer");
        return;
    }

    if(out){
        auto pos = std::find(m_out.begin(), m_out.end(), vertex);
        if(pos == m_out.end()){
            THROW_SPG_VERTEX_EXCEPTION("There is not matching vertex in bond");
        }
        m_out.erase(pos);
    }
    else{
        auto pos = std::find(m_in.begin(), m_in.end(), vertex);
        if(pos == m_in.end()){
            THROW_SPG_VERTEX_EXCEPTION("There is not matching vertex in bond");
        }
        m_in.erase(pos);
    }
}

template<typename T>
SPVertex<T>::SPVertex(T data)
{
    m_data = data;
}

template<typename T>
void SPVertex<T>::setData(T data)
{
    m_data = data;
}

template<typename T>
T SPVertex<T>::getData() const
{
    return m_data;
}

template<typename T>
size_t SPVertex<T>::bondCount(bool out) const
{
    if(out){
        return m_out.size();
    }
    else{
        return m_in.size();
    }
}

template<typename T>
VertexBondType SPVertex<T>::BondType() const
{
    size_t in_size = m_in.size();
    size_t out_size = m_out.size();

    if(in_size == 0 && out_size == 0){
        return VertexBondType::VertexNonCorrect;
    }

    if(in_size == 0){
        if(out_size == 1){
            return VertexBondType::VertexStartSingle;
        }
        else{
            return VertexBondType::VertexStartFull;
        }
    }

    if(out_size == 0){
        if(in_size == 1){
            return VertexBondType::VertexEndSingle;
        }
        else{
            return VertexBondType::VertexEndFull;
        }
    }

    if(in_size == 1 && out_size == 1){
        return VertexBondType::VertexMidSingle;
    }

    if(in_size > 1 && out_size == 1){
        return VertexBondType::VertexMidLeft;
    }

    if(in_size == 1 && out_size > 1){
        return VertexBondType::VertexMidRight;
    }

    if(in_size > 1 && out_size > 1){
        return VertexBondType::VertexMidFull;
    }

    return VertexBondType::VertexNonCorrect;
}

template<typename T>
SPVertex<T>::~SPVertex()
{
    m_out.clear();
    m_in.clear();
}

template<typename I>
std::ostream& operator <<(std::ostream &os, const SPVertex<I>* vertex)
{
    os << vertex->m_data;
    return os;
}

template<typename O>
std::istream& operator >>(std::istream &is, SPVertex<O>* vertex)
{
    return is;
}

}

#endif // SPVERTEX_H
