#include <cstdio>
#include <cstring>
using namespace std;

char a[12];

int main(){
	bool zhen=true;
	scanf("%s",a);
	if(a[0]=='-') zhen=false;
	int len=strlen(a);
	if(!zhen) printf("-");
	while(a[len-1]=='0') len--;
	for(int i=len-1;i>=0;i--){
		if(a[i]=='-') continue;
		printf("%c",a[i]);
	}
}
