#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

bool is_number(const char cur) { return cur >= '0' && cur <= '9'; }
template <class T>
T read() {
    T res = 0, k = 1;
    char x = getchar();
    for (; !is_number(x); x = getchar())
        if (x == '-')
            k = -1;
    for (; is_number(x); x = getchar()) 
		res = res * 10 + (x - '0');
    return res * k;
}
template <class T>
T Min(T a, T b) { return a < b ? a : b; }
template <class T>
T Max(T a, T b) { return a > b ? a : b; }
template <class T>
void chk_Min(T &a, T b) { if (a > b) a = b; }
template <class T>
void chk_Max(T &a, T b) { if (a < b) a = b; }

const int N = 5e5 + 1e4;

int main() {
#ifdef woshiluo
    freopen("e2.in", "r", stdin);
    freopen("e2.out", "w", stdout);
#endif

    int n, k;
    char str[N];
    scanf("%d%d", &n, &k);
    scanf("%s", str + 1);
    int pos = Min(n, k); bool answerd = true;
	{
		int tot = 0; 
		for (int i = Min(n, k); i >= 1; i--) {
			if( tot >= (int)(5e7) ) {
				answerd = false;
				break;
			}
			bool flag = true;
			for (int j = Min(i, pos) + 1; j <= k; j++) {
				tot ++;
				int fir = (j % i == 0) ? i : (j % i);
				int sec = (j % pos == 0) ? pos : (j % pos);
				if (str[fir] < str[sec]) {
					break;
				}
				if (str[sec] < str[fir]) {
					flag = false;
					break;
				}
			}
			if (flag)
				pos = i;
		}
	}
	if( !answerd ) {
		for (int i = 1; i <= Min( n, k ); i ++ ) {
			bool flag = true;
			for (int j = Min(i, pos) + 1; j <= k; j++) {
				int fir = (j % i == 0) ? i : (j % i);
				int sec = (j % pos == 0) ? pos : (j % pos);
				if (str[fir] < str[sec]) {
					flag = false;
					break;
				}
				if (str[sec] < str[fir]) {
					break;
				}
			}
			if(!flag)
				pos = i;
		}
	}

	for (int j = 1; j <= k; j++) {
		int sec = (j % pos == 0) ? pos : (j % pos);
		printf("%c", str[sec]);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
