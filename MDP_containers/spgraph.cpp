#include "spgraph.h"

using namespace spg;

template<typename T>
SPGraph<T>::SPGraph(T &data)
{
    SPVertex<T>* first = new SPVertex<T>(data);
    SPVertex<T>* last = new SPVertex<T>(data);
    first->addVertex(last);
    last->addVertex(first, true);
    vertexes.push_back(first);
    vertexes.push_back(last);
}

template<typename T>
SPGraph<T>::SPGraph(T &firstData, T &lastData)
{
    SPVertex<T>* first = new SPVertex<T>(firstData);
    SPVertex<T>* last = new SPVertex<T>(lastData);
    first->addVertex(last);
    last->addVertex(first, true);
    vertexes.push_back(first);
    vertexes.push_back(last);
}

template<typename T>
void SPGraph<T>::SSPlit(SPVertex<T> *vertex, T &data)
{

}

template<typename T>
void SPGraph<T>::PSPlit(SPVertex<T> *vertex, T &data)
{

}

template<typename T>
void SPGraph<T>::deleteVertex(SPVertex<T> *vertex)
{

}

template<typename T>
SPGraph<T>::~SPGraph()
{
    vertexes.clear();
}
