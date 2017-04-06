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
SPVertex<T>* SPGraph<T>::SSPlit(SPVertex<T> *vertex, T &data)
{
    SPVertex<T>* new_vertex = new SPVertex<T>(data);

    int pos = std::find(vertexes.begin(), vertexes.end(), vertex);

    if(pos == vertexes.end()){
        //exeption
        return NULL;
    }

    std::list<SPVertex<T>*> temp_output = vertex->getOutputs();
    vertex->clearBonds();
    vertex->addVertex(vertex);

    pos--;
    vertexes.insert(pos, new_vertex);

    new_vertex->addVertex(vertex, true);

    for(int i = 0; i < temp_output.size(); i++){
        new_vertex->addVertex(temp_output[i]);
    }

    return new_vertex;
}

template<typename T>
SPVertex<T> *SPGraph<T>::PSPlit(SPVertex<T> *vertex, T &data)
{
    SPVertex<T>* new_vertex = new SPVertex<T>(data);

    int pos = std::find(vertexes.begin(), vertexes.end(), vertex);

    if(pos == vertexes.end()){
        //exeption
        return NULL;
    }

    if(pos == vertexes.begin() || pos == vertexes.end()--){
        //exeption
        return NULL;
    }

    std::list<SPVertex<T>*> temp_output = vertex->getOutputs();
    std::list<SPVertex<T>*> temp_input = vertex->getInputs();

    pos--;
    vertexes.insert(pos, new_vertex);

    for(int i = 0; i < temp_output.size(); i++){
        new_vertex->addVertex(temp_output[i]);
    }

    for(int i = 0; i < temp_input.size(); i++){
        new_vertex->addVertex(temp_input[i], true);
    }

    return new_vertex;
}

template<typename T>
void SPGraph<T>::deleteVertex(SPVertex<T> *vertex)
{
    if(vertex == NULL){
        //exeption
        return;
    }

    int pos = std::find(vertexes.begin(), vertexes.end(), vertex);

    if(pos == vertexes.end()){
        //exeption
        return;
    }

    if(pos == vertexes.begin() || vertexes.end()--){
        //exeption
        return;
    }


}

template<typename T>
SPGraph<T>::~SPGraph()
{
    vertexes.clear();
}
