#include <cstdio>
#include <cstring>
using namespace std;
 
struct node{
    int a,b,c,deep,back;
}sz[11000];
 
int a,b,c,k;
bool x[110][110][110];
 
int main(){
    while(scanf("%d%d%d%d",&a,&b,&c,&k)!=EOF){
        int s=1,e=1;
        memset(x,false,sizeof(x));
        memset(sz,0,sizeof(sz));
        node temp;
        temp.a=a;
        temp.b=0;
        temp.c=0;
        temp.deep=0;
        temp.back=0;
        sz[1]=temp;
		if(temp.a==k){
			printf("yes\n0\n");
			continue;
		}
        x[temp.a][temp.b][temp.c]=true;
        bool y=true;
        while(s<=e){
            temp=sz[s];

            //a
            if(temp.a!=0){
                //a->b
                temp=sz[s];
                if(temp.b<b){
                    if(temp.a>b-temp.b){
                        temp.a-=b-temp.b;
                        temp.b=b;
                    }
                    else {
                        temp.b+=temp.a;
                        temp.a=0;
                    }
                    if(y&&(temp.a==k||temp.b==k||temp.c==k)) {
                        printf("yes\n%d\n",temp.deep+1);
                        y=false;
                    }
                    if(!x[temp.a][temp.b][temp.c]){
                        temp.deep++;
                        temp.back=s;
                        sz[++e]=temp;
                        x[temp.a][temp.b][temp.c]=true;
                    }
                }
                //a->c
                temp=sz[s];
                if(temp.c<c){
                    if(temp.a>c-temp.c){
                        temp.a-=c-temp.c;
                        temp.c=c;
                    }
                    else {
                        temp.c+=temp.a;
                        temp.a=0;
                    }
                    if(y&&(temp.a==k||temp.b==k||temp.c==k)) {
                        printf("yes\n%d\n",temp.deep+1);
                        y=false;
                    }
                    if(!x[temp.a][temp.b][temp.c]){
                        temp.deep++;
                        sz[++e]=temp;
                        x[temp,a][temp.b][temp.c]=true;
                    }
                }
            }
             
            //b 
            temp=sz[s];
            if(temp.b!=0){
                //b->a   
                temp=sz[s];
                if(temp.a<a){
                    if(temp.b>a-temp.a){
                        temp.b-=a-temp.a;
                        temp.a=a;
                    }
                    else {
                        temp.a+=temp.b;
                        temp.b=0;
                    }
                    if(y&&(temp.a==k||temp.b==k||temp.c==k)) {
                        printf("yes\n%d\n",temp.deep+1);
                        y=false;
                    }
                    if(!x[temp.a][temp.b][temp.c]){
                        temp.deep++;
                        sz[++e]=temp;
                        x[temp.a][temp.b][temp.c]=true;
                    }
                }
                //b->c
                temp=sz[s];
                if(temp.c<c){
                    if(temp.b>c-temp.c){
                        temp.b-=c-temp.c;
                        temp.c=c;
                    }
                    else {
                        temp.c+=temp.b;
                        temp.b=0;
                    }
                    if(y&&(temp.a==k||temp.b==k||temp.c==k)) {
                        printf("yes\n%d\n",temp.deep+1);
                        y=false;
                    }
                    if(!x[temp.a][temp.b][temp.c]){
                        temp.deep++;
                        sz[++e]=temp;
                        x[temp.a][temp.b][temp.c]=true;
                    }
                }
            }
 
            //c
            temp=sz[s];
            if(temp.c!=0){
                //c->a   
                temp=sz[s];
                if(temp.a<a){
                    if(temp.c>a-temp.a){
                        temp.b-=c-temp.c;
                        temp.a=a;
                    }
                    else {
                        temp.a+=temp.c;
                        temp.c=0;
                    }
                    if(y&&(temp.a==k||temp.b==k||temp.c==k)) {
                        printf("yes\n%d\n",temp.deep+1);
                        y=false;
                    }
                    if(!x[temp.a][temp.b][temp.c]){
                        temp.deep++;
                        sz[++e]=temp;
                        x[temp.a][temp.b][temp.c]=true;
                    }
                }
                //c->b
                temp=sz[s];
                if(temp.b<b){
                    if(temp.c>b-temp.b){
                        temp.c-=b-temp.b;
                        temp.b=b;
                    }
                    else {
                        temp.b+=temp.c;
                        temp.c=0;
                    }
                    if(y&&(temp.a==k||temp.b==k||temp.c==k)) {
                        printf("yes\n%d\n",temp.deep+1);
                        y=false;
                    }
                    if(!x[temp.a][temp.b][temp.c]){
                        temp.deep++;
                        sz[++e]=temp;
                        x[temp.a][temp.b][temp.c]=true;
                    }
                }
            }
            s++;
        }
        if(y) printf("no\n");
    } 
    return 0;
}
