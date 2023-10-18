#include <bitset>
#include <cstdio>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
const int N = 2005;
int n, m;
int s[ N ][ N ];
bitset<N> a[ N ], b[ N ];
vector<tuple<int, int, int>> ans;
int main() {
	ios::sync_with_stdio( false );
	cin.tie( nullptr ), cout.tie( nullptr );
	cin >> n >> m;
	for ( int i = 1; i <= n; i++ ) {
		string str;
		cin >> str;
		for ( int j = 1; j <= m; j++ )
			s[ i ][ j ] = str[ j - 1 ] - '0';
		for ( int j = 1; j <= m; j++ )
			a[ j ][ i ] = s[ i ][ j ], b[ j ][ i ] = s[ i ][ j ] ^ 1;
	}
	for ( int i = 1; i <= m; i++ ) {
		if ( (int)a[ i ].count() == n ) {
			ans.emplace_back( i, i, 4 );
		}
		if ( (int)b[ i ].count() == n ) {
			ans.emplace_back( i, i, 1 );
		}
	}
	for ( int i = 1; i <= m; i++ )
		for ( int j = i + 1; j <= m; j++ ) {
			if ( (int)( a[ i ] | a[ j ] ).count() == n ) {
				ans.emplace_back( i, j, 4 );
			}
			if ( (int)( b[ i ] | b[ j ] ).count() == n ) {
				ans.emplace_back( i, j, 1 );
			}
			if ( (int)( a[ i ] | b[ j ] ).count() == n ) {
				ans.emplace_back( i, j, 2 );
			}
			if ( (int)( b[ i ] | a[ j ] ).count() == n ) {
				ans.emplace_back( i, j, 3 );
			}
		}
	std::vector<std::vector<int>> f( n + 5, std::vector<int>( 2, 0 ) );
	std::vector<bool> vis( n + 5 );
	for ( auto [ i, j, t ] : ans ) {
		cout << i - 1 << " " << j - 1 << " " << t << "\n";
	}
	int k = ans.size();
	cout << k << "\n";
	for ( auto [ i, j, t ] : ans )
		cout << i - 1 << " " << j - 1 << " " << t << "\n";
	return 0;
}
