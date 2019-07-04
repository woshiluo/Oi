#include <cstdio>
using namespace std;

int n,temp;
double cnt;

int main(){
	scanf("%d",&n);
	if(n>=150){
		cnt+=150*0.4463;
		n-=150;
		if(n>=250){
			cnt+=250*0.4663;
			n-=250;
			if(n>0){
				cnt+=n*0.5663;
			}
		}
		else {
			cnt+=n*0.4663;
		}
	}
	else {
		cnt+=n*0.4463;
	}
/*	temp=cnt*100;
	temp%=10;
	if(temp>=5){
		cnt+=0.1;
	}*/
	printf("%.1lf",cnt);
}
