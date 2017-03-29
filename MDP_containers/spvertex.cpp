#include "spvertex.h"

using namespace spg;

template<typename T>
SPVertex<T>::SPVertex(T &data)
{
    m_data = data;
}

template<typename T>
T SPVertex<T>::getData() const
{
    return m_data;
}

template<typename T>
void SPVertex<T>::setData(const T &data)
{
    m_data = data;
}

template<typename T>
std::list<SPVertex<T> *> SPVertex<T>::getInputs() const
{
    return m_input;
}

template<typename T>
std::list<SPVertex<T> *> SPVertex<T>::getOutputs() const
{
    return m_output;
}

template<typename T>
void SPVertex<T>::addVertex(SPVertex<T> *vertex, bool is_input)
{
    if(vertex == NULL){
        //Need exeption here
        return;
    }

    if(is_input){
        m_input.push_back(vertex);
    }
    else{
        m_output.push_back(vertex);
    }
}

template<typename T>
void SPVertex<T>::deleteVertex(SPVertex<T> *vertex, bool is_input)
{
    if(vertex == NULL){
        //Need exeption here
        return;
    }

    if(is_input){
        this->deleteV(vertex, m_input);
    }
    else{
        this->deleteV(vertex, m_output);
    }
}

template<typename T>
void SPVertex<T>::clearBonds(bool is_input)
{
    if(is_input){
        m_input.clear();
    }
    else{
        m_output.clear();
    }
}

template<typename T>
SPVertex<T>::~SPVertex()
{
    m_input.clear();
    m_output.clear();
}

template<typename T>
void SPVertex<T>::deleteV(SPVertex<T> *vertex, std::list<SPVertex<T> *> m_list)
{
    int pos = std::find(m_list.begin(), m_list.end(), vertex);
    if(pos == m_list.end()){
        //Need exeption here
        return;
    }
    m_list.erase(pos);
}
