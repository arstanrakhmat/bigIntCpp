#pragma once

#include <vector>
#include <iosfwd>
#include <iostream>
#include <stdexcept>

class BigInt
{
    friend std::ostream &operator<<(std::ostream &out, const BigInt &x);
    friend std::istream &operator>>(std::istream &inp, BigInt &x);
    friend BigInt operator+(const BigInt &a, const BigInt &b);
    friend BigInt operator-(const BigInt &a, const BigInt &b);
    friend BigInt operator-(const BigInt &a);
    friend bool operator<(const BigInt &a, const BigInt &b);
    friend BigInt abs(const BigInt &a);
    friend bool operator>(const BigInt &a, const BigInt &b);
    friend bool operator>=(const BigInt &a, const BigInt &b);
    friend bool operator<=(const BigInt &a, const BigInt &b);
    friend bool operator==(const BigInt &a, const BigInt &b);
    friend bool operator!=(const BigInt &a, const BigInt &b);
    friend BigInt operator/(const BigInt &a, const BigInt &b);
    friend BigInt operator*(const BigInt &a, const BigInt &b);
    friend BigInt operator%(const BigInt &a, const BigInt &b);
    friend BigInt multiply(const BigInt &a, const BigInt &b);
    friend std::pair<BigInt, BigInt> divide(const BigInt &a, const BigInt &b);
    friend BigInt remainder(const BigInt &a, const BigInt &b);
    friend BigInt operator++(BigInt &a);
    friend BigInt operator--(BigInt &a);
    friend BigInt operator++(BigInt &a, int);
    friend BigInt operator--(BigInt &a, int);
    friend BigInt operator+=(BigInt &a, BigInt &b);
    friend BigInt operator-=(BigInt &a, BigInt &b);
    friend BigInt operator*=(BigInt &a, BigInt &b);
    friend BigInt operator/=(BigInt &a, BigInt &b);
    friend BigInt operator%=(BigInt &a, BigInt &b);

    std::vector<int> mDigits;
    bool mIsNegative;

public:
    BigInt()
        : mIsNegative(false)
    {
        mDigits.push_back(0);
    }

    BigInt(const std::string &n)
        : mIsNegative(false)
    {
        bool firstZeros = true;

        for (int i = 0; i < (int)n.size(); i++)
        {

            if (i == 0 && n.at(i) == '-')
            {
                mIsNegative = true;
                continue;
            }

            if (n.at(i) == '0' && firstZeros)
            {
                continue;
            }

            if (isdigit(n.at(i)))
            {
                mDigits.push_back(n.at(i) - '0');
                firstZeros = false;
            }
            else
            {
                throw std::runtime_error("Bigint: incrorrect digit " + n);
            }
        }
        if (firstZeros)
        {
            mDigits.push_back(0);
        }
    }

    BigInt(int n) : BigInt(std::to_string(n))
    {
    }

    std::vector<int> getVectorOfDigits() const
    {
        return mDigits;
    }
};

inline std::ostream &operator<<(std::ostream &out, const BigInt &x)
{
    if (x.mDigits.empty())
    {
        out << 0;
        return out;
    }
    if (x.mIsNegative && x != BigInt("0"))
    {
        out << '-';
    }

    int countNumsBezZero = 0;

    for (auto digit : x.mDigits) //0010
    {
        if (digit != 0)
        {
            countNumsBezZero++;
        }
        if (countNumsBezZero != 0) //1
        {
            out << digit; // 10
        }
    }
    if (countNumsBezZero == 0)
    {
        out << 0;
    }
    return out;
}

inline std::istream &operator>>(std::istream &inp, BigInt &x)
{
    std::string n;

    if (inp >> n)
    {
        BigInt t(n);
        x = t;
    }
    else
    {
        inp.setstate(std::ios_base::failbit);
    }

    return inp;
}

BigInt operator-(const BigInt &a) //unary
{
    BigInt r = a;

    if (a != BigInt("0"))
    {
        r.mIsNegative = !a.mIsNegative;
    }

    return r;
}

BigInt add(const BigInt &a, const BigInt &b)
{
    //logic of +
    int i = a.getVectorOfDigits().size() - 1;
    int j = b.getVectorOfDigits().size() - 1;

    std::string s = "";

    int end = 0;
    while (i > -1 || j > -1 || end != 0)
    {
        int t = end;
        if (i > -1)
        {
            t += a.getVectorOfDigits()[i];
            i--;
        }

        if (j > -1)
        {
            t += b.getVectorOfDigits()[j];
            j--;
        }
        end = t / 10;
        int d = t % 10;

        s = std::to_string(d) + s;
    }

    BigInt r(s);
    return r;
}

