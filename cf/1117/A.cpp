#include <cstdio>
#include <algorithm>

inline int Max(int a, int b){return a > b? a: b;}

const int N = 1e5 + 1e4;

int n, max, max_id, len, rig, max_len;
int a[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		if(a[i] > max)
			max = a[i];
	}	
	for(int i = 1; i <= n; i++){
		if(a[i] == max && ( a[i - 1] != max || i == 1 ) ){
			rig = i; len = 0;
			while( a[rig] == a[i] && rig <= n ){
				rig++; len++;
			}
			max_len = Max(len, max_len);
		}
	}	
	printf("%d", max_len);
}
