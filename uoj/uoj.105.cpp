#include <cstdio>

#include <vector>
#include <algorithm>

inline int Max( int _a, int _b ) { return _a > _b? _a: _b; }
inline void chk_Max( int &_a, int _b ) { _a = ( _a > _b? _a: _b ); }

const int N = 2e5 + 1e4;
const int INF = 0x3f3f3f3f;

int n, ans;
int f[N][2];

// Edge Start {{{{
struct edge {
	int to, val, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int now, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// } Edge End}}}

void dp( int cur, int la ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dp( e[i].to, cur );
		int res = Max( f[ e[i].to ][0], f[ e[i].to ][1] + e[i].val );
		f[cur][0] += res;
	}
	bool flag = false;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		flag = true;
		chk_Max( f[cur][1], f[cur][0] - Max( f[ e[i].to ][1] + e[i].val, f[ e[i].to ][0] ) + f[ e[i].to ][0] + e[i].val );
	}
	if( flag == false ) 
		f[cur][1] = -INF;
}

void chk_rt( int cur, int la, int la_f[], int edge_val ) {
	std::vector<int> max, re_max;
	max.push_back(0), re_max.push_back(0);
	int tmp[2];
	int p1 = 1;
	tmp[0] = f[cur][0], tmp[1] = f[cur][1];
	if( la != 0 ) {
		p1 ++;
		int res = Max( la_f[0], la_f[1] + edge_val );
		tmp[0] += res;
		res = - res + la_f[0] + edge_val;
		chk_Max( tmp[1], tmp[0] + res );
		max.push_back(res), re_max.push_back(res);
	}
	chk_Max( ans, tmp[0] );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		int res = - Max( f[ e[i].to ][1] + e[i].val, f[ e[i].to ][0] ) + f[ e[i].to ][0] + e[i].val;
		max.push_back(res), re_max.push_back(res);
	}
	int cnt = max.size(); cnt --;
	for( int i = 2; i <= cnt; i ++ ) {
		chk_Max( max[i], max[ i - 1 ] );
	}
	for( int i = cnt - 1; i >= 1; i -- ) {
		chk_Max( re_max[i], re_max[ i + 1 ] );
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		int cur_f[2] = { tmp[0] - Max( f[ e[i].to ][0], f[ e[i].to ][1] + e[i].val ), 0 };
		if( cnt == 1 ) 
			cur_f[1] = -INF;
		else if( p1 == 1 ) 
			cur_f[1] = cur_f[0] + re_max[ p1 + 1 ];
		else if( p1 == cnt ) 
			cur_f[1] = cur_f[0] + max[ p1 - 1 ];
		else
			cur_f[1] = cur_f[0] + Max( max[ p1 - 1 ], re_max[ p1 + 1 ] );
		p1 ++;
		chk_rt( e[i].to, cur, cur_f, e[i].val );
	}
}

int main() {
#ifdef woshiluo
	freopen( "uoj.105.in", "r", stdin );
	freopen( "uoj.105.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1, u, v, w; i < n; i ++ ) {
		scanf( "%d%d%d", &u, &v, &w );
		add_edge( u, v, w );
		add_edge( v, u, w );
	}
	int rt = ( n / 2 ) + 1;
//	int rt = 8;

	int tmp[2] = { 0, 0 };
	dp( rt, 0 );
	chk_rt( rt, 0, tmp, 0 );

	printf( "%d\n", ans );
}
