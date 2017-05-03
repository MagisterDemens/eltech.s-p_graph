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

}

#endif // SPGRAPHALLOCATOR_H
