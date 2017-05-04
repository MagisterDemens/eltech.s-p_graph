#include "spgraph.h"

namespace spg {

template<typename T>
SPGraph<T>::SPGraph()
{

}

template<typename T>
SPGraph<T>::SPGraph(T data)
{
    SPVertex<T>* in_v = this->addVertex(data);
    SPVertex<T>* out_v = this->addVertex(data);
    this->addBond(in_v, out_v);
}

template<typename T>
SPGraph<T>::SPGraph(T in_data, T out_data)
{
    SPVertex<T>* in_v = this->addVertex(in_data);
    SPVertex<T>* out_v = this->addVertex(out_data);
    this->addBond(in_v, out_v);
}

template<typename T>
SPVertex<T> *SPGraph<T>::SSPlit(SPVertex<T> *vertex, T data, bool before)
{
    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);
    if(pos == vertex_list.end()){
        //exception
        return NULL;
    }

    SPVertex<T>* new_v = this->addVertex(data);
    if(before){
        new_v->setBonds(vertex->getBonds(true));
        vertex->clearBonds(true);
        vertex->addBondVertex(new_v, true);
    }
    else{
        new_v->setBonds(vertex->getBonds(), true);
        vertex->clearBonds();
        vertex->addBondVertex(new_v);
    }

    return new_v;
}

template<typename T>
SPVertex<T> *SPGraph<T>::PSPlit(SPVertex<T> *vertex, T data)
{
    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);
    if(pos == vertex_list.end()){
        //exception
        return NULL;
    }

    if(vertex->countBonds() != 1 && vertex->countBonds(true) != 1){
        //exception
        return NULL;
    }

    SPVertex<T>* new_v = this->addVertex(data);
    SPVertex<T>* in_v = vertex->getBonds(true).front();
    SPVertex<T>* out_v = vertex->getBonds().front();
    new_v->addBondVertex(in_v, true);
    new_v->addBondVertex(out_v);
    in_v->addBondVertex(new_v);
    out_v->addBondVertex(new_v, true);

    return new_v;
}

template<typename T>
void SPGraph<T>::deleteVertex(SPVertex<T> *vertex)
{

}

template<typename T>
void SPGraph<T>::clearGraph()
{
    vertex_list.clear();
}

template<typename T>
SPGraphIterator<T> SPGraph<T>::begin()
{
    return SPGraphIterator<T>(0, vertex_list);
}

template<typename T>
SPGraphIterator<T> SPGraph<T>::end()
{
    return SPGraphIterator<T>(vertex_list.size(), vertex_list);
}

template<typename T>
SPGraph<T>::~SPGraph()
{
    vertex_list.clear();
    allocator.freAll();
}

template<typename T>
SPVertex<T> *SPGraph<T>::addVertex(T data)
{
    SPVertex<T>* v = allocator.newVertex(data);
    return v;
}

template<typename T>
void SPGraph<T>::addBond(SPVertex<T> *in_v, SPVertex<T> *out_v)
{
    in_v->addBondVertex(out_v, true);
    out_v->addBondVertex(in_v);
}

}
