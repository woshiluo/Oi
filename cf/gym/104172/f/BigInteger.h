#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<queue>
#include<map>
#include<vector>
#include<sstream>
using namespace std;
class BigInteger
{
    public :
        //constructor
        BigInteger(int = 0);
        BigInteger(long long);
        BigInteger(const string &);
        BigInteger(const char *str)
        {
            *this = string(str);
        }

        //assignment operators
        BigInteger &operator=(int num)
        {
            return *this = BigInteger(num);
        }
        BigInteger &operator=(long long num)
        {
            return *this = BigInteger(num);
        }
        BigInteger &operator=(const string &str)
        {
            return *this = BigInteger(str);
        }
        BigInteger &operator=(const char *str)
        {
            return *this = BigInteger(str);
        }

        //relatiional operators
        bool operator<(const BigInteger &obj) const
        {
            return cmp(obj) < 0;
        }
        bool operator>(const BigInteger &obj) const
        {
            return cmp(obj) > 0;
        }
        bool operator<=(const BigInteger &obj) const
        {
            return cmp(obj) <= 0;
        }
        bool operator>=(const BigInteger &obj) const
        {
            return cmp(obj) >= 0;
        }
        bool operator==(const BigInteger &obj) const
        {
            return cmp(obj) == 0;
        }
        bool operator!=(const BigInteger &obj) const
        {
            return cmp(obj) != 0;
        }

        //arithmetic operators
        BigInteger operator+() const
        {
            return *this;
        }
        BigInteger operator-() const
        {
            return BigInteger(-sign_, val_);
        }
        BigInteger operator+(const BigInteger &) const;
        BigInteger operator-(const BigInteger &) const;
        BigInteger operator*(const BigInteger &) const;
        BigInteger operator/(const BigInteger &) const;
        BigInteger operator%(const BigInteger &) const;

        //compound assignment operators
        BigInteger &operator+=(const BigInteger &obj)
        {
            return *this = *this + obj;
        }
        BigInteger &operator-=(const BigInteger &obj)
        {
            return *this = *this - obj;
        }
        BigInteger &operator*=(const BigInteger &obj)
        {
            return *this = *this * obj;
        }
        BigInteger &operator/=(const BigInteger &obj)
        {
            return *this = *this / obj;
        }
        BigInteger &operator%=(const BigInteger &obj)
        {
            return *this = *this % obj;
        }

        //increment and decrement operators
        BigInteger &operator++()
        {
            return *this += 1;
        }
        BigInteger &operator--()
        {
            return *this -= 1;
        }
        BigInteger operator++(int);
        BigInteger operator--(int);

        //input and output
        friend istream &operator>>(istream &, BigInteger &);
        friend ostream &operator<<(ostream &, const BigInteger &);

    protected :
        enum div_type { division, remainder };
        enum cmp_type { with_sign, without_sign };
        static const int base_ = (int)1e8;
        static const int width_ = 8;
        BigInteger(int s, const vector<int> &v) : sign_(s), val_(v) {}
        int cmp(const BigInteger &, cmp_type = with_sign) const;
        BigInteger &delZero();
        BigInteger &add(const BigInteger &);
        BigInteger &sub(const BigInteger &);
        BigInteger &mul(const BigInteger &, const BigInteger &);
        BigInteger &div(BigInteger &, BigInteger, div_type = division);

    private :
        int sign_;
        vector<int> val_;
};

BigInteger::BigInteger(int num) : sign_(0)
{
    if (num < 0) sign_ = -1, num = -num;
    else if (num > 0) sign_ = 1;
    do
    {
        val_.push_back(num % base_);
        num /= base_;
    }
    while (num);
}

BigInteger::BigInteger(long long num) : sign_(0)
{
    if (num < 0) sign_ = -1, num = -num;
    else if (num > 0) sign_ = 1;
    do
    {
        val_.push_back(num % base_);
        num /= base_;
    }
    while (num);
}

BigInteger::BigInteger(const string &str)
{
    sign_ = str[0] == '-' ? -1 : 1;
    int be = str[0] == '-' ? 1 : 0, en = str.size();
    while ((en -= width_) >= be)
    {
        stringstream ss(str.substr(en, width_));
        int temp;
        ss >> temp;
        val_.push_back(temp);
    }
    if ((en += width_) > be)
    {
        stringstream ss(str.substr(be, en - be));
        int temp;
        ss >> temp;
        val_.push_back(temp);
    }
    delZero();
}

BigInteger BigInteger::operator+(const BigInteger &obj) const
{
    if (sign_ * obj.sign_ == 1)
    {
        BigInteger temp;
        return cmp(obj, without_sign) >= 0 ? (temp = *this).add(obj) : (temp = obj).add(*this);
    }
    else if (sign_ * obj.sign_ == -1) return *this - -obj;
    else return sign_ == 0 ? obj : *this;
}

