#ifndef SPGRAPH_H
#define SPGRAPH_H

#include<list>
#include<algorithm>
#include"spvertex.h"

namespace spg {

template<typename T>
class SPGraph
{
    typedef std::list<SPVertex<T>*> v_list;
    typedef SPVertex<T>* v_elem;

public:
    SPGraph(T &data);
    SPGraph(T &firstData, T &lastData);
    SPVertex<T>* SSPlit(SPVertex<T>* vertex, T &data);
    SPVertex<T>* PSPlit(SPVertex<T>* vertex, T &data);
    void deleteVertex(SPVertex<T>* vertex);
    ~SPGraph();
private:
    std::list<SPVertex<T>*> vertexes;
};

}



#endif // SPGRAPH_H
