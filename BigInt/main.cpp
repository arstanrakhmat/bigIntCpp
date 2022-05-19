#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../doctest/doctest.h"

#include "BigInt.hpp"
#include "sstream"

using namespace std;

TEST_CASE("Default constructor")
{
    BigInt a;

    ostringstream sout;

    sout << a;

    REQUIRE(sout.str() == "0");
}

TEST_CASE("Constructor with specirifed number")
{
    ostringstream sout;

    SUBCASE("BigInt with positive number")
    {
        BigInt a("20");

        sout << a;

        REQUIRE(sout.str() == "20");
    }

    SUBCASE("BigInt with negative number")
    {
        BigInt a("-10");

        sout << a;

        REQUIRE(sout.str() == "-10");
    }

    SUBCASE("Zeros at the beggining")
    {
        BigInt a("0010");

        sout << a;

        REQUIRE(sout.str() == "10");
    }
}

TEST_CASE("BigInt: addition")
{
    ostringstream sout;

    SUBCASE("-20 + -30")
    {
        BigInt a("-20");
        BigInt b("-30");

        sout << a + b;

        REQUIRE(sout.str() == "-50");
    }

    SUBCASE("50 + 20")
    {
        BigInt a("50");
        BigInt b("20");

        sout << a + b;

        REQUIRE(sout.str() == "70");
    }

    SUBCASE("BIG NUN")
    {
        BigInt a("2057474648564733836385748337");
        BigInt b("46463783464737364846393878974324872537987458");

        sout << a + b;

        REQUIRE(sout.str() == "46463783464737366903868527539058708923735795");
    }

    SUBCASE("-20 + 30")
    {
        BigInt a("-20");
        BigInt b("30");

        sout << a + b;

        REQUIRE(sout.str() == "10");
    }

    SUBCASE("-30 + 40")
    {
        BigInt a("-30");
        BigInt b("40");

        sout << a + b;

        REQUIRE(sout.str() == "10");
    }

    SUBCASE("0 + 1")
    {
        BigInt a("0");
        BigInt b("1");

        sout << a + b;

        REQUIRE(sout.str() == "1");
    }

    SUBCASE("0 + 10")
    {
        BigInt a("0");
        BigInt b("10");

        sout << a + b;

        REQUIRE(sout.str() == "10");
    }

    SUBCASE("1 + 0")
    {
        BigInt a("1");
        BigInt b("0");

        sout << a + b;

        REQUIRE(sout.str() == "1");
    }
    // SUBCASE("-10 + 5")
    // {
    //     BigInt a("-10");
    //     BigInt b("5");

    //     sout << a + b;

    //     REQUIRE(sout.str() == "-5");
    // }

    // SUBCASE("[-500, 500]")
    // {
    //     for (int i = -500; i <= 500; ++i)
    //     {
    //         for (int j = -500; j <= 500; ++j)
    //         {
    //             BigInt x = BigInt(to_string(i));
    //             BigInt y = BigInt(to_string(j));
    //             ostringstream sout2;
    //             // std::cout << x << "     " << y << std::endl;
    //             sout2 << x + y;
    //             REQUIRE(sout2.str() == to_string(i + j));
    //         }
    //     }
    // }
}

TEST_CASE("BigInt: subtraction")
{
    ostringstream sout;

    SUBCASE("40 - 20")
    {
        BigInt a("40");
        BigInt b("20");

        sout << a - b;

        REQUIRE(sout.str() == "20");
    }

    SUBCASE("20 - (-60)")
    {
        BigInt a("20");
        BigInt b("-60");

        sout << a - b;

        REQUIRE(sout.str() == "80");
    }

    SUBCASE("-10 - 55")
    {
        BigInt a("-10");
        BigInt b("55");

        sout << a - b;

        REQUIRE(sout.str() == "-65");
    }

    SUBCASE("-100 - (-200)")
    {
        BigInt a("-100");
        BigInt b("-200");

        sout << a - b;

        REQUIRE(sout.str() == "100");
    }

    SUBCASE("21 - 15")
    {
        BigInt a("21");
        BigInt b("15");

        sout << a - b;

        REQUIRE(sout.str() == "6");
    }

    SUBCASE("49 - 97")
    {
        BigInt a("49");
        BigInt b("97");

        sout << a - b;

        REQUIRE(sout.str() == "-48");
    }

    SUBCASE("5 - (17)")
    {
        BigInt x = 5;
        BigInt y = 17;
        sout << x - y;
        REQUIRE(sout.str() == "-12");
    }

    // SUBCASE("super test")
    // {
    //     for (int i = -100; i <= 100; i++)
    //     {
    //         BigInt a(std::to_string(i));
    //         for (int j = -100; j <= 100; j++)
    //         {
    //             int sum = i - j;
    //             cout << i << "-" << j << "\n"; //use to see which test it fails
    //             stringstream ss;
    //             BigInt b(std::to_string(j));
    //             ss << a - b;
    //             CHECK(ss.str() == to_string(sum));
    //         }
    //     }
    // }
}

