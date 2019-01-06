#include <cstdio>
#include <cmath>
using namespace std;

bool zs(int n){
	int temp=sqrt(n);
	for(int i=2;i<=temp;i++){
		if(n%temp==0)return false;		
	}
	return true;
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=2;i<n;i++){
		if(/*zs(i)&&*/n%i==0){
			printf("%d",n/i);
			return 0;
		}
	}
}
