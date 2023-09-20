/*
 * gym.cpp
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
#include <queue>
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

const int N = 1e5 + 1e4;

struct Segment { int left, rig, kind; };

std::vector<Segment> ori[N], segs;

void gg() {
	printf( "GG\n" );

	fclose(stdin);
	fclose(stdout);
	std::exit(0);
}

int main() {
	freopen( "gym.in", "r", stdin );
	freopen( "gym.out", "w", stdout );


	int n, k;
	n = read<int>(); k = read<int>();
	{
		int num = 0;
		std::map<int, int> mp;
		for( int i = 1; i <= n; i ++ ) {
			int l, r, p;
			l = read<int>(); r = read<int>(); p = read<int>();
			if( mp.count(p) == 0 ) {
				num ++;
				mp[p] = num;
			}
			p = mp[p];
			ori[p].push_back( (Segment) { l, r, p } );
		}
		k = num;
	}
	for( int i = 1; i <= k; i ++ ) {
		if( ori[i].size() == 0 ) 
			continue;
		std::sort( ori[i].begin(), ori[i].end(), []( const Segment &_a, const Segment &_b ) { return _a.rig > _b.rig; } );
		std::priority_queue<int> q;
		int p = 0, st = ori[i][0].rig, size = ori[i].size();
		while( st >= 0 ) {
			if( !q.empty() && q.top() > st ) 
				gg();
			if( p >= size && q.empty() ) 
				break;
			if( q.empty() ) 
				st = ori[i][p].rig;
			while( p < size && ori[i][p].rig >= st ) {
				q.push( ori[i][p].left );
				p ++;
			}
			segs.push_back( (Segment){ q.top(), st, i } ); q.pop();
			st --;
		}
	}


	std::vector<int> nums;
	for( auto &seg: segs ) {
		nums.push_back(seg.left);
		nums.push_back(seg.rig);
	}
	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );

	auto find = [&nums]( const int cur ) { return std::lower_bound( nums.begin(), nums.end(), cur ) - nums.begin() + 1; };
	for( auto &seg: segs ) {
		seg.left = find( seg.left );
		seg.rig = find( seg.rig );
	}

	std::sort( segs.begin(), segs.end(), []( const Segment &_a, const Segment &_b ) { return _a.left < _b.left; } );
	int max_t = nums.size();
	{
		std::priority_queue<int, std::vector<int>, std::greater<int>> wait[N];
		std::map<int, bool> mp;
		int p = 0, size = segs.size(), res = 0;
		static int sum[N];

		auto add = [&]( const int kind, const int rig ) {
			if( wait[kind].size() == 0 ) 
				mp[kind] = true;
			wait[kind].push(rig);
			sum[rig] ++;
		};
		auto del = [&]() {
			res ++;
			std::vector<int> list;
			for( auto &node: mp ) 
				list.push_back( node.first );
			for( auto &kind: list ) {
				sum[ wait[kind].top() ] --;
				wait[kind].pop();
				if( wait[kind].size() == 0 ) 
					mp.erase(kind);
			}
		};
		for( int t = 1; t <= max_t; t ++ ) {
			while( p < size && segs[p].left <= t ) {
				add( segs[p].kind, segs[p].rig );
				p ++;
			}
			if( sum[t] != 0 ) {
				del();
			}
		}

		if( mp.size() != 0 ) 
			res ++;

		printf( "%d\n", res );
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
