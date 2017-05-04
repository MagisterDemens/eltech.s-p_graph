#include "spgraphallocator.h"

namespace spg {

template<typename T>
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
    std::for_each(vertex_mem.begin(), vertex_mem.end(), [](SPVertex<T>* v){delete v;});
    vertex_mem.clear();
}

}
