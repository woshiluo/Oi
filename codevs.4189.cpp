#include <cstdio>
#include <cstring>

int n, len, now, tmp, tcnt;
int trie[2000000][26];
char str[20];

inline void insert(char *str){
	len = strlen(str);	
	now = 0;
	for(int i = 0; i < len; i++){
		tmp=str[i]-'a';
		if( trie[now][tmp] == 0 ) trie[now][tmp] = ++tcnt;
		now = trie[now][tmp];
	}
}

inline bool find(char *str){
	len = strlen(str);	
	now = 0;
	for(int i = 0; i < len; i++){
		tmp = str[i] - 'a';
		if( trie[now][tmp] == 0 ) return false;
		now = trie[now][tmp];
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
