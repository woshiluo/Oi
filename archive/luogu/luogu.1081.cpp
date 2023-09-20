#include <cstdio>
#include <algorithm>

const int N=110000;

inline int Aabs(int a){return a>0?a:0-a;}

struct ci{
	int l,r,id,now,hei;
}c[N];

int n,m,pre,nxt,now,ans,p;
int nid[N],next_a[N],next_b[N],sta[N][25],stb[N][25],f[N][25];
long long x,dis_a,dis_b;
double Min=2147483647;
// helper functions start 

// cmp(ci a,ci b)
// sort helper functions 
// return bool
bool cmp(ci a,ci b){
	return a.hei<b.hei;
}

// fir()
// find tht nearst
// return bool
inline bool fir(){
	if(pre==0) return true;
	if(nxt==0) return false;
	return c[nxt].hei-c[now].hei<c[now].hei-c[pre].hei;
}

// sec(int x,int y)
// find second nearst in a and b
// x > now y < now
// return int 
// - the second nearst's id 
inline int sec(int x,int y){
	if(x==0) return c[y].id;
	if(y==0) return c[x].id;
	if(c[x].hei-c[now].hei<c[now].hei-c[y].hei) return c[x].id;
	else return c[y].id;
}

// get_dis(long long x,int p)
// Get the dis_a ans dis_b
// - x the Max distance
// - p start 
// return void
inline void get_dis(long long x,int p){
	dis_a=dis_b=0;
	for(int j=20;j>=0;j--){
		if(f[p][j]&&(long long)dis_a+dis_b+sta[p][j]+stb[p][j]<=x){
			dis_a+=sta[p][j];
			dis_b+=stb[p][j];
			p=f[p][j];
		}
	}
	if(next_a[p]&&dis_a+dis_b+sta[p][0]<=x) dis_a+=sta[p][0];
}

// helper funtions end

// readin()
// readin
inline void readin(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i].hei);
		c[i].id=i;
	}
}

// init()
// find pre and nxt / Discretization
inline void init(){
	std::sort(c+1,c+n+1,cmp);
	for(int i=1;i<=n;i++){
		nid[c[i].id]=i;
		c[i].l=i-1;
		c[i].r=i+1;
	}
	c[1].l=c[n].r=0;
	for(int i=1;i<=n;i++){
		now=nid[i];pre=c[now].l;nxt=c[now].r;
		if(fir()) next_b[i]=c[nxt].id,next_a[i]=sec(c[nxt].r,pre);
		else next_b[i]=c[pre].id,next_a[i]=sec(nxt,c[pre].l);
		if(pre) c[pre].r=nxt;
		if(nxt) c[nxt].l=pre;
	}
}

// make_st()
// make st table
inline void make_st(){
	for(int i=1;i<=n;i++){
		f[i][0]=next_b[next_a[i]];
		sta[i][0]=Aabs(c[nid[i]].hei-c[nid[next_a[i]]].hei);
		stb[i][0]=Aabs(c[nid[next_a[i]]].hei-c[nid[f[i][0]]].hei);
	}
	for(int j=1;j<=20;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];		
			sta[i][j]=sta[i][j-1]+sta[f[i][j-1]][j-1];
			stb[i][j]=stb[i][j-1]+stb[f[i][j-1]][j-1];
		}		
	}
}

// Ans_all()
// find Max of dis_a / dis_b
inline void Ans_all(){
	scanf("%lld",&x);
	for(int i=1;i<=n;i++){
		get_dis(x,i);
		if(Min>(1.0*dis_a/dis_b)){
			Min=1.0*dis_a/dis_b;
			ans=i;
		}
	}
	printf("%d\n",ans);
}

// Ans()
// get ans of all ask
inline void Ans(){
	scanf("%d",&m);
	while(m--){
		scanf("%d%lld",&p,&x);
		get_dis(x,p);
		printf("%lld %lld\n",dis_a,dis_b);
	}
}
int main(){
	readin();
	init();
	make_st();
	Ans_all();
	Ans();
}
