/*
 * 2.cpp 2024-08-09
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
  //

const int N = 1e5 + 1e4;

const int M = 2e6 + 1e5;

int a[N], b[N];

ModInt<mod> f[N][2], fact[M], ifac[M];

void init() {
	fact[0] = 1;
	for( int i = 1; i < M; i ++ ) 
		fact[i] = fact[ i - 1 ] * i;
	ifac[ M - 1 ] = 1 / fact[ M - 1 ];
	for( int i = M - 2; i >= 0; i -- ) 
		ifac[i] = ifac[ i + 1 ] * ( i + 1 );
}

// choose m in n
ModInt<mod> choose( ci32 n, ci32 m ) { 
	if( n < 0 || m < 0 || n < m )
		return 0;
	return fact[n] * ifac[m] * ifac[n - m]; 
}

ModInt<mod>	solve( ci32 x, ci32 y ) { return choose( x + y + 1, x + 1 ); }

ModInt<mod>	solve_end( ci32 x, ci32 y ) { 
	return ( ( x + 2 ) * choose( x + y + 2, x + 2 ) - y - 1 ) / ( y + 1 ); 
}

int main() {
#ifdef woshiluo
	freopen( "2.in", "r", stdin );
	freopen( "2.out", "w", stdout );
#endif
	init();

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
			b[i] = read<i32>();
		}
		f[0][0] = f[0][1] = 1;
		ModInt<mod> ans = 1;
		for( int i = 1; i <= n; i ++ ) {
			f[i][0] = f[i][1] = 0;
			if( a[i] ) {
				f[i][0] += f[ i - 1 ][0] * solve( a[i] - 1, b[i] );
				f[i][1] += f[ i - 1 ][0] * solve( b[i], a[i] - 1 );
				ans += f[ i - 1 ][0] * solve_end( a[i] - 1, b[i] );
			}
			else {
				f[i][0] += f[ i - 1 ][0];
			}


			if( b[i] ) {
				f[i][0] += f[ i - 1 ][1] * solve( a[i], b[i] - 1 );
				f[i][1] += f[ i - 1 ][1] * solve( b[i] - 1, a[i] );
				ans += f[ i - 1 ][1] * solve_end( a[i], b[i] - 1 );
			}
			else {
				f[i][1] += f[ i - 1 ][1];
			}
		}

		ans.output();
	}
}
