#ifndef SPGRAPH_H
#define SPGRAPH_H

#include"spvertex.h"
#include"spgraphallocator.h"
#include"spgraphiterator.h"
#include"spmanipulator.h"
#include"spgexception.h"

#include<list>
#include<algorithm>
#include<iterator>
#include<sstream>
#include<iostream>
#include<QDebug>
#include<stdio.h>

namespace spg {

template<typename T>
class SPGraph
{

    //friend class SPGraphManipulator<T>;

    std::list<SPVertex<T>*> vertex_list;

    SPGraphAllocator<T> allocator;


    void createVertex(T data);
    void deleteVertexWithoutMerge(SPVertex<T>* vertex);
    void deleteVertexWithMerge(SPVertex<T>* vertex);
    void insertVertex(SPVertex<T>* old_v, SPVertex<T>* new_v, bool after = false);
    void connectVertexes(SPVertex<T>* v1, SPVertex<T>* v2);
public:
    SPGraph();
    SPGraph(T data);
    SPGraph(T in_data, T out_data);

    SPVertex<T>* SSPlit(SPVertex<T>* vertex, T data, bool after = false);
    SPVertex<T>* PSPlit(SPVertex<T>* vertex, T data);
    void deleteVertex(SPVertex<T> *vertex);

    SPGraphIterator<T> begin();
    SPGraphIterator<T> end();

    size_t size() const;
    unsigned int position(SPVertex<T>* vertex) const;
    SPVertex<T>* at(unsigned int pos) const;

    std::vector<unsigned int> getVertexDestination(SPVertex<T>* vertex, bool out = false) const;

    const char* SPGStruct() const;

    void clear();

    bool checkInvariant();

    template<typename O>
    friend std::ostream& operator << (std::ostream& os, const SPGraph<O>& graph);
    template<typename I>
    friend std::istream& operator >> (std::istream& is, SPGraph<I>& graph);

    ~SPGraph();
};

template<typename T>
SPGraph<T>::SPGraph()
{

}

template<typename T>
void SPGraph<T>::createVertex(T data)
{
    SPVertex<T>* vertex = allocator.newVertex(data);
    vertex_list.push_back(vertex);
}


template<typename T>
void SPGraph<T>::deleteVertexWithoutMerge(SPVertex<T> *vertex)
{
    if(vertex == NULL){
        THROW_SPG_NULL_POINTER_EXCEPTION(this,"NULL pointer",T);
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
        THROW_SPG_NULL_POINTER_EXCEPTION(this,"NULL pointer",T);
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
        /*new_v->addBondVertex(old_v, false);
        old_v->addBondVertex(new_v, true);*/
        connectVertexes(old_v, new_v);
        for(auto i = new_v->m_out.begin(); i != new_v->m_out.end(); i++){
            SPVertex<T>* temp = *i;
            temp->deleteBondVertex(old_v, false);
            temp->addBondVertex(new_v, false);
        }
    }
    else{
        new_v->setBond(old_v->m_in, false);
        old_v->clearBond(false);
        /*new_v->addBondVertex(old_v, true);
        old_v->addBondVertex(new_v, false);*/
        connectVertexes(new_v, old_v);
        for(auto i = new_v->m_in.begin(); i != new_v->m_in.end(); i++){
            SPVertex<T>* temp = *i;
            temp->deleteBondVertex(old_v, true);
            temp->addBondVertex(new_v, true);
        }
    }

}

template<typename T>
void SPGraph<T>::connectVertexes(SPVertex<T> *v1, SPVertex<T> *v2)
{
    v1->addBondVertex(v2, true);
    v2->addBondVertex(v1);
}

template<typename T>
SPGraph<T>::SPGraph(T data)
{
    SPVertex<T>* in_v = allocator.newVertex(data);
    SPVertex<T>* out_v = allocator.newVertex(data);

    vertex_list.push_back(in_v);
    vertex_list.push_back(out_v);

    connectVertexes(in_v, out_v);
}

template<typename T>
SPGraph<T>::SPGraph(T in_data, T out_data)
{
    SPVertex<T>* in_v = allocator.newVertex(in_data);
    SPVertex<T>* out_v = allocator.newVertex(out_data);

    vertex_list.push_back(in_v);
    vertex_list.push_back(out_v);

    connectVertexes(in_v, out_v);
}

template<typename T>
SPVertex<T> *SPGraph<T>::SSPlit(SPVertex<T> *vertex, T data, bool after)
{
    if(vertex == NULL){
        THROW_SPG_NULL_POINTER_EXCEPTION(this,"NULL pointer",T);
        return NULL;
    }

    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);

