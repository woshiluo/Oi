#include <cstdio>
#include <cstring>
using namespace std;

char a[110],b[110],c[110];
//   after  before please
char d[110],e[110];//password yz->
int cnt=0;

int main(){
	scanf("%s%s%s",a,b,c);
	int len1=strlen(a);
	int len2=strlen(c);
	for(int i=0;i<len1;i++){
		if(d[a[i]-65]!=0){
			if(b[i]!=d[a[i]-65]){
				printf("Failed");
				return 0;
			}
			continue;
		}
		if(e[b[i]-65]!=0){
			if(a[i]!=e[b[i]-65]){
				printf("Failed");
				return 0;
			}
			continue;
		}
		cnt++;
		d[a[i]-65]=b[i];
		e[b[i]-65]=a[i];
	}
	if(cnt<26) {
		printf("Failed");
		retrun 0;
	}
	for(int i=0;i<len2;i++){
		printf("%c",d[c[i]-65]);
	}
}