TEST_CASE("BigInt: less operation")
{
    ostringstream sout;

    SUBCASE("13 < 20")
    {
        BigInt a("13");
        BigInt b("20");

        bool isTrue = a < b ? true : false;

        REQUIRE(isTrue);
    }

    SUBCASE("-5 < 1")
    {
        BigInt a("-5");
        BigInt b("1");

        bool isTrue = a < b;

        REQUIRE(isTrue);
    }

    SUBCASE("-37 > -50")
    {
        BigInt a("-37");
        BigInt b("-50");

        bool isTrue = !(a < b);

        REQUIRE(isTrue);
    }

    SUBCASE("234 < -3")
    {
        BigInt a("234");
        BigInt b("-3");

        bool isTrue = !(a < b);

        REQUIRE(isTrue);
    }

    SUBCASE("32 < 100")
    {
        BigInt a("32");
        BigInt b("100");

        bool isTrue = a < b;

        REQUIRE(isTrue);
    }

    SUBCASE("15 < 17")
    {
        BigInt a("15");
        BigInt b("17");

        bool isTrue = a < b;

        REQUIRE(isTrue);
    }

    SUBCASE("-15 < -13")
    {
        BigInt a("-15");
        BigInt b("-13");

        bool isTrue = a < b;

        REQUIRE(isTrue);
    }
}

TEST_CASE("BigInt: greated than operation")
{
    SUBCASE("89 > 76")
    {
        BigInt a("89");
        BigInt b("76");

        bool isTrue = a > b;

        REQUIRE(isTrue);
    }

    SUBCASE("89 > -100")
    {
        BigInt a("89");
        BigInt b("-100");

        bool isTrue = a > b;

        REQUIRE(isTrue);
    }

    // SUBCASE("Range -100 to 100")
    // {
    //     for (int i = -100; i <= 100; i++)
    //     {
    //         for (int j = -100; j <= 100; j++)
    //         {
    //             REQUIRE((BigInt(to_string(i)) < BigInt(to_string(j))) == (i < j));
    //         }
    //     }
    // }
}

//check all comparison operators (essepical <<<<<<<<<<<<<<<<<)

TEST_CASE("Multiplication operator")
{
    ostringstream sout;

    SUBCASE("5 * 4")
    {
        BigInt a("5");
        BigInt b("4");

        sout << a * b;

        REQUIRE(sout.str() == "20");
    }

    SUBCASE("-5 * 2")
    {
        BigInt a("-5");
        BigInt b("2");

        sout << a * b;

        REQUIRE(sout.str() == "-10");
    }

    SUBCASE("3 * -2")
    {
        BigInt a("3");
        BigInt b("-2");

        sout << a * b;

        REQUIRE(sout.str() == "-6");
    }

    SUBCASE("-5 * -5")
    {
        BigInt a("-5");
        BigInt b("-5");

        sout << a * b;

        REQUIRE(sout.str() == "25");
    }

    SUBCASE("15 * 12")
    {
        BigInt a("15");
        BigInt b("12");

        sout << a * b;

        REQUIRE(sout.str() == "180");
    }

    SUBCASE("123 * 9")
    {
        BigInt a("123");
        BigInt b("9");

        sout << a * b;

        REQUIRE(sout.str() == "1107");
    }

    // SUBCASE("[-500, 500]")
    // {
    //     for (int i = -500; i <= 500; ++i)
    //     {
    //         BigInt x = BigInt(to_string(i));

    //         for (int j = -500; j <= 500; ++j)
    //         {
    //             //cout << i << "*" << j << "\n"; //use to see which test it fails

    //             BigInt y = BigInt(to_string(j));
    //             ostringstream sout2;
    //             sout2 << x * y;
    //             REQUIRE(sout2.str() == to_string(i * j));
    //         }
    //     }
    // }

    // SUBCASE("super test")
    // {
    //     for (int i = 100; i <= 110; i++)
    //     {
    //         BigInt a(std::to_string(i));
    //         for (int j = -100; j <= 100; j++)
    //         {
    //             int sum = i * j;
    //             cout << i << "*" << j << "\n"; //use to see which test it fails
    //             stringstream ss;
    //             BigInt b(std::to_string(j));
    //             ss << a * b;
    //             CHECK(ss.str() == to_string(sum));
    //         }
    //     }
    // }
}

