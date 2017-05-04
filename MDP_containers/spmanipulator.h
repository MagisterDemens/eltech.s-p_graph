#ifndef SPMANIPULATOR_H
#define SPMANIPULATOR_H

#include<iostream>

#include"spgraph.h"
#include"spvertex.h"

namespace spg {

template<typename T>
class SPGraphManipulator
{
    SPGraphManipulator<T> m_graph;
public:
    SPGraphManipulator(SPGraph<T> &graph);

    template<typename R>
    friend std::ostream &operator<< (std::ostream& os, const SPGraphManipulator<R>& graph_manip);
};


template<typename V>
class SPVertexManipulator{
    SPVertex<V>* m_vertex;
public:
    SPVertexManipulator(SPVertex<V>* vertex);

    template<typename W>
    friend std::ostream &operator<< (std::ostream& os, const SPVertexManipulator<W>& vertex_manip);
};

}

#endif // SPMANIPULATOR_H
