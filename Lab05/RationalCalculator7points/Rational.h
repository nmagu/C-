#ifndef RATIONAL_H
#define RATIONAL_H

#include <cstdint>
#include <iosfwd>
#include <string>

class Rational
{
    public:
    
    Rational()
    : mNum(0), mDen(1)
    {
    }
    
    Rational(std::int64_t num)
    : mNum(num), mDen(1)
    {
    }
    
    Rational(std::int64_t num, std::int64_t den);
    
    int64_t num() const
    {
        return mNum;
    }
    
    int64_t den() const
    {
        return mDen;
    }
    
    double toDouble() const
    {
        return double(mNum) / mDen;
    }

    std::string toSchoolForm() const;
    
    private:
    
    static std::int64_t gcd(std::int64_t a, std::int64_t b);
    
    std::int64_t mNum;
    std::int64_t mDen;
};

std::ostream& operator<<(std::ostream& out, const Rational& r);
std::istream& operator>>(std::istream& in, Rational& r);

Rational operator+(const Rational& r1, const Rational& r2);
Rational operator-(const Rational& r1, const Rational& r2);
Rational operator*(const Rational& r1, const Rational& r2);
Rational operator/(const Rational& r1, const Rational& r2);

inline
Rational operator-(const Rational& r)
{
    return Rational(-r.num(), r.den());
}

inline
Rational operator+(const Rational& r)
{
    return r;
}

bool operator==(const Rational& r1, const Rational& r2);
bool operator!=(const Rational& r1, const Rational& r2);
bool operator<(const Rational& r1, const Rational& r2);
bool operator>(const Rational& r1, const Rational& r2);
bool operator<=(const Rational& r1, const Rational& r2);
bool operator>=(const Rational& r1, const Rational& r2);

#endif
