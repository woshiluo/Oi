#include <cstdio>
#include <cstring>

inline int Aabs(int a) {return a < 0? 0 - a: a;}
inline int Min(int a, int b) {return a < b? a: b;}

int len, ans = 2147483647;
char str[110];

inline int get_sub(char now, char to){
	return Min(('Z' - now) + (to - 'A') + 1, Min(Aabs((to - 'A') - (now - 'A')), ('Z' - to ) + (now - 'A') + 1)); 
}

int get_start(int now){
	return get_sub(str[now], 'A') + get_sub(str[now + 1], 'C') + get_sub(str[now + 2], 'T') + get_sub(str[now + 3], 'G');
}

int main(){
	scanf("%d", &len);
	scanf("%s", str + 1);
	for(int i = 1; i <= len - 4 + 1; i++){
		ans = Min(get_start(i), ans);
	}
	printf("%d", ans);
}
