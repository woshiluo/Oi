#include <cstdio>

#include <vector>
#include <algorithm>

template<class T>
T Min( T a, T b ) { return a < b? a: b; }
template<class T>
T Max( T a, T b ) { return a > b? a: b; }
template<class T>
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T>
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

const int N = 5e5 + 1e4;

int m, T;
struct node { int mon, cos; };
std::vector<node> a[N];
int n[N], s[N];

bool cmp( node _a, node _b ) {
	return _a.mon > _b.mon;
}

namespace sub3 {
	void calc() {
		long long res_cos = 0, res_mon = 0;
		std::vector<node> lst;
		for( int i = 1; i <= m; i ++ ) {
			std::sort( a[i].begin(), a[i].end(), cmp );
			int size = a[i].size();
			long long res = 0;
			for( int j = 0; j < size; j ++ ) {
				if( res >= s[i] ) {
					lst.push_back( a[i][j] );
				}
				else {
					res += a[i][j].mon;
					res_cos += a[i][j].cos;
				}
			}
			if( res < s[i] ) {
				printf( "-1\n" );
				return ;
			}
			res_mon += res;
		}
		int size = lst.size();
		int p = 0;
		while( res_mon < T && p < size ) {
			res_mon += lst[p].mon;
			res_cos += lst[p].cos;
			p ++;
		}
		if( res_mon < T )
			printf( "-1\n" );
		else
			printf( "%lld\n", res_cos );
	}
}

namespace sub_bf {
	long long rule[30][30];
	int hash( int x, int y ) {
		int res = 0;
		for( int i = 1; i < x; i ++ ) {
			res += n[i];
		}
		res += y - 1;
		return res;
	}
	void calc() {
		long long ans = ( 1LL << 60LL );
		int sum_n = 0;
		for( int i = 1; i <= m; i ++ ) 
			sum_n += n[i];
		
		int p;
		scanf( "%d", &p );
		while( p -- ) {
			int op, x1, x2, y1, y2;
			long long c;
			scanf( "%d%d%d%d%d", &op, &x1, &y1, &x2, &y2 );
			if( op == 1 || op == 2 )
				scanf( "%lld", &c );
			if( op == 1 ) 
				c = -c;
			if( op == 3 ) 
				c = -ans;
			rule[ hash( x1, y1 ) ][ hash( x2, y2 ) ] = c;
		}

		for( int k = 0; k < ( 1 << sum_n ); k ++ ) {
			int cnt = 0;
			long long tmp_res_cos = 0, tmp_res_mon = 0;
			for( int i = 1; i <= m; i ++ ) {
				for( int j = 0; j < n[i]; j ++ ) {
					if( k & ( 1 << cnt ) ) {
						tmp_res_cos += a[i][j].cos;
						tmp_res_mon += a[i][j].mon;
					}
					cnt ++;
				}
			}
			for( int i = 0; i < sum_n; i ++ ) {
				for( int j = 0; j < sum_n; j ++ ) {
					if( ( k & ( 1 << i ) ) && ( k & ( 1 << j ) ) ) {
						tmp_res_mon += rule[i][j];
					}
				}
			}
			if( tmp_res_mon > T ) 
				chk_Min( ans, tmp_res_cos );
		}

		if( ans == ( 1LL << 60LL ) ) 
			printf( "%d\n", -1 );
		else 
			printf( "%lld\n", ans );
	}
}

int main() {
	freopen( "courses.in", "r", stdin );
	freopen( "courses.out", "w", stdout );

	int sum_T = 0;
	scanf( "%d%d", &m, &T );
	bool flag_sub_3 = true;
	int sum_n = 0;
	for( int i = 1; i <= m; i ++ ) {
		scanf( "%d%d", &n[i], &s[i] );
		sum_n += n[i];
		for( int j = 0; j < n[i]; j ++ ) {
			int t1, t2;
			scanf( "%d%d", &t1, &t2 );
			if( t1 != 1 ) 
				flag_sub_3 = false;
			// t1 = mon
			// t2 = cos

			a[i].push_back((node){t1, t2});
			sum_T += t1;
		}
	}

	if( sum_T < T ) {
		printf( "-1\n" );
		return 0;
	}

	if( flag_sub_3 ) 
		sub3::calc();
	else 
		sub_bf::calc();

	fclose( stdin );
	fclose( stdout );
	return 0;
}
