#include "spgexception.h"

namespace spg {

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
    m_function(fucntion),
    m_time(time)
{

}

const char *SPGException::what() const
{
    std::ostringstream oss;
    oss << text << " in fucntion " << function << " in line " << line << ". Time: " << time;
    std::string temp_str = oss.str();
    return temp_str.c_str();
}

}
