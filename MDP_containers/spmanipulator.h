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
    os << "Number of vertices: " << size << std::endl;
    auto it = graph_manip.m_graph->begin();
    for(unsigned int j = 0; j < size; j++){
        os << "#" << graph_manip.m_graph->position(*it) << "\tData: " << *it << "\n\tgoes to: ";
        SPVertex<T>* temp = *it;
        std::vector<unsigned int> temp_list = graph_manip.m_graph->getVertexDestination(temp);
        for(auto i = temp_list.begin(); i != temp_list.end(); i++){
            os << *i << " ";
        }
        os << std::endl << std::endl;
        ++it;
    }
    return os;
}

}

#endif // SPMANIPULATOR_H
