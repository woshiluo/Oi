#include <cstdio>

int n, k;
int len, res, ans;
char str[210000];

int main(){
	scanf("%d%d", &n, &k);
	scanf("%s",str);
	for(int i = 0; i < 26; i++){
		res = 0, len =0;
		for(int j = 0; j < n; j++){
			if(str[j] == i + 'a'){
				len++;
				if(len == k) len=0, res++;
			}
			else len = 0;
		}
		ans = res > ans? res: ans;
	}
	printf("%d", ans);
}
