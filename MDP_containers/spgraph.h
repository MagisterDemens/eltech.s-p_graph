#ifndef SPGRAPH_H
#define SPGRAPH_H

#include"spvertex.h"
#include"spgraphallocator.h"
#include"spgraphiterator.h"

#include<list>
#include<algorithm>

namespace spg {

template<typename T> class SPGraphManupulator;

template<typename T>
class SPGraph
{
    friend class SPGraphManupulator<T>;

    std::list<SPVertex<T>*> vertex_list;

    SPGraphAllocator<T> allocator;

    SPGraph();
public:
    SPGraph(T data);
    SPGraph(T in_data, T out_data);

    SPVertex<T>* SSPlit(SPVertex<T>* vertex, T data, bool before = false);
    SPVertex<T>* PSPlit(SPVertex<T>* vertex, T data);

    void deleteVertex(SPVertex<T>* vertex);
    void clearGraph();

    SPGraphIterator<T> begin();
    SPGraphIterator<T> end();

    template<typename R>
    friend std::ostream& operator<<(std::ostream& os,const SPGraph<R> &spgraph);

    template<typename R>
    friend std::istream& operator>>(std::istream& is, SPGraph<R> &spgraph);

    ~SPGraph();

protected:
    SPVertex<T>* addVertex(T data);
    void addBond(SPVertex<T>* in_v, SPVertex<T>* out_v);
};

}

#endif // SPGRAPH_H
