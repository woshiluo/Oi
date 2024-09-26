/*
 * d.cpp 2024-09-25
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

#include <functional>
#include <queue>
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
  
const i32 P = 128;
  
struct Matrix {
	ModInt<mod> a[P][P];
	Matrix( ci32 cur = 1 ) {
		memset( a, 0, sizeof(a) );
		if( cur ) 
			for( int i = 0; i < P; i ++ ) 
				a[i][i] = cur;
	}
	Matrix operator*( const Matrix &_b ) const {
		Matrix res(0);
		for( int i = 0; i < P; i ++ ) 
			for( int j = 0; j < P; j ++ ) 
				for( int k = 0; k < P; k ++ ) {
					res.a[i][k] += a[i][j] * _b.a[j][k];
				}
		return res;
	}
};

const i32 K = 62;
const i32 BK = 7;

i32 list[K][512];

i32 lowbit( ci32 cur ) { return cur & ( -cur ); }

std::vector<ModInt<mod>> bfs( ci32 cur ) {
	std::vector<ModInt<mod>> res(256);
	std::vector<bool> vis(256, false);
	std::priority_queue<i32> q;
	q.push(cur); res[cur] = 1; vis[cur] = 1;

	while( !q.empty() ) {
		ci32 p = q.top(); q.pop();
		i32 tmp = p << 1;
		for( i32 k = 0; k < K && ( tmp & 1 ) == 0; k ++, tmp >>= 1 ) {
			for( int a = 0; a < 128; a ++ ) {
				if( p - a < 0 )
					continue;
				res[ p - a ] += res[p] * list[k][a];
				if( !vis[ p - a ] ) {
					vis[ p - a ] = true;
					q.push( p - a );
				}
			}
		}
	}
	return res;
}

Matrix q[K];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	ci64 n = read<i64>();
	ci32 m = read<i32>();
	for( int i = 1; i <= m; i ++ ) {
		ci32 a = read<i32>();
		ci32 b = read<i32>();
		list[b][a] ++;
	}
	Matrix base_p = 0, base_q = 0;
	for( int i = 128; i < 256; i ++ ) {
		const auto l1 = bfs(i);
		for( int j = 0; j < 128; j ++ ) {
			base_p.a[ i - 128 ][j] += l1[ j + 128 ];
		}
		{
			i32 tmp = i << 1;
			for( i32 k = 0; k < K && ( tmp & 1 ) == 0; k ++, tmp >>= 1 ) {
				for( int a = 0; a < 128; a ++ ) {
					if( i - a < 128 ) {
						base_q.a[i - 128][ i - a ] += list[k][a];
					}
				}
			}
		}
	}

	q[0] = base_q;
	for( int i = 1; i <= BK; i ++ ) 
		q[i] = q[ i - 1 ];
	for( int k = BK + 1; k < K; k ++ ) {
		q[k] = q[ k - 1 ];
		for( int a = 0; a < 128; a ++ ) {
			q[k].a[0][ 128 - a ] += list[k][a];
		}
	}

	Matrix a(0);
	a.a[0][n & 127] = 1;

	Matrix full = 1, less = 1;
	for( int k = BK; k < K; k ++ ) {
		less = less * full;
		full = base_p * q[k] * less;
		if( ( n >> k ) & 1LL ) {
			a = a * full;
		}
	}

	a = a * base_p;

	a.a[0][0].output();
}
