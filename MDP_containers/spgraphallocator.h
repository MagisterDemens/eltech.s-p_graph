#ifndef SPGRAPHALLOCATOR_H
#define SPGRAPHALLOCATOR_H

#include"spvertex.h"
#include<list>
#include<algorithm>

namespace spg {

template<typename T>
class SPGraphAllocator
{
    std::list<SPVertex<T>*> vertex_mem;
public:
    SPGraphAllocator(){}

    SPVertex<T>* newVertex(T data);
    void freeVertex(SPVertex<T>* vertex);
    void freAll();
};

template<typename T> inline
SPVertex<T> *SPGraphAllocator<T>::newVertex(T data)
{
    return new SPVertex<T>(data);
}

template<typename T>
void SPGraphAllocator<T>::freeVertex(SPVertex<T> *vertex)
{
    auto pos = std::find(vertex_mem.begin(), vertex_mem.end(), vertex);
    if(pos == vertex_mem.end()){
        //exception
        return;
    }
    vertex_mem.erase(pos);
    delete vertex;
}

template<typename T>
void SPGraphAllocator<T>::freAll()
{
    for(auto i = vertex_mem.begin(); i != vertex_mem.end(); i++){
        SPVertex<T>* temp = *i;
        delete temp;
    }
    vertex_mem.clear();
}

}

#endif // SPGRAPHALLOCATOR_H
