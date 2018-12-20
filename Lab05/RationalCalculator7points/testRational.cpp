#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <sstream>
#include <stdexcept>

#include "Rational.h"

using namespace std;

TEST_CASE("Check Rational's constructors", "[ctors]")
{
    ostringstream sout;
    
    SECTION("Constructor wih no parameters")
    {
        sout << Rational();
        REQUIRE(sout.str() == "0/1");
    }
    
    SECTION("Constructor with int64_t numerator")
    {
        sout << Rational(-1234567891011);
        REQUIRE(sout.str() == "-1234567891011/1");
    }
    
    SECTION("Constructor with int64_t numerator, int64_t denominator")
    {
        SECTION("Denominator equal to zero")
        {
            REQUIRE_THROWS_AS(Rational(-34, 0), runtime_error);
        }
        SECTION("Fix denominator's sign")
        {
            SECTION("negative denominator")
            {
                sout << Rational(1, -2);
                REQUIRE(sout.str() == "-1/2");
            }
            SECTION("negative numerator, negative denominator")
            {
                sout << Rational(-1, -2);
                REQUIRE(sout.str() == "1/2");
            }
        }
        SECTION("Reducing")
        {
            SECTION("Case 1")
            {
                sout << Rational(13, 23);
                REQUIRE(sout.str() == "13/23");
            }
            SECTION("Case 2")
            {
                sout << Rational(30000, 10000);
                REQUIRE(sout.str() == "3/1");
            }
            SECTION("Case 3")
            {
                sout << Rational(25, -55);
                REQUIRE(sout.str() == "-5/11");
            }
        }
    }
}

TEST_CASE("Check method toDouble()", "[toDouble]")
{
    ostringstream sout;
    sout << fixed << showpoint << setprecision(4);
    
    SECTION("Case 1")
    {
        sout << Rational(1, 3).toDouble();
        REQUIRE(sout.str() == "0.3333");
    }
    SECTION("Case 2")
    {
        sout << Rational(1, 2).toDouble();
        REQUIRE(sout.str() == "0.5000");
    }
}


TEST_CASE("Check method toSchoolForm", "[toSchoolForm]")
{
    REQUIRE(Rational(15, 3).toSchoolForm() == "5");
    REQUIRE(Rational(-15, 3).toSchoolForm() == "-5");
    REQUIRE(Rational(15, 15).toSchoolForm() == "1");
    REQUIRE(Rational(15, -15).toSchoolForm() == "-1");
    REQUIRE(Rational(15, -3).toSchoolForm() == "-5");
    REQUIRE(Rational(25, 10).toSchoolForm() == "2(1/2)");
    REQUIRE(Rational(-25, 10).toSchoolForm() == "-2(1/2)");
}

TEST_CASE("Check equality, inequality", "[equality]")
{
    REQUIRE(Rational(1, 2) == Rational(-1, -2));
    REQUIRE(Rational(10, 20) == Rational(1, 2));
    REQUIRE(Rational(1, 2) != Rational(1, 3));
    REQUIRE(Rational(-1, 2) != Rational(1, 2));
}

TEST_CASE("Check comparisons", "[comparisons]")
{
    REQUIRE(Rational(1, 2) < Rational(1));
    REQUIRE(Rational(-17, 24) < Rational());
    REQUIRE(Rational(5, 4) > Rational(10, 10));
    REQUIRE(Rational(-5, 3) <= Rational(3, -5));
    REQUIRE(Rational(4, 2) <= Rational(15, 3));
    REQUIRE(Rational(7, 15) >= Rational(6, 15));
    REQUIRE(Rational(7, 15) >= Rational(-7, -15));
}

TEST_CASE("Check Arithmetic operators", "[arithmetic]")
{
    REQUIRE(Rational(1, 2) + Rational(1, 3) == Rational(5, 6));
    REQUIRE(Rational(-1, 2) + Rational(1, 2) == 0);
    REQUIRE(Rational(5, 6) - Rational(1, 2) == Rational(1, 3));
    REQUIRE(Rational(1, 3) - Rational(2, 3) == Rational(-1, 3));
    REQUIRE(Rational(4, 5) * Rational(5, -7) == Rational(-4, 7));
    REQUIRE_THROWS_AS(Rational(7, 3) / 0, runtime_error);
    REQUIRE(Rational(7, 3) / Rational(-2, 5) == Rational(-35, 6));
    REQUIRE(-Rational(3, 19) == Rational(-3, 19));
    REQUIRE(+Rational(3, 4) == Rational(3, 4));
}

TEST_CASE("Check >> operator", "[input]")
{
    Rational r;
    
    SECTION("Read Just a number")
    {
        SECTION("Case 1")
        {
            istringstream sinp("10101");
            bool succ = sinp >> r and sinp.eof() and r == 10101;
            REQUIRE(succ); 
        }
        SECTION("Case 2")
        {
            istringstream sinp("-10101");
            bool succ = sinp >> r and sinp.eof() and r == -10101;
            REQUIRE(succ); 
        }
        SECTION("Case 3")
        {
            istringstream sinp("000");
            bool succ = sinp >> r and sinp.eof() and r == 0;
            REQUIRE(succ); 
        }
        SECTION("Case 4")
        {
            istringstream sinp("hello");
            bool succ = bool(sinp >> r);
            REQUIRE_FALSE(succ); 
        }
    }
    
    SECTION("Full form")
    {
        SECTION("Case 1")
        {
            istringstream sinp("  0/5");
            bool succ = sinp >> r and sinp.eof() and r == 0;
            REQUIRE(succ); 
        }
        SECTION("Case 2")
        {
            istringstream sinp("  -45/-25");
            bool succ = sinp >> r and sinp.eof() and r == Rational(9, 5);
            REQUIRE(succ); 
        }
        SECTION("Case 3")
        {
            istringstream sinp("    -45/+25");
            bool succ = sinp >> r and sinp.eof() and r == Rational(-9, 5);
            REQUIRE(succ); 
        }
        SECTION("Case 4")
        {
            istringstream sinp("-45/");
            bool succ = bool(sinp >> r);
            REQUIRE_FALSE(succ); 
        }
        
        SECTION("Case 5")
        {
            istringstream sinp("-45/--5");
            bool succ = bool(sinp >> r);
            REQUIRE_FALSE(succ); 
        }
        SECTION("Case 6")
        {
            istringstream sinp("-45/hello");
            bool succ = bool(sinp >> r);
            REQUIRE_FALSE(succ); 
        }
    }
}