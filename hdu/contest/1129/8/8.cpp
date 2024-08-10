/*
 * 8.cpp 2024-08-05
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

const int N = 3e5 + 1e4;
const int K = 50;

const uint64_t mod1 = 100000000000000013LL;
const uint64_t mod2 = 100000000000000099LL;

template<i64 P>
struct ModInt {// {{{
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

    constexpr ModInt& operator*=(const ModInt &rhs) & { x = (((__int128)x) * rhs.x) % get_mod(); return *this; }
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
//	void output( const char end = '\n' ) { printf( "%" PRId32"%c", x, end ); }
};// }}} 

int ss[N][2], st[N][2];

struct HashMod {
	ModInt<mod1> p1;
	ModInt<mod2> p2;

	HashMod() { }
	HashMod(i32 cur) { p1 = cur, p2 = cur; }

	HashMod& operator+=( const HashMod &_b ) { p1 += _b.p1; p2 += _b.p2; return *this; }
	HashMod& operator-=( const HashMod &_b ) { p1 -= _b.p1; p2 -= _b.p2; return *this; }
	HashMod& operator*=( const HashMod &_b ) { p1 *= _b.p1; p2 *= _b.p2; return *this; }
	
    friend HashMod operator*(const HashMod& lhs, const HashMod& rhs) { HashMod res = lhs; res *= rhs; return res; }
    friend HashMod operator+(const HashMod& lhs, const HashMod& rhs) { HashMod res = lhs; res += rhs; return res; }
    friend HashMod operator-(const HashMod& lhs, const HashMod& rhs) { HashMod res = lhs; res -= rhs; return res; }

	bool operator== ( const HashMod &_b ) const { return p1 == _b.p1 && p2 == _b.p2; }
};

HashMod pre[N], pow_3[N];
i32 valid[N], list[N];
void dfs_s(ci32 cur, ci32 dep, const HashMod tar, ci32 len ) {
	list[dep] = cur;
	valid[cur] = 0;
	if( dep >= len ) {
		const HashMod hash = pre[cur] - pre[ list[dep - len] ] * pow_3[len];
		if( hash == tar ) {
			valid[ list[ dep - len ] ] = cur;
		}
	}
	for( int k = 0; k < 2; k ++ ) {
		if( ss[cur][k] == 0 ) 
			continue;
		ci32 to = ss[cur][k];
		pre[to] = pre[cur] * 3 + k;
		dfs_s( to, dep + 1, tar, len );
	}
}

int id_cnt;
int top[N], dir[N], hlen[N], nxt[N][2], id[N], dep[N];
HashMod hs[N];
void dfs_t( ci32 cur, ci32 depth ) {
	dep[cur] = depth;
	list[depth] = cur;
	i32 son_cnt = 0;
	for( int k = 0; k < 2; k ++ ) {
		if( st[cur][k] == 0 ) 
			continue;
		son_cnt ++;
	}
	if( cur == 0 || son_cnt == 0 || son_cnt == 2 ) {
		id_cnt ++;
		id[cur] = id_cnt;
		nxt[ id[cur] ][0] = nxt[ id[cur] ][1] = 0;

		if( cur != 0 ) {
			nxt[ id[ top[cur] ] ][ dir[ top[cur] ] ] = id[cur];
			hlen[ id[cur] ] = dep[cur] - dep[ top[cur] ];
			hs[ id[cur] ] = pre[cur] - pre[ top[cur] ] * pow_3[ hlen[ id[cur] ] ];
		}

		top[cur] = cur;
	}
	for( int k = 0; k < 2; k ++ ) {
		if( st[cur][k] == 0 ) 
			continue;
		ci32 to = st[cur][k];
		dir[cur] = k;
		top[to] = top[cur];
		pre[to] = pre[cur] * 3 + k;
		dfs_t( to, depth + 1 );
	}
}

int f[N][K];

bool check( ci32 cur, ci32 p ) {
	bool flag = true;
	for( int k = 0; k < 2; k ++ ) {
		if( nxt[p][k] == 0 ) 
			continue;
		if( f[cur][ nxt[p][k] ] == 0 ) 
			return false;
		flag = ( flag && check( f[cur][ nxt[p][k] ], nxt[p][k] ) );
	}
	return flag;
}

int main() {
#ifdef woshiluo
	freopen( "8.in", "r", stdin );
	freopen( "8.out", "w", stdout );
#endif

	pow_3[0] = 1;
	for( int i = 1; i < N; i ++ ) {
		pow_3[i] = pow_3[ i - 1 ] * 3u;
	}

	i32 T = read<i32>();
	while( T -- ) {
		id_cnt = 0;
		ci32 n = read<i32>();
		for( int i = 0; i < n; i ++ ) {
			ss[i][0] = read<i32>();
			ss[i][1] = read<i32>();
		}
		ci32 m = read<i32>();
		for( int i = 0; i < m; i ++ ) {
			st[i][0] = read<i32>();
			st[i][1] = read<i32>();
		}

		dfs_t( 0, 0 );
		for( int i = 2; i <= id_cnt; i ++ ) {
			dfs_s( 0, 0, hs[i], hlen[i] );
			for( int cur = 0; cur < n; cur ++ ) {
				if( valid[cur] != 0 ) {
					f[cur][i] = valid[cur];
					valid[cur] = 0;
				}
				else 
					f[cur][i] = 0;
			}
		}

		std::vector<i32> rts;
		for( int i = 0; i < n; i ++ ) {
			if( check( i, 1 ) ) 
				rts.push_back(i);
		}

		printf( "%zu\n", rts.size() );
		for( auto &x: rts ) 
			printf( "%d ", x );
		printf( "\n" );
	}
}
