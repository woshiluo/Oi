#include <cstdio>

int n, now, tmp, tcnt;
int trie[2000000][26];
char str[20], *p;

inline void insert(char *str){
	p = str;
	now = 0;
	while(*p){	
		tmp = *p - 'a';
		if( trie[now][tmp] == 0 ) trie[now][tmp] = ++tcnt;
		now = trie[now][tmp];
		p++;
	}
}

inline bool find(char *str){
	p = str;
	now = 0;
	while(*p){
		tmp = *p - 'a';
		if( trie[now][tmp] == 0 ) return false;
		now = trie[now][tmp];
		p++;
	}
	return true;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%s", str);
		insert(str);
	}
	
	scanf("%d",&n);
	while(n--){
		scanf("%s", str);
		printf("%s\n", find(str)? "YES": "NO");
	}
}
