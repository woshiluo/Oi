#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct FUCK{
	int x,min;
};

int cmp(FUCK a,FUCK b){
    return a.min>b.min;
}

int main(){
	int m,n,k,l,d;
	scanf("%d%d%d%d%d",&m,&n,&k,&l,&d);
	int ax[d],ay[d],bx[d],by[d];
	FUCK x[m+10],y[n+10];
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	for(int i=0;i<d;i++){
		scanf("%d%d%d%d",&ax[i],&ay[i],&bx[i],&by[i]);
		if(ay[i]==by[i]) {
			int min;
			if(ax[i]<bx[i]) min=ax[i];
			else min=bx[i];
			x[min].min++;
			x[min].x=min;
		}
		if(ax[i]==bx[i]) {
			int min;
			if(ay[i]<by[i]) min=ay[i];
			else min=by[i];
			y[min].min++;
			y[min].x=min;
		}
	}
	sort(y,y+n+10,cmp);
	sort(x,x+m+10,cmp);
	int a[k+1];
	int b[l+1];
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	int temp=0;
	for(int i=0;i<m+1;i++){
		if(temp==k) break;
		if(x[i].min>0) {temp++;a[i]=x[i].x;}
	}
	temp=0;
	for(int i=0;i<n+1;i++){
		if(temp==l) break;
		if(y[i].min>0) {temp++;b[i]=y[i].x;}
	}
	sort(a,a+k);
	sort(b,b+l);
	for(int i=0;i<k;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	for(int i=0;i<l;i++){
		printf("%d ",b[i]);
	}
} 
