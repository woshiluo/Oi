#include <cstdio>
using namespace std;

int a[20];

int gcd(int x , int y){
	if(!y) return x;
	else return gcd(y,x%y);
}

int main(){
	int n,gys,gbs;
	scanf("%d",&n);
	scanf("%d %d",&a[0],&a[1]);
	if(a[1]<a[0]) gys=gcd(a[0],a[1]);
	else gys=gcd(a[1],a[0]);
	gbs=(a[1]/gys)*a[0];
	for(int i=2;i<n;i++){
		scanf("%d",&a[i]);
		if(gbs<a[i]) gys=gcd(a[i],gbs);
		else gys=gcd(gbs,a[i]);
		gbs=a[i]/gys*gbs;
	}	
	printf("%d",gbs);
}
