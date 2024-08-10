/*
 * 8.cpp 2024-08-09
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
  
const int N = 128;

struct Matrix {
	ModInt<mod> a[N][N];

	Matrix( ci32 cur ) {
		memset( a, 0, sizeof(a) );
		if( cur == 0 ) 
			return ;
		for( int i = 0; i < N; i ++ ) 
			a[i][i] = cur;
	}

	Matrix operator* ( const Matrix &_b ) const {
		Matrix res(0);
		for( int i = 0; i < N; i ++ ) {
			for( int j = 0; j < N; j ++ ) {
				for( int k = 0; k < N; k ++ ) {
					res.a[i][j] += a[i][k] * _b.a[k][j];
				}
			}
		}
		return res;
	}
};

ModInt<mod> f[N][N], g[N];

void dfs( ci32 cur, ci32 n ) {
	if( cur == n - 1 ) 
		return ;
	for( int j = cur + 1; j < n; j ++ ) {
		g[j] += g[cur] * f[cur][j];
	}
	dfs( cur + 1, n );
}

int main() {
#ifdef woshiluo
	freopen( "8.in", "r", stdin );
	freopen( "8.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		ci64 l = read<i64>() - 1;
		ci64 r = read<i64>() - 1;

		Matrix t1(1), t2(0), t3(1), p(0);
		memset( f, 0, sizeof(f) );
		for( int i = 0; i < n; i ++ ) {
			t3.a[n][i] = 1;
		}
		t2.a[n][n] = 1;


		p.a[0][0] = 1;

		for( int i = 1; i <= m; i ++ ) {
			ci32 u = read<i32>() - 1;
			ci32 v = read<i32>() - 1;
			ci32 w = read<i32>();

			if( v < n ) {
				f[u][v] = w;
			}
			else {
				t2.a[ v - n ][u] = w;
			}
		}
		
		for( int s = n - 1; s >= 0; s -- ) {
			g[s] = 1;
			dfs(s, n);
			for( int t = s; t < n; t ++ ) {
				t1.a[t][s] = g[t];
				g[t] = 0;
			}
		}

		p = t1 * p;

		ci64 lb = l / n;
		ci64 rb = r / n;
		ModInt<mod> res = 0;
		if( lb == rb ) {
			p = pow( t1 * t2, lb ) * p;
			for( i64 i = ( l % n ); i <= ( r % n ); i ++ ) {
				res += p.a[i][0];
			}
		}
		else if( rb == lb + 1 ) {
			p = pow( t1 * t2, lb ) * p;
			for( i64 i = ( l % n ); i < n; i ++ ) {
				res += p.a[i][0];
			}
			p = ( t1 * t2 ) * p;
			for( i64 i = 0; i <= ( r % n ); i ++ ) {
				res += p.a[i][0];
			}
		}
		else {
			p = pow( t1 * t2, lb ) * p;
			for( i64 i = ( l % n ); i < n; i ++ ) {
				res += p.a[i][0];
			}
			p = pow( t3 * t1 * t2, rb - lb - 1 ) * p;
			res += p.a[n][0];
			p = ( t1 * t2 ) * p;
			for( i64 i = 0; i <= ( r % n ); i ++ ) {
				res += p.a[i][0];
			}
		}
		res.output();
	}
}
