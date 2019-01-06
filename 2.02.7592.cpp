#include <cstdio>
using namespace std;

int f(int x,int y){
	if(x%y==0) return y;
	int temp=x%y;
	return f(y,temp);
}

int main(){
	int a,b;
	scanf("%d %d",&a,&b);
	if(b>a){
		int temp=b;
		b=a;
		a=temp;
	}
	printf("%d",f(a,b));
}
