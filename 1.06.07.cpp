#include <cstdio>
#include <iostream>
using namespace std;

int n;
int a[3100];
bool x[3100];

int main(){
   scanf("%d",&n);
   for(int i=1;i<=n;i++){
       scanf("%d",&a[i]);
       if(i>=2){
           int temp=max(a[i],a[i-1])-min(a[i],a[i-1]);
           if(x[temp]||temp>=n||temp<=0) {
               printf("Not jolly");
               return 0;
           }
           else x[temp]=true;
       }
   }
   printf("Jolly");
}
