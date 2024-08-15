// powered by c++11
// by Isaunoya
#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (int i = (x); i >= (y); --i)

using namespace std;
using db = double;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

#define pii pair<int, int>
#define fir first
#define sec second

template <class T>

void cmax(T& x, const T& y) {
	if (x < y) x = y;
}

template <class T>

void cmin(T& x, const T& y) {
	if (x > y) x = y;
}

#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back

template <class T>

void sort(vector<T>& v) {
	sort(all(v));
}

template <class T>

void reverse(vector<T>& v) {
	reverse(all(v));
}

template <class T>

void unique(vector<T>& v) {
	sort(all(v)), v.erase(unique(all(v)), v.end());
}

void reverse(string& s) { reverse(s.begin(), s.end()); }

#define int long long

int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
int lcm(int x, int y) { return x * y / gcd(x, y); }

int n;

struct point { int x, y; };

int dis(point x, point y) { return (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y); }
const int maxn = 2e6 + 1e5;
point a[maxn];
int ans[maxn];

int getid(int x) { return (x > n) ? (x - n) : x; }
bool chk(int t, int x, int y) {
  int distx = dis(a[t], a[x]);
  int disty = dis(a[t], a[y]);
  if (x > t + n || x < t) distx *= -1;
  if (y > t + n || y < t) disty *= -1;
  if (distx == disty) return getid(x) > getid(y);
  return distx < disty;
}

void solve(int l, int r, int ql, int qr) {
  if (l > r) return;
  int mid = (l + r) >> 1, nxt = ql;
  for (int i = ql; i <= qr; i++)
    if (chk(mid, nxt, i)) nxt = i;
  ans[mid] = getid(nxt);
  solve(l, mid - 1, ql, nxt);
  solve(mid + 1, r, nxt, qr);
}

const double pi = acos(-1);

struct Vector {
	int x, y;
	Vector(int _x = 0, int _y = 0) { x = _x, y = _y; }
	Vector operator-(const Vector& rhs) const { return Vector(x - rhs.x, y - rhs.y); }
	double operator^(const Vector& rhs) const { return x * rhs.y - y * rhs.x; }
	bool operator<(const Vector& rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
};

Vector rtt(Vector x, double tht) {
	return Vector(x.x * cos(tht) - x.y * sin(tht), x.x * sin(tht) + x.y * cos(tht));
}
vector<Vector> p;

long long pow_2( int p ) { return 1LL * p * p; }

signed main() {
#ifdef woshiluo
	freopen( "tmp.in", "r", stdin );
#endif
	std::ios::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
	// code begin.
	int T;
	cin >> T;
	while( T -- ) {
		int m;
		cin >> m;
		std::vector<std::pair<int, int>> list;
		for( int i = 1; i <= m; i ++ ) {
			int a, b;
			cin >> a >> b;
			list.emplace_back( a, b );
		}
		double c = 0;
		for( int i = 1; i < m; i ++ ) 
			c += sqrt( pow_2( list[i].first - list[ i - 1 ].first ) + pow_2( list[i].second - list[ i - 1 ].second ) );
		c += sqrt( pow_2( list[0].first - list[ m - 1 ].first ) + pow_2( list[0].second - list[ m - 1 ].second ) );
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
		for (int i = n + 1; i <= n * 2; i++) a[i] = a[ i - n ];
		solve(1, n, 1, n * 2);
		int res = 0;
		for (int i = 1; i <= n; i++) cmax(res, dis(a[i], a[ans[i]]));
		cout << setprecision(20) << sqrt(res) * pi * 2.0 + c << '\n';
	}
	return 0;
	// code end.
}