TEST_CASE("Divsion operator")
{

    ostringstream sout;

    SUBCASE("10 / 5")
    {
        BigInt a("10");
        BigInt b("5");
        sout << a / b;
        REQUIRE(sout.str() == "2");
    }

    SUBCASE("121 / 11")
    {
        BigInt a("121");
        BigInt b("11");

        sout << a / b;

        REQUIRE(sout.str() == "11");
    }

    SUBCASE("-121 / 11")
    {
        BigInt a("-121");
        BigInt b("11");

        sout << a / b;

        REQUIRE(sout.str() == "-11");
    }

    SUBCASE("5000 / 5")
    {
        BigInt a("5000");
        BigInt b("5");

        sout << a / b;

        REQUIRE(sout.str() == "1000");
    }

    SUBCASE("1010 / 10")
    {
        BigInt a("1010");
        BigInt b("10");

        sout << a / b;

        REQUIRE(sout.str() == "101");
    }

    // SUBCASE("[-100, 100]")
    // {
    //     for (int i = -100; i <= 100; ++i)
    //     {
    //         BigInt x = BigInt(to_string(i));

    //         for (int j = -100; j <= 100; ++j)
    //         {
    //             cout << i << "/" << j << "\n"; //use to see which test it fails

    //             BigInt y = BigInt(to_string(j));
    //             ostringstream sout2;
    //             if (j == 0)
    //             {
    //                 continue;
    //             }
    //             //ostringstream sout2;
    //             sout2 << x / y;
    //             REQUIRE(sout2.str() == to_string(i / j));
    //         }
    //     }
    // }
}

TEST_CASE("Remainder operator")
{
    ostringstream sout;

    SUBCASE("4 % 2")
    {
        BigInt a("4");
        BigInt b("2");

        sout << a % b;

        REQUIRE(sout.str() == "0");
    }

    SUBCASE("10 % 3")
    {
        BigInt a("10");
        BigInt b("3");

        sout << a % b;

        REQUIRE(sout.str() == "1");
    }

    SUBCASE("-20 % 3")
    {
        BigInt a("-20");
        BigInt b("3");

        sout << a % b;

        REQUIRE(sout.str() == "-2");
    }

    SUBCASE("161 % -14")
    {
        BigInt a("163");
        BigInt b("-14");

        sout << a % b;

        REQUIRE(sout.str() == "9");
    }

    // SUBCASE("[-100, 100]")
    // {
    //     for (int i = -100; i <= 100; ++i)
    //     {
    //         BigInt x = BigInt(to_string(i));

    //         for (int j = -100; j <= 100; ++j)
    //         {
    //             cout << i << "%" << j << "\n"; //use to see which test it fails

    //             BigInt y = BigInt(to_string(j));
    //             ostringstream sout2;
    //             if (j == 0)
    //             {
    //                 continue;
    //             }
    //             //ostringstream sout2;
    //             sout2 << x % y;
    //             REQUIRE(sout2.str() == to_string(i % j));
    //         }
    //     }
    // }
}

TEST_CASE("Increment and Decrement operators")
{
    ostringstream sout;

    SUBCASE("++5")
    {
        BigInt a(5);
        sout << ++a;

        REQUIRE(sout.str() == "6");
    }

    SUBCASE("--7")
    {
        BigInt a(7);
        sout << --a;

        REQUIRE(sout.str() == "6");
    }
}

TEST_CASE("+= -=")
{
    ostringstream sout;

    SUBCASE("5 += 3")
    {
        BigInt a(5);
        BigInt b(3);

        a += b;
        sout << a;

        REQUIRE(sout.str() == "8");
    }

    SUBCASE("7 -= 2")
    {
        BigInt a(7);
        BigInt b(2);

        a -= b;
        sout << a;

        REQUIRE(sout.str() == "5");
    }
}