/*
 * g.cpp 2024-10-04
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
#include <cassert>
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ( ch - '0' );
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

const i32 mod = 500501;

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

const int N = 1e5 + 1e4;

struct Edge {
	i32 to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

ModInt<mod> f[N][2];

void dfs( ci32 cur, ci32 la ) {
	ModInt<mod> pro = 1;
	std::vector<std::pair<ModInt<mod>, ModInt<mod>>> list;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		dfs( to, cur );
		list.emplace_back( f[to][0], f[to][1] );
	}
	f[cur][0] = f[cur][1] = pro;
	ci32 size = list.size();
	if( size == 0 ) 
		return ;
	std::vector<ModInt<mod>> g[3];
	g[0].resize(size); g[1].resize(size); g[2].resize(size);
	g[0][0] = list[0].first + list[0].second;
	g[0][1] = list[0].first + list[0].second;
	g[0][2] = 0;
	for( int i = 1; i < size; i ++ ) {
		g[i][0] = g[ i - 1 ][0] * ( list[i].first + list[i].second );
		g[i][1] = g[ i - 1 ][1] * list[i].first;
		g[i][1] += g[ i - 1 ][0] * list[i].second;
		
		g[i][2] = g[ i - 1 ][2] * list[i].first;
		g[i][2] = g[ i - 1 ][1] * list[i].second;
	}

	f[cur][0] = g[0].back() + g[2].back();
	f[cur][1] = g[1].back();
}

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	i32 n = read<i32>();
	for( int i = 1; i < n; i ++ ) {
		ci32 u = read<i32>();
		ci32 v = read<i32>();
		add_edge( u, v );
		add_edge( v, u );
	}
	
	dfs( 1, 0 );

	f[1][0].output();
}
