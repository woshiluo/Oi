/*
 * k.cpp 2024-10-03
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cinttypes>

#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
constexpr T pow( T a, i64 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const i32 mod = 1e9 + 7;

template<i32 P>
struct ModInt {// {{{
    i32 x;
    constexpr ModInt() : x {0} {}
    constexpr ModInt(i64 _x) : x {norm(_x % get_mod())} {}
    
    static i32 mod;

    constexpr static i32 get_mod() { return P > 0? P: mod; }
    constexpr static void set_mod(i32 _mod) { mod = _mod; }

    static constexpr i32 norm(i32 x) {
        if (x < 0) {
            x += get_mod();
        }
        if (x >= get_mod()) {
            x -= get_mod();
        }
        return x;
    }
    constexpr i32 val() const { return x; }
    constexpr ModInt operator-() const {
        ModInt res;
        res.x = norm(get_mod() - x);
        return res;
    }

    constexpr ModInt inv() const { return pow(*this, get_mod() - 2); }

    constexpr ModInt& operator*=(const ModInt &rhs) & { x = (((i64)x) * rhs.x) % get_mod(); return *this; }
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
	void output( const char end = '\n' ) { printf( "%" PRId32 "%c", x, end ); }
};// }}} 

int main() {
#ifdef woshiluo
	freopen( "k.in", "r", stdin );
	freopen( "k.out", "w", stdout );
#endif

	ci64 n = read<i64>();
	ci64 k = read<i64>();

	ci64 base = n / k;
	ci64 less = n % k;

	ModInt<mod> res = 0;
	res += pow( (ModInt<mod>)2, base ) * ( k - less );
	res += pow( (ModInt<mod>)2, base + 1 ) * less;

	res.output();
}
