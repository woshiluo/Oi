/*
 * d.cpp 2024-08-08
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

const int base[6][5][6] = { // {{{
{},
{{10,0,5,0,0,2},
{0,9,0,4,0,2},
{0,5,8,0,0,2},
{4,0,4,8,0,2},
{2,0,0,0,9,4}},

{{11,0,5,0,0,2},
{0,10,0,4,0,2},
{0,5,9,0,0,2},
{4,0,4,9,0,2},
{2,0,0,0,10,4}},

{{12,0,5,0,0,2},
{0,11,0,4,0,2},
{0,6,10,0,0,2},
{4,0,4,10,0,2},
{3,0,0,0,11,4}},

{{13,0,5,0,0,2},
{0,12,0,4,0,2},
{0,6,11,0,0,2},
{4,0,4,11,0,2},
{3,0,0,0,12,4}},

{{14,0,5,0,0,2},
{0,13,0,4,0,2},
{0,7,12,0,0,2},
{5,0,5,12,0,2},
{4,0,0,0,13,4}} 

};// }}}
  

struct Uma {
	int abi[6];
	int init[6];
	int bonus[6];
	Uma() {
		memset( abi, 0, sizeof(abi) );
		memset( init, 0, sizeof(init) );
		memset( bonus, 0, sizeof(bonus) );
	}
} cur;

struct Card {
	i32 fri, dri, tra;
	int init[6];
	int bonus[6];
	Card() {
		memset( init, 0, sizeof(init) );
		memset( bonus, 0, sizeof(bonus) );
	}
} card[6];

const double coef[] = {  -0.2, -0.1, 0, 0.1, 0.2 };
i32 get_d( ci32 abi_id, ci32 lv, ci32 type, ci32 drive, ci32 weight, const std::vector<std::pair<i32, bool>> &cards ) {
	i32 train_sum = 0;
	i32 dri_sum = 0;
	i32 base_sum = 0;
	double fri_mul = 1;
	for( auto &[x, flag]: cards ) {
		train_sum += card[x].tra;
		dri_sum += card[x].dri;
		base_sum += card[x].bonus[abi_id];
		if( flag )
			fri_mul *= ( (double)card[x].fri * 0.01 + 1.0 );
	}
	ci32 base_p = base[lv][type][abi_id] + base_sum;
	const double fri = fri_mul;
	const double tra = 1.0 + 0.01 * train_sum;
	const double mot = 1.0 + coef[drive] * ( 1.0 + 0.01 * dri_sum );
	const double groth = 1.0 + ( 0.01 * cur.bonus[abi_id] );
	const double sup = 1.0 + ( 0.05 * cards.size() );

	const double d = base_p * fri * tra * mot * groth * sup; 
	// TODO: otheers
	//
	if( weight && abi_id == 0 ) 
		return 0;

	return std::floor(d);
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif


	for( int i = 0; i < 5; i ++ ) {
		cur.init[i] = read<i32>();
	}
	cur.init[5] = 120;
	for( int i = 0; i < 5; i ++ )
		cur.bonus[i] = read<i32>();
	cur.bonus[5] = 0;
	// TODO: set skill+
	
	for( int p = 0; p < 6; p ++ ) {
		card[p].fri = read<i32>();
		card[p].dri = read<i32>();
		card[p].tra = read<i32>();
		for( int i = 0; i < 5; i ++ )
			card[p].init[i] = read<i32>();
		card[p].init[5] = 0;
		for( int i = 0; i < 5; i ++ )
			card[p].bonus[i] = read<i32>();
		card[p].bonus[5] = 0;
	}

	for( int abi_id = 0; abi_id < 6; abi_id ++ ) {
		cur.abi[ abi_id ] += cur.init[ abi_id ];
		for( int p = 0; p < 6; p ++ ) {
			cur.abi[ abi_id ] += card[p].init[ abi_id ];
		}
		chk_Min( cur.abi[ abi_id ], 1200 );
	}

	static int type_cnt[5];
	i32 T = read<i32>();
	while( T -- ) {
		ci32 summer = read<i32>();
		ci32 weight = read<i32>();
		ci32 drive = read<i32>();
		ci32 type = read<i32>();

		ci32 cur_lv = Min( summer? 5: 1 + ( type_cnt[type] / 4 ), 5 );
		ci32 k = read<i32>();
		std::vector<std::pair<i32, bool>> cards(k);
		for( int i = 0; i < k; i ++ ) {
			cards[i].first = read<i32>() - 1;
			cards[i].second = read<i32>();
		}
		for( int abi_id = 0; abi_id < 6; abi_id ++ ) {
			cur.abi[ abi_id ] += get_d( abi_id, cur_lv, type, drive, weight, cards ) ;
			if( abi_id != 5 )
				chk_Min( cur.abi[ abi_id ], 1200 );
		}
		for( int abi_id = 0; abi_id < 6; abi_id ++ ) {
			printf( "%d ", cur.abi[ abi_id ] );
		}

		printf( "\n" );
		if( !summer )
			type_cnt[type] ++;
	}
	
}
