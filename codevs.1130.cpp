#include <cstdio>
#include <cstring>
using namespace std;

int temp_len;

int main(){
	char a[11];
	scanf("%s",a);
	int len=strlen(a);
	if(a[0]=='-') printf("-");
	for(int i=len-1;i>=0;i--){
		if(a[i]>='0'&&a[i]<='9'){
			if(a[i]=='0'&&temp_len==0) continue;
			printf("%c",a[i]);
			temp_len++;
		}
	}
}
