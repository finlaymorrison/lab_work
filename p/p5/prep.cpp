/*
 * Project: p5
 * File: p5/prep.cpp
 * -----
 * File Created: Tuesday, 2nd March 2021 10:19:54 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:31:24 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <iostream>
#include <vector>

class gate
{
protected:
    std::vector<bool> result;
public:
    gate() = default;
    gate(int len) :
        result(len)
    {}
    std::vector<bool>& get_result()
    {
        return result;
    }
};

/* result[0]=out */
class AND : public gate
{
public:
    AND() :
        gate(1)
    {}
    void calculate(bool a, bool b)
    {
        result[0] = a & b;
    }
};

/* result[0]=out */
class OR : public gate
{
public:
    OR() :
        gate(1)
    {}
    void calculate(bool a, bool b)
    {
        result[0] = a | b;
    }
};

/* result[0]=out */
class NOT : public gate
{
public:
    NOT() :
        gate(1)
    {}
    void calculate(bool in)
    {
        result[0] = !in;
    }
};

/* result[0]=out */
class NAND : public gate
{
public:
    NAND() :
        gate(1)
    {}
    void calculate(bool a, bool b)
    {
        AND and_gate;
        NOT not_gate;

        and_gate.calculate(a, b);
        not_gate.calculate(and_gate.get_result()[0]);

        result[0] = not_gate.get_result()[0];
    }
};

/* result[0]=out */
class XOR : public gate
{
public:
    XOR() :
        gate(1)
    {}
    void calculate(bool a, bool b)
    {
        NAND nand_gate0;
        NAND nand_gate1;
        NAND nand_gate2;
        NAND nand_gate3;

        nand_gate0.calculate(a, b);
        nand_gate1.calculate(a, nand_gate0.get_result()[0]);
        nand_gate2.calculate(nand_gate0.get_result()[0], b);
        nand_gate3.calculate(nand_gate1.get_result()[0], nand_gate2.get_result()[0]);

        result[0] = nand_gate3.get_result()[0];
    }
};

/* result[0]=sum result[1]=carry */
class HA : public gate
{
public:
    HA() :
        gate(2)
    {}
    void calculate(bool a, bool b)
    {
        XOR xor_gate;
        AND and_gate;

        xor_gate.calculate(a, b);
        and_gate.calculate(a, b);

        result[0] = xor_gate.get_result()[0];
        result[1] = and_gate.get_result()[0];
    }
};

/* result[0]=sum result[1]=carry */
class FA : public gate
{
public:
    FA() :
        gate(2)
    {}
    void calculate(bool a, bool b, bool ci)
    {
        HA half_adder0;
        HA half_adder1;
        OR or_gate;

        half_adder0.calculate(a, b);
        half_adder1.calculate(half_adder0.get_result()[0], ci);
        or_gate.calculate(half_adder0.get_result()[1], half_adder1.get_result()[1]);

        result[0] = half_adder1.get_result()[0];
        result[1] = or_gate.get_result()[0];
    }
};

/* result[0..7]=sum[0..7] result[8]=overflow */
class ADD : public gate
{
public:
    ADD() :
        gate(9)
    {}
    void calculate(const std::vector<bool>& a, const std::vector<bool>& b, bool ci)
    {
        std::vector<FA> adders(8);

        for(int i = 0; i < 8; ++i)
        {
            adders[i].calculate(a[i], b[i], ci);
            ci = adders[i].get_result()[1];
        }

        for (int i = 0; i < 8; ++i)
        {
            result[i] = adders[i].get_result()[0];
        }
        result[8] = adders[7].get_result()[1];
    }
};

/* result[0..7]=sum[0..7] result[8]=underflow */
class SUB : public gate
{
public:
    SUB() :
        gate(9)
    {}
    void calculate(const std::vector<bool>& a, const std::vector<bool>& b)
    {
        std::vector<NOT> inverters(8);
        std::vector<FA> adders(8);
        NOT not_gate;
        AND and_gate;

        bool ci=1;
        for (int i = 0; i < 8; ++i)
        {
            inverters[i].calculate(b[i]);
            adders[i].calculate(a[i], inverters[i].get_result()[0], ci);
            ci = adders[i].get_result()[1];
        }
        /* testing for underflow */
        not_gate.calculate(adders[7].get_result()[0]);
        and_gate.calculate(a[7], not_gate.get_result()[0]);

        for (int i = 0; i < 8; ++i)
        {
            result[i] = adders[i].get_result()[0];
        }
        result[8] = and_gate.get_result()[0];
    }
};

/* result[0..7]=sum[0..7] result[8]=overflow result[9]=underflow */
class ADDSUB : public gate
{
public:
    ADDSUB() :
        gate(10)
    {}
    void calculate(const std::vector<bool>& a, const std::vector<bool>& b, bool sub)
    {
        std::vector<XOR> inverters(8);
        std::vector<FA> adders(8);
        NOT not_gate;
        AND and_gate;

        bool ci=sub;
        for (int i = 0; i < 8; ++i)
        {
            inverters[i].calculate(b[i], sub);
            adders[i].calculate(a[i], inverters[i].get_result()[0], ci);
            ci = adders[i].get_result()[1];
        }
        /* testing for underflow */
        not_gate.calculate(adders[7].get_result()[0]);
        and_gate.calculate(a[7], not_gate.get_result()[0]);

        for (int i = 0; i < 8; ++i)
        {
            result[i] = adders[i].get_result()[0];
        }
        result[8] = adders[7].get_result()[1];
        result[9] = and_gate.get_result()[0];
    }
};

/* std::ostream&::operator<< overload to handle printing out binary numbers represented in a vector of bools. */
std::ostream& operator<< (std::ostream& os, const std::vector<bool>& vec)
{
    for (int i = vec.size() - 1; i >= 0; --i)
    {
        os << vec[i];
    }
    return os;
}

int main(int argc, char** argv)
{
    std::cout << "adder-subtractor\n";
    for (int i = 0; i < (1 << 17); ++i)
    {
        ADDSUB addsub;

        bool sub = i&0b1;

        std::vector<bool> a(8);
        std::vector<bool> b(8);
        for (int j = 1; j < 9; ++j)
        {
            a[j] = i&(0b1<<j);
            b[j] = i&(0b1<<(j+8));
        }

        addsub.calculate(a, b, sub);

        std::vector<bool> result = addsub.get_result();
        std::vector<bool> num(8);
        for (int i = 0; i < 8; ++i)
        {
            num[i] = result[i];
        }
        bool overflow = result[8];
        bool underflow = result[9];

        std::cout << "a=" << a << " b=" << b << " sub=" << sub << " result=" << num << " overflow=" << overflow <<  " underflow=" << underflow << '\n';
    }
    std::cout << std::flush;
    return 0;
}