BigInt subtract(const BigInt &a, const BigInt &b)
{
    //logic of -
    int i = a.getVectorOfDigits().size() - 1;
    int j = b.getVectorOfDigits().size() - 1;

    std::string s = "";

    int end = 0;

    while (i > -1 || j > -1 || end != 0)
    {
        int t = 0;
        if (i > -1)
        {
            t += a.getVectorOfDigits()[i] - end;
            i--;
        }

        if (j > -1)
        {
            t -= b.getVectorOfDigits()[j];
            j--;
        }

        if (t < 0)
        {
            end = 1;
            t += 10;
        }
        else
        {
            end = 0;
        }

        int d = t % 10;
        s = std::to_string(d) + s;
    }

    if (end == 1)
    {
        s = "-" + s;
    }

    BigInt r(s);
    return r;
}

inline BigInt operator-(const BigInt &a, const BigInt &b)
{
    BigInt r;

    //a - b
    //-a - b <=> -(a + b)
    //a - (-b)   a +b
    //-a - (-b)  b - a
    if (!a.mIsNegative && !b.mIsNegative)
    {
        if (b > a)
        {
            r = subtract(b, a);
            r = -r;
        }
        else
        {
            r = subtract(a, b);
        }
    }
    else if (!a.mIsNegative && b.mIsNegative)
    {
        r = add(a, b);
    }
    else if (a.mIsNegative && !b.mIsNegative) //4 - 6
    {
        r = add(a, b);

        r = -r;
    }
    else if (a.mIsNegative && b.mIsNegative)
    {

        // -4 - -2 => -4 + 2
        if (abs(a) > abs(b))
        {
            r = subtract(a, b);
            r = -r;
        }
        else
        {
            //-4 - -9 => -4 + 9
            r = subtract(b, a);
        }
    }

    return r;
}

inline BigInt operator+(const BigInt &a, const BigInt &b)
{
    BigInt r;

    if (a.mIsNegative && b.mIsNegative)
    {
        r = add(a, b);

        r = -r;
    }
    else if (!a.mIsNegative && !b.mIsNegative)
    {
        r = add(a, b);
    }
    else if (a.mIsNegative && !b.mIsNegative) //-3 + 5
    {
        if (abs(b) > abs(a))
        {
            r = subtract(abs(b), abs(a));
        }
        else
        {
            r = subtract(abs(a), abs(b)); //FIX THE LOGIC
            if (r != BigInt("0"))
            {
                r = -r;
            }
        }
    }
    else
    {
        if (abs(b) > abs(a))
        {
            r = subtract(abs(b), abs(a));
            r = -r;
        }
        else
        {
            r = subtract(abs(a), abs(b));
        }
    }

    return r;
}

bool operator<(const BigInt &a, const BigInt &b)
{
    bool check = false;
    bool equal = true;

    if (a.mIsNegative && !b.mIsNegative)
    {
        check = true;
    }
    else if (!a.mIsNegative && b.mIsNegative)
    {
        check = false;
    }
    else if (a.mDigits.size() < b.mDigits.size())
    {
        check = true;
    }
    else if (a.mDigits.size() > b.mDigits.size())
    {
        check = false;
    }
    else if (a.mDigits.size() == b.mDigits.size())
    {
        for (int i = 0; i < (int)a.mDigits.size(); i++)
        {
            if (a.mDigits[i] != b.mDigits[i])
            {
                check = a.mDigits[i] < b.mDigits[i];
                equal = false;
                break;
            }
        }
        if (equal)
        {
            return false;
        }
    }

    if (a.mIsNegative && b.mIsNegative)
    {
        check = !check;
    }

    return check;
}

inline bool operator>(const BigInt &a, const BigInt &b)
{
    return b < a;
}

inline bool operator<=(const BigInt &a, const BigInt &b)
{
    return !(a > b);
}

inline bool operator>=(const BigInt &a, const BigInt &b)
{
    return !(a < b);
}

inline bool operator==(const BigInt &a, const BigInt &b)
{
    return !((a > b) || (b > a));
}

inline bool operator!=(const BigInt &a, const BigInt &b)
{
    return !(a == b);
}
//multiply - to use loop

BigInt abs(const BigInt &a)
{
    return a.mIsNegative ? -a : a;
}