BigInteger BigInteger::operator-(const BigInteger &obj) const
{
    if (sign_ * obj.sign_ == 1)
    {
        BigInteger temp;
        return cmp(obj, without_sign) >= 0 ? (temp = *this).sub(obj) : (temp = -obj).sub(*this);
    }
    else if (sign_ * obj.sign_ == -1) return *this + -obj;
    else return sign_ == 0 ? -obj : *this;
}

inline BigInteger BigInteger::operator*(const BigInteger &obj) const
{
    BigInteger temp;
    return (temp.sign_ = sign_ * obj.sign_) == 0 ? temp : temp.mul(*this, obj);
}

inline BigInteger BigInteger::operator/(const BigInteger &obj) const
{
    BigInteger temp, mod = *this;
    return cmp(obj, without_sign) < 0 || (temp.sign_ = sign_ * obj.sign_) == 0 ? temp : temp.div(mod, obj);
}

inline BigInteger BigInteger::operator%(const BigInteger &obj) const
{
    BigInteger temp, mod = *this;
    return cmp(obj, without_sign) < 0 || (temp.sign_ = sign_) == 0 ? mod : temp.div(mod, obj, remainder);
}

inline BigInteger BigInteger::operator++(int)
{
    BigInteger temp = *this;
    ++*this;
    return temp;
}

inline BigInteger BigInteger::operator--(int)
{
    BigInteger temp = *this;
    --*this;
    return temp;
}

inline istream &operator>>(istream &in, BigInteger &obj)
{
    string str;
    if (in >> str) obj = str;
    return in;
}

ostream &operator<<(ostream &out, const BigInteger &obj)
{
    if (obj.sign_ == -1) out << '-';
    out << obj.val_.back();
    for (int i = obj.val_.size() - 2; i >= 0; i--)
        out << setw(BigInteger::width_) << setfill('0') << obj.val_[i];
    return out;
}

int BigInteger::cmp(const BigInteger &obj, cmp_type typ) const
{
    if (typ == with_sign && sign_ != obj.sign_) return sign_ - obj.sign_;
    int sign = typ == with_sign ? sign_ : 1;
    if (val_.size() != obj.val_.size()) return sign * (val_.size() - obj.val_.size());
    for (int i = val_.size() - 1; i >= 0; i--)
        if (val_[i] != obj.val_[i]) return sign * (val_[i] - obj.val_[i]);
    return 0;
}

inline BigInteger &BigInteger::delZero()
{
    while(val_.back() == 0 && val_.size() > 1) val_.pop_back();
    if (val_.back() == 0) sign_ = 0;
    return *this;
}

BigInteger &BigInteger::add(const BigInteger &obj)
{
    int os = obj.val_.size();
    val_.push_back(0);
    for (int i = 0; i < os; i++)
    {
        long long tmp = (long long) val_[i] + obj.val_[i];
        if(tmp >= base_) tmp -= base_, ++val_[i + 1];
        val_[i] = tmp;
    }
    return delZero();
}

BigInteger &BigInteger::sub(const BigInteger &obj)
{
    int pos = obj.val_.size();
    for (int i = 0; i < pos; i++)
    {
        long long tmp = (long long) val_[i] - obj.val_[i];
        if(tmp < 0) tmp += base_, --val_[i + 1];
        val_[i] = tmp;
    }
    while (val_[pos] < 0) val_[pos] += base_, --val_[++pos];
    return delZero();
}

BigInteger &BigInteger::mul(const BigInteger &a, const BigInteger &b)
{
    int as = a.val_.size(), bs = b.val_.size();
    val_.resize(as + bs);
    for (int i = 0; i < as; i++) for (int j = 0; j < bs; j++)
        {
            int x = i + j;
            long long tmp = val_[x] + (long long) a.val_[i] * b.val_[j];
            val_[x + 1] += tmp / base_;
            tmp %= base_;
            val_[x] = tmp;
        }
    return delZero();
}

BigInteger &BigInteger::div(BigInteger &a, BigInteger b, div_type typ)
{
    int move = a.val_.size() - b.val_.size();
    val_.resize(move + 1);
    b.val_.insert(b.val_.begin(), move, 0);
    for (int i = move; i >= 0; i--)
    {
        int left = 0, right = base_;
        while (left + 1 < right)
        {
            int mid = (left + right) >> 1;
            if (a.cmp(b * BigInteger(mid), without_sign) >= 0) left = mid;
            else right = mid;
        }
        val_[i] = left;
        a.sub(b * BigInteger(left));
        b.val_.erase(b.val_.begin());
    }
    return typ == division ? delZero() : a;
}
