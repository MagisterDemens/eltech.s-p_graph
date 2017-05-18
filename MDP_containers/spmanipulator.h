#ifndef SPMANIPULATOR_H
#define SPMANIPULATOR_H

#include<iostream>

#include"spgraph.h"
//#include"spvertex.h"

namespace spg {

template<typename T>
class SPGraphManipulator
{
    SPGraph<T> m_graph;
public:
    SPGraphManipulator(SPGraph<T> &graph)
    {
        m_graph = graph;
    }

    template<typename O>
    friend std::ostream &operator<< (std::ostream& os, const SPGraphManipulator<O>& graph_manip)
    {
        return os;
    }
};

template<typename T>
class SPVertexManipulator{
    SPVertex<T>* m_vertex;
public:
    SPVertexManipulator(SPVertex<T>* vertex)
    {
        m_vertex = vertex;
    }

    template<typename O>
    friend std::ostream &operator<< (std::ostream& os, const SPVertexManipulator<O>& vertex_manip)
    {
        return os;
    }
};


}

#endif // SPMANIPULATOR_H
