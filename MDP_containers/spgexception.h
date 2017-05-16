#ifndef SPGEXCEPTION_H
#define SPGEXCEPTION_H

#include<string>
#include<exception>
#include<sstream>

namespace spg {

class SPGException : public std::exception
{
public:
    SPGException();
    SPGException(std::string text, int line, std::string function, std::string time);

    //virtual const char* what() const throw();

protected:
    std::string m_text;
    int m_line;
    std::string m_function;
    std::string m_time;
};

SPGException::SPGException():
    exception(),
    m_text(""),
    m_line(0),
    m_function(""),
    m_time("")
{

}

SPGException::SPGException(std::string text, int line, std::string function, std::string time):
    exception(),
    m_text(text),
    m_line(line),
    m_function(function),
    m_time(time)
{

}

}

#endif // SPGEXCEPTION_H
