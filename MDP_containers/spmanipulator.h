#ifndef SPMANIPULATOR_H
#define SPMANIPULATOR_H

#include<iostream>

#include"spgraph.h"
#include"spvertex.h"

namespace spg {

template<typename T> class SPGraph;
template<typename T> class SPVertex;

template<typename T>
class SPGraphManipulator
{

public:
    SPGraph<T>* m_graph;

    SPGraphManipulator(SPGraph<T>* graph){m_graph = graph;}

    template<typename O>
    friend std::ostream &operator << (std::ostream& os, const SPGraphManipulator<T>& graph_manip);
};

template<typename T>
std::ostream& operator<<(std::ostream &os, const SPGraphManipulator<T> &graph_manip)
{
    size_t size = graph_manip.m_graph->size();
    os << "Vertex count: " << size << std::endl;
    auto it = graph_manip.m_graph->begin();
    for(unsigned int j = 0; j < size; j++){
        os << graph_manip.m_graph->position(*it) << ":\t" << *it << ";\tGoes to: ";
        SPVertex<T>* temp = *it;
        std::list<SPVertex<T>*> temp_list = temp->getBond(true);
        for(auto i = temp_list.begin(); i != temp_list.end(); i++){
            os << graph_manip.m_graph->position(*i) << " ";
        }
        os << std::endl;
        ++it;
    }
    return os;
}

/*
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
        if(vertex_manip.m_vertex == NULL)
        {
            return os;
        }

        os << vertex_manip.m_vertex->m_data;

        return os;
    }
};
*/

}

#endif // SPMANIPULATOR_H
