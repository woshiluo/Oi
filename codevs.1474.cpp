#include <cstdio>
using namespace std;

int main(){
	int n,m,temp[1000],cnt=0;
	scanf("%d %d",&n,&m);
	while(n!=0){
		temp[cnt++]=n%m;
		n/=m;
	}
	for(int i=cnt-1;i>=0;i--){ 
		if(temp[i]<10) printf("%d",temp[i]);
		else printf("%c",temp[i]-10+65);
	}
	return 0;
}
