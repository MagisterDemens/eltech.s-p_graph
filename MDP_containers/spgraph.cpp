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
std::list<SPVertex<T> *> SPGraph<T>::SSPlit(SPVertex<T>* vertex, T &data)
{
    int pos = std::find(vertexes.begin(), vertexes.end(), vertex);

    if(pos == vertexes.end()){
        //exeption
        return NULL;
    }

    SPVertex<T>* new_vertex = new SPVertex<T>(data);

    std::list<SPVertex<T>*> temp_output = vertex->getOutputs();
    vertex->clearBonds();
    vertex->addVertex(vertex);

    new_vertex->addVertex(vertex, true);
    new_vertex->addVertex(temp_output);
    /*
    for(int i = 0; i < temp_output.size(); i++){
        new_vertex->addVertex(temp_output[i]);
    }
    */
    pos++;
    vertexes.insert(pos, new_vertex);

    return new_vertex;
}

template<typename T>
std::list<SPVertex<T> *> SPGraph<T>::PSPlit(SPVertex<T>* vertex, T &data)
{
    int pos = std::find(vertexes.begin(), vertexes.end(), vertex);

    if(pos == vertexes.end()){
        //exeption
        return NULL;
    }

    if(pos == vertexes.begin() || pos == vertexes.end()--){
        //exeption
        return NULL;
    }

    if(vertex->count() != 1 && vertex->count(true) != 1){
       //exeption
       return NULL;
    }

    SPVertex<T>* new_vertex = new SPVertex<T>(data);

    std::list<SPVertex<T>*> temp_output = vertex->getOutputs();
    std::list<SPVertex<T>*> temp_input = vertex->getInputs();
    new_vertex->addVertex(temp_output);
    new_vertex->addVertex(temp_input, true);
    /*
    for(int i = 0; i < temp_output.size(); i++){
        new_vertex->addVertex(temp_output[i]);
    }

    for(int i = 0; i < temp_input.size(); i++){
        new_vertex->addVertex(temp_input[i], true);
    }
    */
    pos++;
    vertexes.insert(pos, new_vertex);

    return new_vertex;
}

template<typename T>
void SPGraph<T>::deleteVertex(SPVertex<T>* vertex)
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

    if(pos == vertexes.begin()){
        if(vertex->count(false) == 1){
            std::list<SPVertex<T>*> temp = vertex->getOutputs();
            for(int i = 0; i < temp.size(); i++){
               SPVertex<T>* vt = temp[i];
               vt->deleteVertex(vertex);
               vertex->clearBonds();
               vertexes.erase(pos);
               delete vertex;
            }
        }
        else{
            //exeption
            return;
        }
    }

    if(pos == vertexes.end()--){
        if(vertex->count(true) == 1){
            std::list<SPVertex<T>*> temp = vertex->getInputs();
            for(int i = 0; i < temp.size(); i++){
                SPVertex<T>* vt = temp[i];
                vt->deleteVertex(vertex, true);
                vertex->clearBonds(true);
                vertexes.erase(pos);
                delete vertex;
            }
        }
        else{
            //exeption
            return;
        }
    }

    if(vertex->count(true) > 1 && vertex->count(false) > 1){
        //exeption
        return;
    }

    if(vertex->count(true) == 1 && vertex->count(false) == 1){
        std::list<SPVertex<T>*> temp_input = vertex->getInputs();
        std::list<SPVertex<T>*> temp_output = vertex->getOutputs();

        bool input_flag = false;
        bool output_flag = false;

        for(int i = 0; i < temp_input.size(); i++){
            SPVertex<T>* temp = temp_input[i];
            if(temp->count(false) > 1){
                input_flag = true;
                break;
            }
        }

        for(int i = 0; i < temp_output.size(); i++){
            SPVertex<T>* temp = temp_output[i];
            if(temp->count(true) > 1){
                output_flag = true;
                break;
            }
        }

        if(input_flag && output_flag){
            vertex->clearBonds(true);
            vertex->clearBonds();
            vertexes.erase(pos);
            delete vertex;
            return;
        }
        else{
            for(int i = 0; i < temp_output.size(); i++){
                SPVertex<T>* temp = temp_output[i];
                temp->clearBonds(true);
            }

            for(int i = 0; i < temp_input.size(); i++){
                SPVertex<T>* temp = temp_input[i];
                temp->clearBonds();
                temp->addVertex(temp_output);
            }
            vertex->clearBonds();
            vertex->clearBonds(true);
            vertexes.erase(pos);
            delete vertex;
            return;
        }
    }

    if((vertex->count(true) == 1 && vertex->count(false) > 1) ||
        vertex->count(true) > 1 && vertex->count(false) == 1){

        std::list<SPVertex<T>*> temp_input = vertex->getInputs();
        std::list<SPVertex<T>*> temp_output = vertex->getOutputs();

        for(int i = 0; i < temp_output.size(); i++){
            SPVertex<T>* temp = temp_output[i];
            temp->clearBonds(true);
            temp->addVertex(temp_input, true);
        }

        for(int i = 0; i < temp_input.size(); i++){
            SPVertex<T>* temp = temp_input[i];
            temp->clearBonds();
            temp->addVertex(temp_output);
        }

        vertexes.erase(pos);
        delete vertex;
        return;
    }
}

template<typename T>
SPGraph<T>::~SPGraph()
{
    vertexes.clear();
}

template<typename T>
SPGraph<T>::SPGraphIterator::SPGraphIterator(const size_t pos, std::list<SPVertex<T>*> list)
{
    m_pos = pos;
    m_list = list;
    m_iterator = list.begin();
    for(int i = 0; i < m_pos; i++) m_iterator++;
}

template<typename T>
typename SPGraph<T>::SPGraphIterator &SPGraph<T>::SPGraphIterator::operator ++()
{
    if(m_list.size() < m_pos+1){
        //exeption
        return *this;
    }
    m_pos++;
    m_iterator++;
    return *this;
}

template<typename T>
typename SPGraph<T>::SPGraphIterator &SPGraph<T>::SPGraphIterator::operator --()
{
    if(0 > m_pos-1){
        //exeption
        return *this;
    }
    m_pos--;
    m_iterator--;
    return *this;
}

template<typename T>
bool SPGraph<T>::SPGraphIterator::operator ==(const SPGraph<T>::SPGraphIterator &iterator)
{
    return (m_iterator == iterator.m_iterator);
}
template<typename T>
bool SPGraph<T>::SPGraphIterator::operator !=(const SPGraph<T>::SPGraphIterator &iterator)
{
    return (m_iterator != iterator.m_iterator);
}

template<typename T>
SPVertex<T> *SPGraph<T>::SPGraphIterator::operator *()
{
    if(m_pos == m_list.size()){
        //exeption
        return NULL;
    }

    return *m_iterator;
}
