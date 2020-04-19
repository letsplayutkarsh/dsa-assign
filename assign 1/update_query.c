#include <stdio.h>
#include <limits.h>

struct node {
    int max;
    int min;
};

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

void constructTree(struct node st[], int n){
    int i;

    for(i=n-2; i>-1; i--){
        if(st[2*i+1].max < st[2*i+2].max)
            st[i].max = st[2*i+2].max;
        else
            st[i].max = st[2*i+1].max;

        if(st[2*i+1].min > st[2*i+2].min)
            st[i].min = st[2*i+2].min;
        else
            st[i].min = st[2*i+1].min;
    }
}

void update(struct node st[], int i, int x, int n){
    st[n+i-1].max=x;
    st[n+i-1].min=x;

    i=((n-1+i)-1)/2;
    while(i>=0){

        if(st[2*i+1].max < st[2*i+2].max)
            st[i].max = st[2*i+2].max;
        else
            st[i].max = st[2*i+1].max;

        if(st[2*i+1].min > st[2*i+2].min)
            st[i].min = st[2*i+2].min;
        else
            st[i].min = st[2*i+1].min;

        if(i==0)
            break;

        i=(i-1)/2;
    }
}

int findmax(struct node st[], int n, int i, int j, int s, int e, int p){
    if (s > j || e < i)
        return INT_MIN;
    else if (s >= i && e <= j)
        return st[p].max;

    int mid = (s+e)/2;

    int l1 = findmax(st,n,i,j,s,mid,2*p+1);
    int l2 = findmax(st,n,i,j,mid+1,e,2*p+2);

    if(l1>=l2)
        return l1;
    else
        return l2;
}


int findmin(struct node st[], int n, int i, int j, int s, int e, int p){
    if (s > j || e < i)
        return INT_MAX;
    else if (s >= i && e <= j)
        return st[p].min;

    int mid = (s+e)/2;

    int l1 = findmin(st,n,i,j,s,mid,2*p+1);
    int l2 = findmin(st,n,i,j,mid+1,e,2*p+2);

    if(l1<=l2)
        return l1;
    else
        return l2;
}

int query(struct node st[], int n, int x, int c){
    int s = 1, e = n-x;
    int mid, flag;
    while(s < e){
        mid = (s + e)/2;
        int max = findmax(st,n,x,x+mid-1,0,n-1,0);
        int min = findmin(st,n,x,x+mid-1,0,n-1,0);
        if(st[n+x-1].min-c <= min && max <= st[n+x-1].max+c){
            s = mid + 1;
            flag = 1;
        }
        else{
            e = mid;
            flag = 0;
        }
    }
    if(flag)
        return mid;
    else
        return mid-1;
}

int findz(struct node st[], int n, int x, int len){
    int max = findmax(st,n,x,x+len-1,0,n-1,0);
    int min = findmin(st,n,x,x+len-1,0,n-1,0);
    int l1 = max - st[n+x-1].max;
    int l2 = st[n+x-1].min - min;
    return l1 >= l2 ? l1 : l2;
}

int main(){

    int n,t,num,i;
    scanf("%d",&n);
    scanf("%d",&t);
    int k=findN(n);
    int size = 2*k-1;

    struct node st[size];
    for(i=0;i<n;i++){
        scanf("%d",&num);
        st[k+i-1].max=num;
        st[k+i-1].min=num;
    }
    for(i=n;i<k;i++){
        st[k+i-1].min=INT_MIN;
        st[k+i-1].max=INT_MAX;
    }
    constructTree(st,k);

    char q[1];
    int x,y,c;
    while(t>0){
        scanf("%s",q);
        if(q[0]=='U'){
            scanf("%d",&x);
            scanf("%d",&y);
            update(st,x-1,y,k);
        }
        if(q[0]=='Q'){
            scanf("%d",&x);
            scanf("%d",&c);
            if(c<0)
                printf("-1 -1\n");
            else{
                int l = query(st,k,x-1,c);
                int z = findz(st,k,x-1,l);
                printf("%d %d\n",l,z);
            }
        }
        t--;
    }

    return 0;
}
