#include <cstdio>
#include <cmath>
#include <math.h>
#include <algorithm>
using namespace std;

double f(double x){
    return pow(x,5)-15*pow(x,4)+85*pow(x,3)-225*pow(x,2)+274*x-121;
}


int main(){
    double l=1.5,r=2.4,mid;
    while(l<=r){
        mid=(l+r)/2;
        if(fabs( l-r )<0.0000001) break;
        if(f(mid)<0) r=mid;
        if(f(mid)>0) l=mid;
    }
    printf("%lf",mid);
}
