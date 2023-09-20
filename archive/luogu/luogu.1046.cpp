#include <cstdio>
using namespace std;
	
int cnt;
int n,a[11];

int main(){
	for(int i=0;i<10;i++) scanf("%d",&a[i]);
	scanf("%d",&n);
	n+=30;
	for(int i=0;i<10;i++){
		if(a[i]<=n) cnt++;
	}
	printf("%d",cnt);
}
