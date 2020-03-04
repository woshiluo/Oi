#include <cstdio>

inline int Max( int _a, int _b ) { return _a > _b? _a: _b; }

const int N = 2e5 + 1e4;

int n;
int blue_val[N];

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
		dp( e[i].to, now );
		int res = Max( f[ e[i].to ][0], f[ e[i].to ][1] + e[i]. val );
		f[cur][0] += res;
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		chk_Max( f[cur][1], f[cur][0] - Max( f[ e[i].to ][1] + e[i].val, f[ e[i].to ][0] ) + f[ e[i].to ][0] + e[i].val );
	}
}

void chk_rt( int cur, int la, int la_f[], int edge_val ) {
	int cnt = 0, tmp_f[2];
	std::vector sum, re_sum, max, _re_max; 
	sum.push_back(0); re_sum.push_back(0);
	max.push_back(0); re_max.push_back(0);
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		int res = Max( f[ e[i].to ][0], f[ e[i].to ][1] + e[i].val );
		cnt ++;
		sum.push_back(res);
		re_sum.push_back(res);
		res = -res + f[ e[i].to ][0] + e[i].val;
		max.push_back(res);
		re_max.push_back(res);
	}
	for( int i = cnt - 1; i >= 1; i ++ ) {
		re_sum[i] += re_sum[ i + 1 ];
		chk_Max( re_max[i], re_max[ i + 1 ] );
	}
	for( int i = 2; i <= n; i ++ ) {
		sum[i] += sum[ i - 1 ];
		chk_Max( max[i], max[ i + 1 ] );
	}
	tmp_f[0] = f[i][0], tmp_f[1] = f[i][1];
	if( la != 0 ) {
		tmp_f[0] += Max( la_f[0], la_f[1] );
		chk_Max( tmp_f[1], tmp_f[0] - Max( la_f[0], la_f[1] + e[i].val ) + la_f[0] + edge_val );
	}
	ans = Max( ans, Max( tmp_f[1], tmp_f[0] ) );
	int p1 = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		int res = Max( f[ e[i].to ][0], f[ e[i].to ][1] + e[i].val );
		tmp_f[0] -= res;
		tmp_f[1] = Max( max[ i - 1 ], re_max[ i + 1 ] );
		chk_rt( e[i].to, now, tmp_f, e[i].val );
	}
}

int main() {
	scanf( "%d", &n );
	for( int i = 1, u, v, w; i < n; i ++ ) {
		scanf( "%d%d%d", &u, &v, &w );
		add_edge( u, v, w );
		add_edge( v, u, w );
	}
	int rt = ( n / 2 ) + 1;

	dp( rt, 0 );
	chk_rt( rt, 0, int a[2] = [ 0, 0 ] );
}
