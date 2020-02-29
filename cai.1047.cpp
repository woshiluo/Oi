#include <cstdio>
#include <cstring>
using namespace std;

struct node{
	int deep,a[3][5],k,last;
	char d;
}b[400000],ed;

int l=1,r=1,fff;
int temp[5],p[16];
bool x[362881];

int kt(node s){	

	int a[10],L=0,R=0;

	for(int i=1;i<=2;i++){
		for(int j=1;j<=4;j++){
			L++;
			a[L]=s.a[i][j];
		}
	}

	long long ans=0;bool x[20];
	memset(x,false,sizeof(x));

	for(long long i=1;i<=7;i++){
		R=0;

		for(int j=1;j<a[i];j++) if(x[j]==false) R++;

		ans=ans+R*p[9-i];
		x[a[i]]=true;
	}

	ans++;
	return ans;
} 

void sc2(int k){
	if(b[k].last!=-1) sc2(b[k].last);
	if(b[k].last!=-1) printf("%c",b[k].d);
	return ;	
}

void sc(int k)//输出
{
	printf("%d\n",b[k].deep);
	sc2(k);
	printf("\n");
	return;
}

void A(){
	node c;
	for(int i=1;i<=4;i++) c.a[2][i]=b[l].a[1][i];
	for(int i=1;i<=4;i++) c.a[1][i]=b[l].a[2][i];
	c.k=kt(c);
	if(!x[ c.k ]){
		r++;
		x[ c.k ]=true;
		b[r]=c;b[r].last=l;b[r].d='A';b[r].deep=b[l].deep+1;
		if(c.k==ed.k) {
			sc(r);
			fff=1;
		}
	}
}

void B(){
	node d;
	d.a[1][1]=b[l].a[1][4];
	d.a[2][1]=b[l].a[2][4];
	d.a[1][2]=b[l].a[1][1];
	d.a[2][2]=b[l].a[2][1];
	d.a[1][3]=b[l].a[1][2];
	d.a[2][3]=b[l].a[2][2];
	d.a[1][4]=b[l].a[1][3];
	d.a[2][4]=b[l].a[2][3];
	d.k=kt(d);
	if(!x[ d.k ]){
		r++;
		x[ d.k ]=true;
		d.deep=b[l].deep+1;
		b[r]=d;b[r].last=l;b[r].d='B';
		if(d.k==ed.k) {
			sc(r);
			fff=1;
		}
	}
}

void C(){
	node e;
	e.a[1][1]=b[l].a[1][1];
	e.a[1][4]=b[l].a[1][4];
	e.a[2][1]=b[l].a[2][1];
	e.a[2][4]=b[l].a[2][4];

	e.a[1][2]=b[l].a[2][2];
	e.a[1][3]=b[l].a[1][2];
	e.a[2][2]=b[l].a[2][3];
	e.a[2][3]=b[l].a[1][3];
	e.k=kt(e);
	if(!x[ e.k ]){
		r++;
		x[ e.k ]=true;
		e.deep=b[l].deep+1;
		b[r]=e;b[r].last=l;b[r].d='C';
		if(e.k==ed.k){
			sc(r);
			fff=1;
		}
	}
}

int main(){
	p[0]=1;
	for(int i=1;i<=15;i++) p[i]=p[i-1]*i;
	b[1].last=-1;
	b[1].deep=0;
	b[1].a[1][1]=1;
	b[1].a[1][2]=2;
	b[1].a[1][3]=3;
	b[1].a[1][4]=4;
	b[1].a[2][1]=8;
	b[1].a[2][2]=7;
	b[1].a[2][3]=6;
	b[1].a[2][4]=5;
	b[1].k=kt(b[1]);
	for(int i=1;i<=4;i++) scanf("%d",&ed.a[1][i]);
	for(int i=4;i>=1;i--) scanf("%d",&ed.a[2][i]);
	ed.k=kt(ed);
	if(ed.k==b[1].k) {
		printf("0");
		return 0;
	}
	b[1].d=' ';
	memset(x,false,sizeof(x));
	while(l<=r){
		fff=0;
		A();
		if(fff==1) return 0;
		B();
		if(fff==1) return 0;
		C();
		if(fff==1) return 0;
		l++;
	}

}
