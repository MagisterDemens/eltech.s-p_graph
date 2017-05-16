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

    template<typename T>
    friend std::ostream &operator<< (std::ostream& os, const SPGraphManipulator<T>& graph_manip);
};

template<typename T>
class SPVertexManipulator{
    SPVertex<T>* m_vertex;
public:
    SPVertexManipulator(SPVertex<T>* vertex);

    template<typename T>
    friend std::ostream &operator<< (std::ostream& os, const SPVertexManipulator<T>& vertex_manip);
};

template<typename T>
SPGraphManipulator::SPGraphManipulator(SPGraph<spg::T> &graph)
{
    m_graph = graph;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const SPGraphManipulator<T> &graph_manip)
{
    return os;
}

template<typename T>
SPVertexManipulator<T>::SPVertexManipulator(SPVertex<T> *vertex)
{
    m_vertex = vertex;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const SPVertexManipulator<T> &vertex_manip)
{
    return os;
}

}

#endif // SPMANIPULATOR_H
