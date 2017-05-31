#ifndef SPGEXCEPTION_H
#define SPGEXCEPTION_H

#include<string>
#include<exception>
#include<sstream>

#include"spgraph.h"
#include"spvertex.h"

namespace spg {

#define THROW_SPG_EXCEPTION(s) throw SPGException(s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_NULL_POINTER_EXCEPTION(s) throw SPGNullPointerException(s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_INCORRECT_OPEARTION_EXCEPTION(s) throw SPGIncorrectOperationException(s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_NON_EXISTENT_VERTEX_EXCEPTION(s) throw SPGNonExistentVertexEXception(s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_ITERATOR_EXCEPTION(s) throw SPGIteratorException(s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_MANIPULATOR_EXCEPTION(s) throw SPGManipualtorException(s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_ALLOCATOR_EXCEPTION(s) throw SPGAllocatorException(s , __LINE__, __FUNCTION__, __TIME__)
#define THROW_SPG_VERTEX_EXCEPTION(s) throw SPGVrtexException(s , __LINE__, __FUNCTION__, __TIME__)

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

class SPGNullPointerException : public SPGException
{
public:
    SPGNullPointerException(): SPGException(){}
    SPGNullPointerException(std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){}
};

class SPGIncorrectOperationException : public SPGException
{
public:
    SPGIncorrectOperationException(): SPGException(){}
    SPGIncorrectOperationException(std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){}
};

class SPGNonExistentVertexEXception : public SPGException
{
public:
    SPGNonExistentVertexEXception(): SPGException(){}
    SPGNonExistentVertexEXception(std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){}
};

class SPGIteratorException : public SPGException
{
public:
    SPGIteratorException(): SPGException(){}
    SPGIteratorException(std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){}
};

class SPGManipualtorException : public SPGException
{
public:
    SPGManipualtorException(): SPGException(){}
    SPGManipualtorException(std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){}
};

class SPGAllocatorException : public SPGException
{
public:
    SPGAllocatorException(): SPGException(){}
    SPGAllocatorException(std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){}
};

class SPGVrtexException : public SPGException
{
public:
    SPGVrtexException(): SPGException(){}
    SPGVrtexException(std::string text, int line, std::string function, std::string time): SPGException(text, line, function, time){}
};


}

#endif // SPGEXCEPTION_H
