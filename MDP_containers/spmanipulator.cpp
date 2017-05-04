#include "spmanipulator.h"

namespace spg {

template<typename T>
SPGraphManipulator<T>::SPGraphManipulator(SPGraph<T> &graph)
{

}

template<typename T>
std::ostream& operator<<(std::ostream &os, const SPGraphManipulator<T> &graph_manip)
{
    return os;
}

template<typename T>
SPVertexManipulator<T>::SPVertexManipulator(SPVertex<T> *vertex)
{

}

template<typename T>
std::ostream& operator<<(std::ostream &os, const SPVertexManipulator<T> &vertex_manip)
{
    return os;
}


}
