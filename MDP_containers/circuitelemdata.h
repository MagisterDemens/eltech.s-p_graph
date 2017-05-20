#ifndef CIRCUITELEMDATA_H
#define CIRCUITELEMDATA_H

#include<iostream>

class CircuitElemData
{
    double m_r;
    double m_u;
    double m_i;
public:
    CircuitElemData(){m_r = -1; m_u = -1; m_i = -1;}
    CircuitElemData(double R, double U, double I){m_r = R; m_u = U; m_i = I;
    }

    double getR() const {return m_r;}
    void setR(double R){m_r = R;}

    double getU() const {return m_u;}
    void setU(double U){m_u = U;}

    double getI() const {return m_i;}
    void setI(double I){m_i = I;}

    friend std::ostream& operator << (std::ostream& os, const CircuitElemData& data){
        double r = data.getR();
        double u = data.getU();
        double i = data.getI();
        os << r << " " << u << " " << i;
        return os;
    }

    friend std::istream& operator >> (std::istream& is, CircuitElemData& data){
        double r,u,i;
        is >> r >> u >> i;
        data = CircuitElemData(r,u,i);
        return is;
    }
};

#endif // CIRCUITELEMDATA_H
















