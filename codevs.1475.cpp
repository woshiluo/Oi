#include <cstdio>
#include <cstring>
using namespace std;

int main(){
	int n;
	char m[1100];
	int a[1100];
	scanf("%s",m);
	scanf("%d",&n);
	int len=strlen(m);
	for(int i=0;i<len;i++){
		int temp;
		if(m[i]>='0'&&m[i]<='9'){
			temp=m[i]-48;
		}
		else temp=m[i]-65+10;
		a[i]=temp;
	}
	int ans=0;
	for(int i=0;i<len;i++){
		ans=ans*n+a[i];
	}
	printf("%d",ans);
}
