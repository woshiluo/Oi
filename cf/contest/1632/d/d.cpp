/*
 * d.cpp
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

int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

struct Segment {
	int left, rig;
	bool operator< ( const Segment &_b ) const {
		return this -> left < _b.left;
	}
};

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	std::map<Segment, int> mp;
	int n = read<int>(), cnt = 0;
	for( int i = 1; i <= n; i ++ ) {
		{
			std::vector<std::pair<Segment,int>> list;
			for( auto &pair: mp) {
				list.push_back(pair);
			}
			int size = list.size();
			for( int k = 0; k < size; k ++ ) {
				int p = k;
				while( p + 1 < size && list[ p + 1 ].second == list[p].second )
					p ++;
				if( p == k ) 
					continue;
				auto tmp = list[k];
				tmp.first.rig = list[p].first.rig;
				for( int j = k; j <= p; j ++ ) 
					mp.erase(list[j].first);
				mp.insert(tmp);
			}
		}
		int tmp = read<int>();
		bool flag = false;
		std::vector<Segment> erase_list;
		mp.insert( std::make_pair( (Segment){ i, i }, tmp ) );
		for( auto &pair: mp ) {
			pair.second = gcd( pair.second, tmp );
			if( i - pair.first.rig + 1 <= pair.second && pair.second <= i - pair.first.left + 1 ) {
				flag = true;
				break;
			}
			if( pair.second <= i - pair.first.rig + 1 ) 
				erase_list.push_back(pair.first);
		}
		if( !flag ) {
			for( auto &item: erase_list ) {
				mp.erase(item);
			}
		}
		else {
			mp.clear();
		}
		cnt += flag;
		printf( "%d ", cnt );
	}
}
