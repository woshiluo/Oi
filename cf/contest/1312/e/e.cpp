// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/10 15:50:48 
#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 510;

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

int n;
int a[N];
int f[N][N], merged[N][N];

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		f[i][i] = 1;
		merged[i][i] = a[i];
	}
	for( int len = 2; len <= n; len ++ ) {
		for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
			f[left][rig] = rig - left + 1;
			for( int mid = left; mid < rig; mid ++ ) {
				int &f_left = f[left][mid], &f_rig = f[ mid + 1 ][rig],
				&merge_left = merged[left][mid], &merge_rig = merged[ mid + 1 ][rig];
				chk_Min( f[left][rig], f_left + f_rig );
				if( f_left == 1 && f_rig == 1 && merge_left == merge_rig ) {
					f[left][rig] = 1;
					merged[left][rig] = merge_left + 1;
				}
			}
		}
	}
	printf( "%d\n", f[1][n] );
}
