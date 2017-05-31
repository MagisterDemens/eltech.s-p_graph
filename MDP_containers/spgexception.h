#ifndef SPGEXCEPTION_H
#define SPGEXCEPTION_H

#include<string>
#include<exception>
#include<sstream>

/*#include"spgraph.h"
#include"spvertex.h"
#include"spgraphiterator.h"*/

namespace spg {

#define THROW_SPG_EXCEPTION(s) throw SPGException(s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_NULL_POINTER_EXCEPTION(g, s, T) throw SPGNullPointerException<T>(s , __LINE__, __FUNCTION__, __TIME__, g)
#define THROW_SPG_INCORRECT_OPERATION_EXCEPTION(g,v,op,s, T) throw SPGIncorrectOperationException<T>(g,v,op,s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_NON_EXISTENT_VERTEX_EXCEPTION(g,s, T) throw SPGNonExistentVertexEXception<T>(g,s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_ITERATOR_EXCEPTION(i,s, T) throw SPGIteratorException<T>(i,s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_ALLOCATOR_EXCEPTION(v,s, T) throw SPGAllocatorException<T>(v,s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_VERTEX_EXCEPTION(v,s, T) throw SPGVertexException<T>(v,s , __LINE__, __FUNCTION__, __TIME__)

class SPGException : public std::exception
{
public:
    SPGException():
        exception(),
        m_text(""),
        m_line(0),
        m_function(""),
        m_time("")
    {

    }
    SPGException(std::string text, int line, std::string function, std::string time):
        exception(),
        m_text(text),
        m_line(line),
        m_function(function),
        m_time(time)
    {

    }

    virtual const char* what() const throw()
    {
        std::ostringstream oss;
        oss << m_time << ": " <<  m_function << " in line " << m_line << " | " << m_text << std::endl;
        return oss.str().c_str();
    }

protected:
    std::string m_text;
    int m_line;
    std::string m_function;
    std::string m_time;
};

template<typename T> class SPGraph;
template<typename T> class SPVertex;
template<typename T> class SPGraphIterator;

template<typename T>
class SPGNullPointerException : public SPGException
{
    const SPGraph<T>* m_g;
public:
    SPGNullPointerException(std::string text, int line, std::string function, std::string time, const SPGraph<T>* g = NULL): SPGException(text, line, function, time){
        m_g = g;
    }

    const SPGraph<T>* getGraph(){return m_g;}
};

template<typename T>
class SPGIncorrectOperationException: public SPGException
{
    SPGraph<T>* m_g;
    SPVertex<T>* m_v;
    std::string m_op;
public:
    SPGIncorrectOperationException(SPGraph<T>* g, SPVertex<T>* v, std::string op ,std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){
        m_g = g;
        m_v = v;
        m_op = op;
    }

    SPGraph<T>* getGraph(){ return m_g;}
    SPVertex<T>* getVertex(){ return m_v;}
    std::string getOp(){ return m_op;}
};

template<typename T>
class SPGNonExistentVertexEXception : public SPGException
{
    SPGraph<T>* m_g;
public:
    SPGNonExistentVertexEXception(SPGraph<T>* g, std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){
        m_g = g;
    }

    SPGraph<T>* getGraph(){ return m_g;}
};

template<typename T>
class SPGIteratorException : public SPGException
{
    SPGraphIterator<T>* m_it;
public:
    SPGIteratorException(SPGraphIterator<T>* it, std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){
        m_it = it;
    }

    SPGraphIterator<T>* getIterator(){ return m_it;}
};

template<typename T>
class SPGAllocatorException : public SPGException
{
    SPVertex<T>* m_v;
public:
    SPGAllocatorException(SPVertex<T>* v, std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){
        m_v = v;
    }

    SPVertex<T>* getVertex(){ return m_v;}
};


template<typename T>
class SPGVertexException: public SPGException
{
    SPVertex<T>* m_v;
public:
    SPGVertexException(SPVertex<T>* v, std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){
        m_v = v;
    }

    SPVertex<T>* getVertex(){ return m_v;}
};


}

#endif // SPGEXCEPTION_H
