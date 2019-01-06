#include <cstdio>
using namespace std;

long long a[110],alen;

int main(){
   while(1){
       scanf("%d",&a[alen++]);
       if(a[alen-1]==0){
            break;
       }
   } 
   for(int i=alen-2;i>=0;i--){
       printf("%d ",a[i]);
   }
}
