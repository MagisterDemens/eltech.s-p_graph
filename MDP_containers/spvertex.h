#ifndef SPVERTEX_H
#define SPVERTEX_H

#include<list>
#include<algorithm>

namespace spg {

template<typename T>
class SPVertex
{

public:
    SPVertex(T& data);
    T getData() const;
    void setData(const T &data);
    std::list<SPVertex<T>*> getInputs() const;
    std::list<SPVertex<T>*> getOutputs() const;
    void addVertex(SPVertex<T>* vertex, bool is_input = false);
    void addVertex(std::list<SPVertex<T>*> vertex, bool is_input = false);
    void deleteVertex(SPVertex<T>* vertex, bool is_input = false);
    void clearBonds(bool is_input = false);
    int count(bool is_input);
    ~SPVertex();
private:
    void deleteV(SPVertex<T>* vertex ,std::list<SPVertex<T>*> m_list);
    void addV(SPVertex<T>* vertex ,std::list<SPVertex<T>*> m_list);

    T m_data;
    std::list<SPVertex<T>*> m_input;
    std::list<SPVertex<T>*> m_output;
};

}


#endif // SPVERTEX_H
