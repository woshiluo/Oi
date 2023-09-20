/*
 * t1.cpp
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

#include <vector>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;
typedef const ll cll;

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
T pow( T a, ll p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const ll N = 1e6 + 1e5;

ll ori_s[N], ori_t[N];
ll ss[N], st[N];

void read_01( ll ori[], ll sum[] ) {
	static char str[N];
	scanf( "%s",  str + 1 );
	ll len = strlen( str + 1 );
	for( ll i = 1; i <= len; i ++ ) 
		ori[i] = ( str[i] - '0' );
	for( ll i = 1; i <= len; i ++ ) 
		sum[i] = sum[ i - 1 ] + ori[i];
}


struct Vec {
	ll x, y;

	Vec operator- ( const Vec &_b ) const { return (Vec) { _b.x - x, _b.y - y }; }
	ll operator* ( const Vec &_b ) const { return 1LL * x * _b.y - 1LL * y * _b.x; }
	ll dot( const Vec &_b ) const { return 1LL * x * _b.x + 1LL * y * _b.y; }
};

Vec get_vec( ll sum[], cll l, cll r ) {
	cll len = r - l + 1;
	cll p1 = len - ( sum[r] - sum[ l - 1 ] );
	return (Vec) { len - p1 + 1, p1 + 1 };
}

int main() {
#ifdef woshiluo
	freopen( "t1.in", "r", stdin );
	freopen( "t1.out", "w", stdout );
#endif
	std::vector<Vec> sta;

	read_01( ori_s, ss );
	{
		cll n = read<ll>();
		std::vector<Vec> vecs;
		for( ll i = 1; i <= n; i ++ ) {
			cll l = read<ll>();
			cll r = read<ll>();
			vecs.push_back( get_vec( ss, l, r ) );
		}

		std::sort( vecs.begin(), vecs.end(), []( const Vec &_a, const Vec &_b ) { 
			if( _a.x == _b.x ) 
				return _a.y < _b.y;
			return _a.x < _b.x;
		});

		for( auto &cur: vecs ) {
			if( sta.size() < 2 ) {
				sta.push_back(cur);
				continue;
			}
			while( sta.size() > 1 ) {
				cll size = sta.size() - 1;
				if( ( sta[size - 1] - sta[size] ) * ( sta[size] - cur ) > 0 ) 
					sta.pop_back();
				else
					break;
			}

			sta.push_back(cur);
		}
	}

	read_01( ori_t, st );
	{
		cll m = read<ll>();
		for( ll i = 1; i <= m; i ++ ) {
			cll l = read<ll>();
			cll r = read<ll>();

			Vec cur = get_vec( st, l, r );
			std::swap( cur.x, cur.y );

			ll left = 0, rig = sta.size() - 1, res = 0;

			while( left <= rig ) {
				cll mid = ( left + rig ) >> 1;

				if( sta[mid].dot(cur) > sta[ mid + 1 ].dot(cur) ) {
					res = mid;
					rig = mid - 1;
				}
				else
					left = mid + 1;
			}

			printf( "%lld\n", sta[res].dot(cur) - 1 );
		}
	}
}
