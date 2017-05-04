#ifndef SPVERTEX_H
#define SPVERTEX_H

#include<list>
#include<algorithm>

//

namespace spg {

template<typename T> class SPGraph;
template<typename T> class SPVertexManipulator;

template<typename T>
class SPVertex
{
    friend class SPGraph<T>;
    friend class SPVertexManipulator<T>;

    T m_data;
    std::list<SPVertex<T>*> m_in;
    std::list<SPVertex<T>*> m_out;

    void setBonds(std::list<SPVertex<T>*> v_list, bool out = false);
    void addBondVertex(SPVertex<T>* vertex, bool out = false);
    void deleteBondVertex(SPVertex<T>* vertex, bool out = false);
    void clearBonds(bool out = false);
public:
    SPVertex(T data);

    unsigned int countBonds(bool out = false);
    const std::list<SPVertex<T>*> getBonds(bool out = false);
    void setData(T data);
    T getData();

    ~SPVertex();

    template<typename R>
    friend std::ostream& operator<<(std::ostream& os, const SPVertex<R>* spvertex);

    template<typename R>
    friend std::istream& operator>>(std::istream& is, SPGraph<R>* spvertex);
protected:

};

}

#endif // SPVERTEX_H