    if(pos == vertex_list.end()){
        THROW_SPG_NON_EXISTENT_VERTEX_EXCEPTION(this,"Vertex is not exist in the graph",T);
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
        THROW_SPG_NULL_POINTER_EXCEPTION(this,"Point on NULL",T);
        return NULL;
    }

    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);

    if(pos == vertex_list.end()){
        THROW_SPG_NON_EXISTENT_VERTEX_EXCEPTION(this,"Vertex is not exist in the graph",T);
        return NULL;
    }

    if(vertex->BondType() != VertexBondType::VertexMidSingle){
        THROW_SPG_INCORRECT_OPERATION_EXCEPTION(this, vertex,"Parallel adding","Cannot add parallel connection to vertex without VertexMidSingle bond type",T);
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
        THROW_SPG_NULL_POINTER_EXCEPTION(this,"Point on NULL",T);
        return;
    }

    if(vertex_list.size() == 2){
        THROW_SPG_INCORRECT_OPERATION_EXCEPTION(this, vertex,"Deleting","Cannot delete from graph with size = 2",T);
        return;
    }

    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);

    if(pos == vertex_list.end()){
        THROW_SPG_NON_EXISTENT_VERTEX_EXCEPTION(this,"Vertex is not exist in the graph",T);
        return;
    }

    VertexBondType type = vertex->BondType();

    switch (type) {
    case VertexBondType::VertexEndFull:
    case VertexBondType::VertexMidFull:
    case VertexBondType::VertexStartFull:
    case VertexBondType::VertexNonCorrect:
        THROW_SPG_INCORRECT_OPERATION_EXCEPTION(this, vertex,"Deleting","Vertex bond type does not allow to delete it",T);
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

        if(temp1->bondCount(true) > 1 && temp2->bondCount(false) > 1){
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
    return SPGraphIterator<T>(0, &vertex_list);
}

template<typename T>
SPGraphIterator<T> SPGraph<T>::end()
{
    return SPGraphIterator<T>(vertex_list.size(), &vertex_list);
}

template<typename T>
size_t SPGraph<T>::size() const
{
    return vertex_list.size();
}

template<typename T>
unsigned int SPGraph<T>::position(SPVertex<T> *vertex) const
{
    unsigned int pos = 0;

    for(auto i = vertex_list.begin(); i != vertex_list.end(); i++){
        if(*i == vertex){
            break;
        }
        pos++;
    }
    return pos;
}

template<typename T>
SPVertex<T> *SPGraph<T>::at(unsigned int pos) const
{
    if(pos >= vertex_list.size()){
        THROW_SPG_NULL_POINTER_EXCEPTION(this, "Null pointer (position out of graph)",T);
        return NULL;
    }

    auto i = vertex_list.begin();

    for(unsigned int j = 0; j < pos; j++){
        i++;
    }

    return *i;
}

template<typename T>
std::vector<unsigned int> SPGraph<T>::getVertexDestination(SPVertex<T> *vertex, bool out) const
{
    std::vector<unsigned int> destination;

    auto pos = std::find(vertex_list.begin(), vertex_list.end(), vertex);

    if(pos == vertex_list.end()){
        THROW_SPG_NULL_POINTER_EXCEPTION(this,"Null pointer",T);
        return destination;
    }

    std::list<SPVertex<T>*> temp;
    if(out)
    {
        temp = vertex->getBond(true);
    }
    else
    {
        temp = vertex->getBond();
    }
    for(auto i = temp.begin(); i != temp.end(); i++){
        destination.push_back(this->position(*i));
    }

    return destination;
}

template<typename T>
const char *SPGraph<T>::SPGStruct() const
{
    std::ostringstream oss;

    oss << this->size() << std::endl;

    for(auto i = vertex_list.begin(); i != vertex_list.end(); i++){
        SPVertex<T>* temp = *i;
        oss << temp->getData() << std::endl;
    }

    for(auto i = vertex_list.begin(); i != vertex_list.end(); i++){
        SPVertex<T>* temp = *i;
        oss << this->position(temp) << " " << temp->bondCount(true);
        std::vector<unsigned int> out = this->getVertexDestination(temp, true);
        for(auto j = out.begin(); j != out.end(); j++){
            oss << " " << *j;
        }
        oss << std::endl;
    }

    return oss.str().c_str();
}

template<typename T>
void SPGraph<T>::clear()
{
    allocator.freAll();
    vertex_list.clear();
}

template<typename T>
bool SPGraph<T>::checkInvariant()
{
    unsigned int out = 0;
    unsigned int in = 0;

    for(auto i = vertex_list.begin(); i != vertex_list.end(); i++){
        SPVertex<T>* temp = *i;
        if((*i) == NULL)
            return false;

        out += temp->bondCount(true);
        in += temp->bondCount(false);
    }

    if(out != in){
        return false;
    }

    return true;
}

template<typename T>
SPGraph<T>::~SPGraph()
{
    /*allocator.freAll();
    vertex_list.clear();*/
}

template<typename O>
std::ostream& operator <<(std::ostream &os, const SPGraph<O>& graph)
{
    os << SPGraphManipulator<O>(graph);
    return os;
}

template<typename I>
std::istream& operator >>(std::istream &is, SPGraph<I>& graph)
{
    graph.clear();
    //graph = new SPGraph<I>();
    unsigned int s;
    //qDebug() << "Read size\n";
    is >> s;
    //qDebug() << "hui" << s;
    for(unsigned int i = 0; i < s; i++){
        //qDebug() << "Data #" << i << "\n";
        I temp;
        is >> temp;
        graph.createVertex(temp);
    }

    for(unsigned int i = 0; i < s; i++){
        unsigned int n;
        unsigned int c;
        //qDebug() << "Connection #" << i << "\n";
        is >> n;
        //qDebug() << "Count #" << i << "\n";
        is >> c;
        for(unsigned int j = 0; j < c; j++){
            unsigned int d;
            //qDebug() << "Destination #" << j << "\n";
            is >> d;
            graph.connectVertexes(graph.at(n), graph.at(d));
        }
    }
    return is;
}

}

#endif // SPGRAPH_H
