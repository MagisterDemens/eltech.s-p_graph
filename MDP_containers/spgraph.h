#ifndef SPGRAPH_H
#define SPGRAPH_H

#include"spvertex.h"
#include"spgraphallocator.h"
#include"spgraphiterator.h"

#include<list>
#include<algorithm>
#include<iterator>

namespace spg {

template<typename T> class SPGraphManupulator;

template<typename T>
class SPGraph
{
    friend class SPGraphManupulator<T>;

    std::list<SPVertex<T>*> vertex_list;

    SPGraphAllocator<T> allocator;

    SPGraph();
    //SPVertex<T>* createVertex(std::iterator pos, T data);
    void deleteVertexWithoutMerge(SPVertex<T>* vertex);
    void deleteVertexWithMerge(SPVertex<T>* vertex);
    void insertVertex(SPVertex<T>* old_v, SPVertex<T>* new_v, bool after = false);
public:
    SPGraph(T data);
    SPGraph(T in_data, T out_data);

    SPVertex<T>* SSPlit(SPVertex<T>* vertex, T data, bool after = false);
    SPVertex<T>* PSPlit(SPVertex<T>* vertex, T data);
    void deleteVertex(SPVertex<T> *vertex);

    SPGraphIterator<T> begin();
    SPGraphIterator<T> end();

    template<typename O>
    friend std::ostream& operator << (std::ostream& os, SPGraph<O> graph);
    template<typename I>
    friend std::istream& operator >> (std::ostream& is, SPGraph<I> graph);

    ~SPGraph();
};

template<typename T>
SPGraph<T>::SPGraph()
{

}

/*template<typename T>
SPVertex<T> *SPGraph<T>::createVertex(std::iterator pos, T data)
{
    SPVertex<T> vertex = allocator.newVertex(data);]
    vertex_list.insert(pos, vertex);
}*/

template<typename T>
void SPGraph<T>::deleteVertexWithoutMerge(SPVertex<T> *vertex)
{
    if(vertex == NULL){
        //exception
        return;
    }

    std::list<SPVertex<T>*> in_list = vertex->m_in;
    std::list<SPVertex<T>*> out_list = vertex->m_out;

    for(auto i = in_list.begin(); i != in_list.end(); i++){
        SPVertex<T>* temp = *i;
        temp->deleteBondVertex(vertex, true);
    }

    for(auto i = out_list.begin(); i != out_list.end(); i++){
        SPVertex<T>* temp = *i;
        temp->deleteBondVertex(vertex);
    }

    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);
    vertex_list.erase(pos);
    allocator.freeVertex(vertex);
}

template<typename T>
void SPGraph<T>::deleteVertexWithMerge(SPVertex<T> *vertex)
{
    if(vertex == NULL){
        //exception
        return;
    }

    std::list<SPVertex<T>*> in_list = vertex->m_in;
    std::list<SPVertex<T>*> out_list = vertex->m_out;

    for(auto i = in_list.begin(); i != in_list.end(); i++){
        SPVertex<T>* temp = *i;
        temp->deleteBondVertex(vertex, true);
    }

    for(auto i = out_list.begin(); i != out_list.end(); i++){
        SPVertex<T>* temp = *i;
        temp->deleteBondVertex(vertex);
    }

    for(auto i = in_list.begin(); i != in_list.end(); i++){
        SPVertex<T>* temp1 = *i;
        for(auto j = out_list.begin(); j != out_list.end(); i++){
            SPVertex<T>* temp2 = *j;
            temp1->addBondVertex(temp2, true);
            temp2->addBondVertex(temp1);
        }
    }

    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);
    vertex_list.erase(pos);
    allocator.freeVertex(vertex);
}

template<typename T>
void SPGraph<T>::insertVertex(SPVertex<T> *old_v, SPVertex<T> *new_v, bool after)
{
    if(after){
        new_v->setBond(old_v->m_out, true);
        old_v->clearBond(true);
        new_v->addBondVertex(old_v, false);
        old_v->addBondVertex(new_v, true);
        for(auto i = new_v->m_out.begin(); i != new_v->m_out.end(); i++){
            SPVertex<T>* temp = *i;
            temp->deleteBondVertex(old_v, false);
            temp->addBondVertex(new_v, false);
        }
    }
    else{
        new_v->setBond(old_v->m_in, false);
        old_v->clearBond(false);
        new_v->addBondVertex(old_v, true);
        old_v->addBondVertex(new_v, false);
        for(auto i = new_v->m_in.begin(); i != new_v->m_in.end(); i++){
            SPVertex<T>* temp = *i;
            temp->deleteBondVertex(old_v, true);
            temp->addBondVertex(new_v, true);
        }
    }

}

