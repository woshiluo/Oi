/*
 * f.cpp 2024-09-21
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cinttypes>

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

using i128 = __int128;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const i64 mod1 = ( 1LL << 61 ) - 1;

template<i64 P> struct ModInt {// {{{
    i64 x;
    constexpr ModInt() : x {0} {}
    constexpr ModInt(i64 _x) : x {norm(_x % get_mod())} {}
    
    static i64 mod;

    constexpr static i64 get_mod() { return P > 0? P: mod; }
    constexpr static void set_mod(i64 _mod) { mod = _mod; }

    static constexpr i64 norm(i64 x) {
        if (x < 0) {
            x += get_mod();
        }
        if (x >= get_mod()) {
            x -= get_mod();
        }
        return x;
    }
    constexpr i64 val() const { return x; }
    constexpr ModInt operator-() const {
        ModInt res;
        res.x = norm(get_mod() - x);
        return res;
    }

    constexpr ModInt inv() const { return pow(*this, get_mod() - 2); }

    constexpr ModInt& operator*=(const ModInt &rhs) & { x = (((i128)x) * rhs.x) % get_mod(); return *this; }
    constexpr ModInt& operator+=(const ModInt &rhs) & { x = norm(x + rhs.x); return *this; }
    constexpr ModInt& operator-=(const ModInt rhs) & { x = norm(x - rhs.x); return *this; }
    constexpr ModInt& operator/=(const ModInt rhs) & { return *this *= rhs.inv(); }

    friend constexpr ModInt operator*(const ModInt& lhs, const ModInt& rhs) { ModInt res = lhs; res *= rhs; return res; }
    friend constexpr ModInt operator+(const ModInt& lhs, const ModInt& rhs) { ModInt res = lhs; res += rhs; return res; }
    friend constexpr ModInt operator-(const ModInt& lhs, const ModInt& rhs) { ModInt res = lhs; res -= rhs; return res; }
    friend constexpr ModInt operator/(const ModInt& lhs, const ModInt& rhs) { ModInt res = lhs; res /= rhs; return res; }

    friend constexpr bool operator==(const ModInt& lhs, const ModInt& rhs) { return lhs.val() == rhs.val(); }
    friend constexpr bool operator!=(const ModInt& lhs, const ModInt& rhs) { return lhs.val() != rhs.val(); }
//    friend constexpr bool operator<(const ModInt& lhs, const ModInt& rhs) { return lhs.val() < rhs.val(); }
	void output( const char end = '\n' ) { printf( "%" PRId64 "%c", x, end ); }
}; // }}}

struct Hash {
	ModInt<mod1> p1;

	Hash(i32 x = 0) { p1 = x; }

	void add( ci32 x ) {
		p1 *= 10; p1 += x;
	}

	Hash operator+( const Hash &_b ) const {
		Hash res;
		res.p1 = p1 + _b.p1;
		return res;
	}
	Hash operator-( const Hash &_b ) const {
		Hash res;
		res.p1 = p1 - _b.p1;
		return res;
	}
	Hash operator*( const Hash &_b ) const {
		Hash res;
		res.p1 = p1 * _b.p1;
		return res;
	}

	bool operator< ( const Hash &_b ) const { return p1.x < _b.p1.x; }
};

const int N = 2e6 + 1e4;

std::map<Hash, int> mp;


std::pair<Hash, Hash> fib(ci32 n) {
	if (n == 0) return {0, 1};
	const auto p = fib(n >> 1);
	const Hash c = p.first * (p.second * 2 - p.first);
	const Hash d = p.first * p.first + p.second * p.second;
	if (n & 1)
		return {d, c + d};
	else
		return {c, d};
}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	std::vector<std::pair<Hash, i32>> list;
	std::vector<std::string> num(n);
	for( int i = 1; i <= n; i ++ ) {
		std::cin >> num[ i - 1 ];
	}
	std::sort( num.begin(), num.end(), []( const auto &_a, const auto &_b ) {
			if( _a.size() == _b.size() ) 
				return  _a < _b;
			return _a.size() < _b.size();
	});
	i64 res = 0;
	for( int i = 1; i <= n; i ++ ) {
		const char *buf = num[ i - 1 ].c_str();
		ci32 len = strlen(buf);
		Hash cur;
		for( int p = 0; p < len; p ++ ) 
			cur.add( buf[p] - '0' );
		if( len <= 18 ) {
			const long double p1 = ( log10l( sqrtl(5.0) * std::stoll(buf) ) );
			const long double p2 = ( log10l( ( sqrtl(5.0) + 1.0 ) / 2.0 ) );
			list.emplace_back( cur, p1 / p2 );
		}
		else {
			num[ i - 1 ][18] = 0;
			const long double p1 = ( log10l( sqrtl(5.0) * std::stoll(buf) ) + ( len - 18 ) );
			const long double p2 = ( log10l( ( sqrtl(5.0) + 1.0 ) / 2.0 ) );
			list.emplace_back( cur, p1 / p2 );
		}
		const auto &[ h, a ] = list.back();
		for( int j = 0; j < 10; j ++ ) {
			const Hash p = fib(a + j).first;
			const Hash q = p - h;
			res += mp[q];
		}
		mp[cur] ++;
	}
	printf( "%" PRId64 "\n", res );
}
