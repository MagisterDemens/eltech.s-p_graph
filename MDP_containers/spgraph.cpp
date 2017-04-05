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
    SPVertex* new_vertex = new SPVertex(data);

    int pos = std::find(vertexes.begin(), vertexes.end(), vertex);

    if(pos == vertexes.size()){
        //exeption
        return;
    }

    std::list<SPVertex<T>*> temp_output = vertex->getOutputs();
    vertex->clearBonds();
    vertex->addVertex(vertex);

    vertexes.insert(pos, new_vertex);

    new_vertex->addVertex(vertex, true);

    for(int i = 0; i < temp_output.size(); i++){
        new_vertex->addVertex(temp_output[i]);
    }

}

template<typename T>
void SPGraph<T>::PSPlit(SPVertex<T> *vertex, T &data)
{
    SPVertex* new_vertex = new SPVertex(data);

    int pos = std::find(vertexes.begin(), vertexes.end(), vertex);

    if(pos == vertexes.size()){
        //exeption
        return;
    }

    std::list<SPVertex<T>*> temp_output = vertex->getOutputs();
    std::list<SPVertex<T>*> temp_input = vertex->getInputs();

    vertexes.insert(pos, new_vertex);

    for(int i = 0; i < temp_output.size(); i++){
        new_vertex->addVertex(temp_output[i]);
    }

    for(int i = 0; i < temp_input.size(); i++){
        new_vertex->addVertex(temp_input, true);
    }
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
