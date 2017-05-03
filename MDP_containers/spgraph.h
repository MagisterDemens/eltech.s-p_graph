#ifndef SPGRAPH_H
#define SPGRAPH_H

#include<list>
#include<algorithm>
#include"spvertex.h"

namespace spg {

template<typename T>
class SPGraph
{

public:
    SPGraph(T &data);
    SPGraph(T &firstData, T &lastData);
    std::list<SPVertex<T>*> SSPlit(SPVertex<T>* vertex, T &data);
    std::list<SPVertex<T>*> PSPlit(SPVertex<T>* vertex, T &data);
    void deleteVertex(SPVertex<T>* vertex);
    ~SPGraph();

    //итератор
    class SPGraphIterator
    {
        //typename std::list<SPVertex<T>*>::iterator vertex_iterator;

    public:
        SPGraphIterator(const size_t pos, std::list<SPVertex<T>*> list);
        SPGraphIterator& operator ++ ();
        SPGraphIterator& operator -- ();
        bool operator == (const SPGraphIterator &iterator);
        bool operator != (const SPGraphIterator &iterator);
        SPVertex<T>* operator * ();
    private:
        size_t m_pos;
        std::list<SPVertex<T>*> m_list;
        typename std::list<SPVertex<T>*>::iterator m_iterator;
    };

private:
    std::list<SPVertex<T>*> vertexes;
};

}



#endif // SPGRAPH_H
