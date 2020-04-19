#include <stdio.h>

int findN(int n){
    long long int power=1;
    for(int i=1; ;i++){
        power *=2;
        if(power>=n)
            return power;
    }
}

int log_2(int n){
    int i;
    for(i=1;;i++){
        if(n==1)
            return i-1;
        n=n/2;
    }
}

void constructTree(int a[], int st[], int n){
    int i;
    for(i=0;i<n;i++)
        st[n+i-1]=a[i];

    for(i=n-2; i>-1; i--)
        st[i]=st[2*i+2]+st[2*i+1];

    for(i=0;i<n;i++)
        st[2*n-1+i]=i+1;
}

void update(int a[], int st[], int i, int n){
    a[i]=0;
    st[n-1+i]=0;
    i=((n-1+i)-1)/2;
    while(i>=0){
        st[i]=st[2*i+1]+st[2*i+2];

        if(i==0)
            break;
        i=(i-1)/2;
    }
}

int index_(int st[],int x,int k, int height){
    int i=0,h=1;
    if(st[0]<x)
        return -1;

    while(h<=height){
        if(st[2*i+1]<x){
            x=x-st[2*i+1];
            i=2*i+2;
        }
        else if(st[2*i+1]>x){
            i=2*i+1;
        }
        else if(st[2*i+1]==x){
            i=2*i+1;
            h++;
            if(h>height)
                break;
            if(st[2*i+2]==0){
                i=2*i+1;
            }

            else{
                x=x-st[2*i+1];
                i=2*i+2;
            }
        }
        h++;
    }
    return st[i+k];
}

int main(){

    int n,t,i;
    scanf("%d",&n);
    scanf("%d",&t);
    int k=findN(n);
    int a[k];

    for(i=0;i<n;i++)
        a[i]=1;
    for(i=n;i<k;i++)
        a[i]=0;

    long int size = 3*k-1;
    int st[size];

    constructTree(a,st,k);
    int height=log_2(size-k);
    int z=0,q,x;
    while (z<t) {
        scanf("%d",&q);
        scanf("%d",&x);

        if(q==0){
            update(a,st,x-1,k);
        }

        if(q==1)
            printf("%d\n",index_(st,x,k,height));
        z++;
    }

    return 0;
}
