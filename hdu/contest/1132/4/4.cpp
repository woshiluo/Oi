/*
 * 4.cpp 2024-08-16
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

using i128 = __int128;
using u128 = unsigned __int128;
using ci128 = const i128;
using cu128 = const u128;

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

struct Card {
	int id;
	int type;
	// 1
	// 2
	// 3
	i32 x, k, cnt;
	i64 base_h, h;
	bool alive;

	bool operator< ( const Card &_b ) const {
		return h > _b.h;
	}
};

void write_out( i128 res ) {
	if( res == 0 ) {
		printf( "0" );
		return ;
	}
	static int buf[64], cnt;
	cnt = 0;
	while( res ) {
		cnt ++;
		buf[cnt] = res % 10;
		res /= 10;
	}
	for( int i = cnt; i >= 1; i -- ) 
		printf( "%d", buf[i] );
}

int main() {
#ifdef woshiluo
	freopen( "4.in", "r", stdin );
	freopen( "4.out", "w", stdout );
#endif


	i32 T = read<i32>();

	while( T -- ) {
		ci32 n = read<i32>();

		std::vector<Card> cards( n + 1 );
		std::priority_queue<Card> live;

		int cnt_3 = 0;
		for( int i = 1; i <= n; i ++ ) {
			cards[i].id = i;
			cards[i].cnt = 0;
			cards[i].alive = true;
			cards[i].type = read<i32>();
			if( cards[i].type == 1 ) {
				cards[i].h = read<i32>();
			}
			else if( cards[i].type == 2 ) {
				cards[i].h = read<i32>();
				cards[i].base_h = cards[i].h;
				cards[i].x = read<i32>();
				cards[i].k = read<i32>();
			}
			else if( cards[i].type == 3 ) {
				cnt_3 ++;
				cards[i].h = read<i32>();
			}
			if( i != 1 )
				live.push( cards[i] );
		}

		std::queue<i32> dead;
		dead.push(1);
		cards[1].alive = false;
		if( cards[1].type == 3 ) 
			cnt_3 --;

		i64 base = 0;
		while( !dead.empty() ) {
			ci32 cur = dead.front(); dead.pop();
			auto &card = cards[cur];
			card.alive = false;
			if( card.type == 1 ) {
				std::vector<i32> list;
				ci32 ata = cnt_3 + 1;
				base += ata;
				while( !live.empty() && live.top().h <= base ) {
					list.push_back( live.top().id ); live.pop();
				}
				std::sort( list.begin(), list.end() );
				for( auto &x: list ) {
					if( cards[x].type == 3 ) 
						cnt_3 --;
					dead.push(x);
				}
			}
			if( card.type == 2 ) {
				if( card.x == 0 )
					continue;
				card.alive = true;
				card.x --;
				card.cnt ++;
				card.base_h *= 2;
				card.h = card.base_h + base;
				live.push(card);
			}
			if( card.type == 3 ) {
				continue;
			}
		}

		for( int i = 1; i <= n; i ++ ) {
			const auto &card = cards[i];
			if( card.type == 1 || card.type == 3 ) {
				if( !card.alive ) 
					printf( "0\n" );
				else 
					printf( "%" PRId64 "\n", card.h - base );
			}
			else {
				if( !card.alive )
					printf( "0 0 0\n" );
				else {
					write_out( pow( (i128)card.k, card.cnt ) );
					printf( " %d %" PRId64 "\n",  card.x, card.h - base );
				}
			}
		}
	}
}
