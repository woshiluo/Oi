#include <cstdio>
#include <cstring>

const int N=1100;

char s[N]; 

int main(){
	scanf("%s",s);
	int tmp=strlen(s);	
	for(int i=0;i<tmp-1;i++){
		if(s[i]!=s[i+1]) printf("1 ");
		else printf("0 ");
	}
	if(s[tmp-1]=='a') printf("1");
	else printf("0");
}