template<typename T>
SPGraph<T>::SPGraph(T data)
{
    SPVertex<T> in_v = allocator.newVertex(data);
    SPVertex<T> out_v = allocator.newVertex(data);

    vertex_list.push_back(in_v);
    vertex_list.push_back(out_v);

    in_v.addBondVertex(out_v, true);
    out_v.addBondVertex(in_v);
}

template<typename T>
SPGraph<T>::SPGraph(T in_data, T out_data)
{
    SPVertex<T>* in_v = allocator.newVertex(in_data);
    SPVertex<T>* out_v = allocator.newVertex(out_data);

    vertex_list.push_back(in_v);
    vertex_list.push_back(out_v);

    in_v->addBondVertex(out_v, true);
    out_v->addBondVertex(in_v);
}

template<typename T>
SPVertex<T> *SPGraph<T>::SSPlit(SPVertex<T> *vertex, T data, bool after)
{
    if(vertex == NULL){
        //exception
        return NULL;
    }

    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);

    if(pos == vertex_list.end()){
        //exeption
        return NULL;
    }

    SPVertex<T>* new_v = allocator.newVertex(data);

    if(after){
        pos++;
    }

    vertex_list.insert(pos, new_v);
    insertVertex(vertex, new_v, after);

    return new_v;
}

template<typename T>
SPVertex<T> *SPGraph<T>::PSPlit(SPVertex<T> *vertex, T data)
{
    if(vertex == NULL){
        //exception
        return NULL;
    }

    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);

    if(pos == vertex_list.end()){
        //exeption
        return NULL;
    }

    if(vertex->BondType() != VertexBondType::VertexMidSingle){
        //exception
        return NULL;
    }

    SPVertex<T>* new_v = allocator.newVertex(data);

    new_v->setBond(vertex->m_in);
    new_v->setBond(vertex->m_out, true);

    for(auto i = new_v->m_in.begin(); i != new_v->m_in.end(); i++){
        SPVertex<T>* temp = *i;
        temp->addBondVertex(new_v, true);
    }

    for(auto i = new_v->m_out.begin(); i != new_v->m_out.end(); i++){
        SPVertex<T>* temp = *i;
        temp->addBondVertex(new_v);
    }

    vertex_list.insert(pos, new_v);
    return new_v;
}

template<typename T>
void SPGraph<T>::deleteVertex(SPVertex<T>* vertex)
{
    if(vertex == NULL){
        //exception
        return;
    }

    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);

    if(pos == vertex_list.end()){
        //exception
        return;
    }

    VertexBondType type = vertex->BondType();

    switch (type) {
    case VertexBondType::VertexEndFull:
    case VertexBondType::VertexMidFull:
    case VertexBondType::VertexStartFull:
    case VertexBondType::VertexNonCorrect:
        //exception
        break;
    case VertexBondType::VertexEndSingle:
    case VertexBondType::VertexStartSingle:
    case VertexBondType::VertexMidLeft:
    case VertexBondType::VertexMidRight:
        deleteVertexWithMerge(vertex);
        break;
    case VertexBondType::VertexMidSingle:
        SPVertex<T>* temp1 = vertex->m_in.front();
        SPVertex<T>* temp2 = vertex->m_out.front();

        if(temp1->bondCound(true) > 1 && temp2->bondCound(false) > 1){
            deleteVertexWithoutMerge(vertex);
        }
        else{
            deleteVertexWithMerge(vertex);
        }
        break;
    }
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
    allocator.freAll();
}

template<typename O>
std::ostream& operator <<(std::ostream &os, SPGraph<O> graph)
{
    return os;
}

template<typename I>
std::istream& operator >>(std::ostream &is, SPGraph<I> graph)
{
    return is;
}


}

#endif // SPGRAPH_H
