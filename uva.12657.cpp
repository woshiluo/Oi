#include <cstdio>
using namespace std;

struct node{
    int next,last;
    int n;
}a[110000];

int head,last;
int n,m,x,y,mcnt;
int temp;
node tmp1,tmp2;
bool zf=false;

inline void bian1(){
    scanf("%d%d",&x,&y);
    
    if(a[y].last==x||x==y) return ; 
    tmp1=a[x];tmp2=a[y];
    if(x==last) last=a[x].last;
    if(x==head) head=tmp1.next;
    else if(y==head) head=x;
    
    a[tmp1.next].last=tmp1.last;
    a[tmp1.last].next=tmp1.next;

    a[tmp2.last].next=x; 
    a[x].last=tmp2.last;

    a[x].next=y;
    a[y].last=x;   
}

inline void bian2(){
    scanf("%d%d",&x,&y);

    tmp1=a[x];tmp2=a[y];
    if(a[y].next==x||x==y) return ;    
    if(y==last) last=x;
    else if(x==last) last=a[x].last; 
    if(x==head) head=tmp1.next;
 
    a[tmp1.next].last=tmp1.last;
    a[tmp1.last].next=tmp1.next;
    
    a[x].last=y;
    a[y].next=x;

    a[tmp2.next].last=x;
    a[x].next=tmp2.next;
}

inline void bian3(){
    scanf("%d%d",&x,&y);
    if(x==y) return ;
    if(x==head) head=y;
    else if(y==head) head=x;
    if(x==last) last=y;
    else if(y==last) last=x;
    if(a[y].next==x) {int te;te=x;x=y;y=te;}
    tmp1=a[x];tmp2=a[y];
    if(a[x].next==y){
        a[tmp1.last].next=y;
        a[y].last=tmp1.last;

        a[y].next=x;
        a[x].last=y;

        a[tmp2.next].last=x;
        a[x].next=tmp2.next;
    }
    else {
        a[tmp1.next].last=y;   
        a[y].next=tmp1.next;
        a[tmp1.last].next=y;
        a[y].last=tmp1.last;

        a[tmp2.next].last=x;   
        a[x].next=tmp2.next;
        a[tmp2.last].next=x;
        a[x].last=tmp2.last;
    }

}

inline void bian4(){zf=!zf;}

inline void read(){
    for(int i=1;i<=m;i++){
        scanf("%d",&temp); 
        if(temp==4) bian4();
        if(zf&&temp!=3) temp=3-temp;
        if(temp==1) bian1();
        if(temp==2) bian2();
        if(temp==3) bian3();
    }
}

inline void init(){
    mcnt++;
    for(int i=1;i<=n;i++){
        a[i].n=i;
        a[i].next=i+1;
        a[i].last=i-1;
    }
    zf=false;
    head=1;
    last=n;
//    a[n].next=1;
    //    a[1].last=n;
}

inline void sum(){
    long long sum=0,cnt=0;
    if(!zf)
        for(int i=head;;i=a[i].next){
            cnt++;
            //printf("%d ",a[i].n);
            if(cnt%2!=0) sum+=a[i].n;
            if(i==last){ 
                printf("Case %lld: %lld\n",mcnt,sum);
                break;                
            }
        }
    else {
        for(int i=last;;i=a[i].last){
            cnt++; 
            //printf("%d ",a[i].n);
            if(cnt%2!=0) sum+=a[i].n;   
            if(i==head){
                printf("Case %lld: %lld\n",mcnt,sum);
                break;
            }
        }
    }
}

int main(){
//    freopen("233.in","r",stdin);
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        read();
        sum();
    }
}
