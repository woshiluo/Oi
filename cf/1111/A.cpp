#include <cstdio>
#include <cstring>

int alen, blen;
char a[1100], b[1100];

inline bool yy(char a){
	if(a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u') return true;
	else return false;
}

int main(){
	scanf("%s", a);
	scanf("%s", b);
	alen = strlen(a);
	blen = strlen(b);
	if(alen != blen){
		printf("No\n");
		return 0;
	}
	for(int i = 0; i < alen; i++){
		if(yy(a[i]) != yy(b[i])){
			printf("No\n");
			return 0;
		}	
	}
	printf("Yes\n");
}
