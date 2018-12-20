#include <cctype>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "Rational.h"

using namespace std;

Rational::Rational(int64_t num, int64_t den)
: mNum(num), mDen(den)
{
    if (mDen == 0)
    {
        throw runtime_error("Rational: denominator equal to zero");
    }
    
    int64_t d = gcd(mNum, mDen);
    mNum /= d;
    mDen /= d;
    
    if (mDen < 0)
    {
        mNum = -mNum;
        mDen = -mDen;
    }
}

ostream& operator<<(ostream& out, const Rational& r)
{
    return out << r.num() << "/" << r.den();
}

istream& operator>>(istream& inp, Rational& r)
{
    int64_t num;
    char ch;
    int64_t den;
    
    if (not (inp >> num))
    {
        return inp;
    }
    
    if (inp.eof())
    {
        r = num;
        return inp;
    }
    
    if (not inp.get(ch))
    {
        return inp;
    }
    
    if (ch != '/')
    {
        r = num;
        inp.unget();
        return inp;
    }
    
    if (not inp.get(ch))
    {
        return inp;
    }
    
    if (not (ch == '+' or ch == '-' or isdigit(ch)))
    {
        inp.setstate(ios_base::failbit);
        return inp;
    }
    
    inp.unget();
    
    if (not (inp >> den))
    {
        return inp;
    }
    
    r = Rational(num, den);
    
    return inp;
}
    
bool operator==(const Rational& r1, const Rational& r2)
{
    return r1.num() == r2.num() and r1.den() == r2.den();
}

bool operator!=(const Rational& r1, const Rational& r2)
{
    return not (r1 == r2);
}

bool operator<(const Rational& r1, const Rational& r2)
{
    return r1.num() * r2.den() < r2.num() * r1.den();
}

bool operator>(const Rational& r1, const Rational& r2)
{
    return r2 < r1;
}

bool operator<=(const Rational& r1, const Rational& r2)
{
    return not (r2 < r1);
}

bool operator>=(const Rational& r1, const Rational& r2)
{
    return not (r1 < r2);
}

Rational operator+(const Rational& r1, const Rational& r2)
{
    return Rational(r1.num() * r2.den() + r2.num() * r1.den(), r1.den() * r2.den());
}


Rational operator-(const Rational& r1, const Rational& r2)
{
    return Rational(r1.num() * r2.den() - r2.num() * r1.den(), r1.den() * r2.den());
}


Rational operator*(const Rational& r1, const Rational& r2)
{
    return Rational(r1.num() * r2.num(), r1.den() * r2.den());
}


Rational operator/(const Rational& r1, const Rational& r2)
{
    if (r2 == 0)
    {
        throw runtime_error("Rational: division by zero");
    }
    
    return Rational(r1.num() * r2.den(), r1.den() * r2.num());
}

string Rational::toSchoolForm() const
{
    ostringstream sout;
    
    if (mDen == 1)
    {
        sout << mNum; 
    }
    else if (abs(mNum) > mDen)
    {
        sout << mNum / mDen << "(" << abs(mNum) % mDen << "/" << mDen << ")";
    }
    else
    {
        sout << *this;
    }
    
    return sout.str();
}

int64_t Rational::gcd(int64_t a, int64_t b)
{
    a = abs(a);
    b = abs(b);
    
    if (a == 0)
    {
        return b;
    }
    
    if (b == 0)
    {
        return a;
    }
    
    int64_t r = a % b;
    while (r != 0)
    {
        a = b;
        b = r;
        r = a % b;
    }
    
    return b;
}