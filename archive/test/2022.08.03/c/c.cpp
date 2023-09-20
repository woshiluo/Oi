/*
 * c.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
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
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 1e6 + 1e5;
const int Q = 110;

struct Edge { cint from, to; };
struct Change { cint id, val; };
std::vector<Edge> edges[N], bases;
 
std::vector<int> primes;
int min_prime[N], mu[N], val[N];
bool is_prime[N];

void pre() {/*{{{*/
	memset( is_prime, true, sizeof(is_prime) );

	mu[1] = 1;
	for( int i = 2; i < N; i ++ ) {
		if( is_prime[i] ) {
			primes.push_back(i);
			min_prime[i] = i;
			mu[i] = -1;
		}
		for( auto &p: primes ) {
			if( 1LL * p * i >= N ) 
				break;

			cint nxt = p * i;
			is_prime[nxt] = false;
			min_prime[nxt] = Min( min_prime[i], p );
			mu[nxt] = -mu[i];

			if( i % p == 0 ) {
				mu[nxt] = 0;
				break;
			}
		}
	}
}/*}}}*/

int fa[N], size[N];
int get_fa( cint cur ) {
	if( fa[cur] == cur ) 
		return fa[cur];
	return get_fa( fa[cur] );
}

int full_pow( cint cur ) { return 1 << cur; } 
bool chk_pos( cint cur, cint pos ) { return cur & full_pow(pos); }

void add_edge( const Edge &edge, std::vector<int> &list ) {
	cint tot = list.size();

	for( int i = 0; i < full_pow(tot); i ++ ) {
		int cur = 1;
		for( int j = 0; j < tot; j ++ ) {
			if( chk_pos( i, j ) ) {
				cur *= list[j];
			}
		}
		edges[cur].push_back(edge);
	}
}


int changed[Q][Q], ori_id[N];
std::map<int, int> change_id;
std::vector<int> impo[N];
ll ans[Q];

std::vector<int> get_list( int cur ) {
	std::vector<int> list;
	for( ; cur != 1; ) {
		cint k = min_prime[cur];
		list.push_back(k);
		while( cur % k == 0 ) 
			cur /= k;
	}

	return list;
}

void add_impo( cint cur, std::vector<int> &list ) {
	cint tot = list.size();
	for( int i = 0; i < full_pow(tot); i ++ ) {
		int res = 1;
		for( int j = 0; j < tot; j ++ ) {
			if( chk_pos( i, j ) ) {
				res *= list[j];
			}
		}

		impo[res].push_back(cur);
	}
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	pre();
	cint n = read<int>();

	for( int i = 1; i < n; i ++ ) {
		cint u = read<int>();
		cint v = read<int>();
		cint w = read<int>();

		val[ i - 1 ] = w;
		bases.push_back( { u, v } );
	}

	cint q = read<int>();

	for( int i = 1; i <= q; i ++ ) {
		cint x = read<int>() - 1;
		cint w = read<int>();

		if( change_id.count(x) == 0 ) {
			change_id[x] = change_id.size() + 1;
			ori_id[ change_id[x] ] = x;
		}

		cint p = change_id[x];

		changed[0][p] = val[x];
		changed[i][p] = w;

		auto list = get_list(w);
		add_impo( x, list );
	}

	for( int i = 1; i <= q; i ++ ) {
		for( int j = 1; j <= q; j ++ ) {
			if( changed[i][j] == 0 ) 
				changed[i][j] = changed[ i - 1 ][j];
		}
	}

	for( int i = 0; i < n - 1; i ++ ) {
		cint u = bases[i].from;
		cint v = bases[i].to;
		cint w = val[i];

		auto list = get_list(w);
		if( change_id.count(i) ) 
			add_impo( i, list );
		else
			add_edge( { u, v }, list );
	}

	for( int i = 0; i < N; i ++ ) {
		fa[i] = i;
		size[i] = 1;
	}
	for( int i = 1; i < N; i ++ ) {
		if( mu[i] == 0 )
			continue;

		struct Op { cint x, y; };
		std::vector<Op> ops;
		ll res = 0;

		auto get_res = [] ( cint cur ) { return 1LL * cur * ( cur - 1 ); };/*{{{*/
		auto merge = [&] ( cint cur, cint to ) {
			int fcur = get_fa(cur), fto = get_fa(to);
			if( fcur == fto )
				return ;
			if( size[fcur] < size[fto] ) 
				std::swap( fcur, fto );

			ops.push_back( { fcur, fto } );

			res -= get_res( size[fcur] );
			res -= get_res( size[fto] );

			size[fcur] += size[fto];
			fa[fto] = fcur;

			res += get_res( size[fcur] );
		};
		auto rollback = [&]( Op cur ) {
			cint x = cur.x;
			cint y = cur.y;

			res -= get_res( size[x] );

			size[x] -= size[y];
			fa[y] = y;

			res += get_res( size[x] );
			res += get_res( size[y] );
		};
		auto reset = [] ( cint cur ) {
			fa[cur] = cur;
			size[cur] = 1;
		};/*}}}*/

		for( auto &e: edges[i] ) {
			merge( e.from, e.to );
		}

		std::sort( impo[i].begin(), impo[i].end() );
		impo[i].erase( std::unique( impo[i].begin(), impo[i].end() ), impo[i].end() );
		cint st = ops.size();
		for( int time = 0; time <= q; time ++ ) {
			for( auto &cur: impo[i] ) {
				if( changed[time][ change_id[cur] ] % i == 0 )
					merge( bases[cur].from, bases[cur].to );
			}
			ans[time] += 1LL * mu[i] * res;
			while( (int)ops.size() != st ) {
				rollback( ops.back() );
				ops.pop_back();
			}
		}

		for( auto &e: edges[i] ) {
			reset( e.from );
			reset( e.to );
		}
	}

	for( int i = 0; i <= q; i ++ ) {
		printf( "%lld\n", ans[i] >> 1 );
	}
}
