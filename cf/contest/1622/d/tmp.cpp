#include<bits/stdc++.h>
 
using ll = long long;
using ld = long double;
 
namespace GTI
{
	char gc(void)
   	{
		const int S = 1 << 16;
		static char buf[S], *s = buf, *t = buf;
		if (s == t) t = buf + fread(s = buf, 1, S, stdin);
		if (s == t) return EOF;
		return *s++;
	}
	ll gti(void)
   	{
		ll a = 0, b = 1, c = gc();
		for (; !isdigit(c); c = gc()) b ^= (c == '-');
		for (; isdigit(c); c = gc()) a = a * 10 + c - '0';
		return b ? a : -a;
	}
	int gts(char *s)
   	{
		int len = 0, c = gc();
		for (; isspace(c); c = gc());
		for (; c != EOF && !isspace(c); c = gc()) s[len++] = c;
		s[len] = 0;
		return len;
	}
	int gtl(char *s)
   	{
		int len = 0, c = gc();
		for (; isspace(c); c = gc());
		for (; c != EOF && c != '\n'; c = gc()) s[len++] = c;
		s[len] = 0;
		return len;
	}
}
using GTI::gti;
using GTI::gts;
using GTI::gtl;
 
const int M = 998244353, N = 5050;
int fpw(int a, int b)
{
	a %= M, b %= M - 1;
	if (b < 0) b += M - 1;
	int c = 1;
	for (; b; b >>= 1, a = 1ll * a * a % M)
		if (b & 1)
			c = 1ll * c * a % M;
	return c;
}
 
int fct[N], ifct[N];
void init(int n)
{
	fct[0] = 1;
	for (int i = 1; i <= n; i++)
		fct[i] = 1ll * fct[i - 1] * i % M;
	ifct[n] = fpw(fct[n], -1);
	for (int i = n - 1; i >= 0; i--)
		ifct[i] = ifct[i + 1] * (i + 1ll) % M;
}
int C(int n, int m)
{
	if (m < 0 || n - m < 0) return 0;
	return 1ll * fct[n] * ifct[m] % M * ifct[n - m] % M;
}
 
char s[N];
int main(void)
{
	freopen( "d.in", "r", stdin );
	int n = gti(), k = gti();
	init(n + 1);
	gts(s);
	int cnt1 = 0;
	for (int i = 0; i < n; i++)
		cnt1 += (s[i] - '0');
	if (cnt1 < k) puts("1");
	else
	{
		int ans = 1;
		for (int l = 0; l < n; l++)
		{
			cnt1 = 0;
			for (int r = l; r < n; r++)
			{
				cnt1 += (s[r] - '0');
				if (l < r && cnt1 <= k)
				{
					int now = cnt1;
					if (s[l] == '0') --now;
					if (s[r] == '0') --now;
					ans = (ans + C(r - l - 1, now)) % M;
				}
			}
		}
		printf("%d\n", (ans % M + M) % M);
	}
	return 0;
}
