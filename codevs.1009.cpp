#include <cstdio>
#include <cstring>
using namespace std;

char a[20][2];
bool x[20];

int main(){
	char n[40];
	memset(n,0,sizeof(n));
	int k;
	long long ans=0;
	scanf("%s %d",n,&k);
	int len=strlen(n);
	for(int i=0;i<k;i++) scanf("\n%c %c",&a[i][0],&a[i][1]);
	for(int i=0;i<k;i++){
		for(int j=0;j<len;j++){
			if(a[i][0]==n[j]){ 
				ans++;
				if(!x[j]){
					x[j]=true;
					ans++;
				}
			}
		}
	}
	printf("%lld",ans);
}