BigInt multiply(const BigInt &a, const BigInt &b)
{
    BigInt r;

    int i = a.mDigits.size() - 1;
    int j = b.mDigits.size() - 1;
    int k = 0;

    while (j > -1)
    {
        std::vector<int> temp;
        int carry = 0;

        for (int z = 0; z < k; z++)
        {
            temp.push_back(0);
        }

        while (i > -1)
        {
            int s = a.mDigits[i] * b.mDigits[j] + carry;
            --i;

            carry = s / 10;
            int ld = s % 10;
            temp.insert(temp.begin(), ld);
            if (i < 0)
            {
                temp.insert(temp.begin(), carry);
            }
        }

        BigInt tempB;
        tempB.mDigits = temp;

        r = r + tempB;
        --j;
        i = a.mDigits.size() - 1;
        ++k;
    }

    return r;
}

inline BigInt operator*(const BigInt &a, const BigInt &b)
{
    BigInt r;
    //-a * b <=> -(a * b)
    //a * -b <=> -(a * b)

    //a * b <=> a * b
    //-a * -b <=> a * b
    if (a == BigInt("0") || b == BigInt("0"))
    {
        return BigInt("0");
    }

    if (!a.mIsNegative && !b.mIsNegative)
    {
        r = multiply(a, b);
    }
    else if ((!a.mIsNegative && b.mIsNegative) || (a.mIsNegative && !b.mIsNegative))
    {
        r = multiply(a, b);
        r = -r;
    }
    else if (a.mIsNegative && b.mIsNegative)
    {
        r = multiply(a, b);
    }

    return r;
}

std::pair<BigInt, BigInt> divide(const BigInt &a, const BigInt &b)
{
    BigInt r;
    r.mDigits.clear();
    BigInt temp;
    int result = 0;

    int i = 0;

    while (i < int(a.mDigits.size()))
    {
        if (temp == BigInt("0"))
        {
            temp.mDigits.clear();
        }

        temp.mDigits.push_back(a.mDigits[i++]); //1010 / 10

        // while (temp < b)
        // {
        //     temp.mDigits.push_back(a.mDigits[i++]); // 10
        // }

        while (abs(temp) >= abs(b)) //10 - 10
        {
            temp = subtract(temp, b);
            result++;
        }

        r.mDigits.push_back(result);
        result = 0;
    }
    // return temp; for remainder

    return std::make_pair(r, temp);
}

inline BigInt operator/(const BigInt &a, const BigInt &b)
{
    std::pair<BigInt, BigInt> r;

    if (a == BigInt("0"))
    {
        return BigInt();
    }
    else if (b == BigInt("0"))
    {
        std::runtime_error("Can not be divided by zero");
    }
    else if (a == b)
    {
        return BigInt("1");
    }
    else if ((a.mIsNegative && !b.mIsNegative) || (!a.mIsNegative && b.mIsNegative))
    {
        if (abs(a) >= abs(b))
        {
            r = divide(a, b);
            return -(r.first);
        }
        else
        {
            return BigInt();
        }
    }
    else
    {
        if (abs(a) > abs(b))
        {
            r = divide(a, b);
            return r.first;
        }
        else
        {
            return BigInt();
        }
    }
    return r.first;
}

inline BigInt operator%(const BigInt &a, const BigInt &b)
{
    std::pair<BigInt, BigInt> r;

    if (a == BigInt("0"))
    {
        return BigInt();
    }
    else if (b == BigInt("0"))
    {
        std::runtime_error("Can not be divided by zero");
    }
    else if (abs(a) == abs(b))
    {
        return BigInt();
    }
    else if (a.mIsNegative)
    {
        if (abs(a) >= abs(b))
        {
            r = divide(a, b);
            return -(r.second);
        }
        else
        {
            BigInt temp = a;
            return temp;
        }
    }
    else
    {
        if (abs(a) > abs(b))
        {
            r = divide(a, b);
            return r.second;
        }
        else
        {
            BigInt temp = a;
            return temp;
        }
    }
    return r.second;
}

inline BigInt operator++(BigInt &a)
{
    return a + BigInt(1);
}

inline BigInt operator++(BigInt &a, int)
{
    BigInt temp;
    ++a;
    return temp;
}

inline BigInt operator--(BigInt &a)
{
    return a - BigInt(1);
}

inline BigInt operator--(BigInt &a, int)
{
    BigInt temp;
    --a;
    return temp;
}

inline BigInt operator+=(BigInt &a, BigInt &b)
{
    a = a + b;
    return a;
}

inline BigInt operator-=(BigInt &a, BigInt &b)
{
    a = a - b;

    return a;
}

inline BigInt operator*=(BigInt &a, BigInt &b)
{
    a = a * b;

    return a;
}

inline BigInt operator/=(BigInt &a, BigInt &b)
{
    a = a / b;

    return a;
}

inline BigInt operator%=(BigInt &a, BigInt &b)
{
    a = a % b;

    return a;
}