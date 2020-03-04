#include <cstdio>

#include <queue>
#include <vector>
#include <algorithm>

const int N = 2e5 + 1e4;

int n, cnt;
int mp[N], a[N], t[N];

struct node {
	int id, val;
} tmp_a[N];

struct node2 {
	int val;
	bool operator< ( const node2 _b ) const { return this -> val < _b.val; }
};

bool cmp( node _a, node _b ) { return _a.val < _b.val; }
std::vector<int> sta[N];
std::priority_queue<node2> q;

void init() {
	std::sort( tmp_a + 1, tmp_a + n + 1, cmp );
	for( int i = 1; i <= n; i ++ ) {
		if( i == 1 || tmp_a[i].val != tmp_a[ i - 1 ].val ) {
			cnt ++;
			mp[cnt] = tmp_a[i].val;
		}
		a[ tmp_a[i].id ] = cnt;
	}
}

int main() {
#ifdef woshiluo
	freopen( "D.in", "r", stdin );
	freopen( "D.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &tmp_a[i].val );
		tmp_a[i].id = i;
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &t[i] );
	}

	init();
	for( int i = 1; i <= n; i ++ ) {
		sta[ a[i] ].push_back(i);
	}

	int la = 0;
	long long cur_sta = mp[1], ans = 0, sum = 0;
	while(1) {
		if( cur_sta == mp[ la + 1 ] ) {
			la ++;
			int size = sta[la].size();
			for( int i = 0; i < size; i ++ ) {
				int val = t[ sta[la][i] ];
				q.push( (node2){val} );
				sum += val;
			}
		}
		if( q.empty() ) {
			if( la == cnt ) 
				break;
			cur_sta = mp[ la + 1 ];
			continue;
		}
		int top = q.top().val;
		sum -= top;
		q.pop();
		ans += sum;
		cur_sta ++;
	}
	printf( "%lld\n", ans );
}
