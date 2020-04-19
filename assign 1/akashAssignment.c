#include <stdio.h>

struct node {
    int f[26];
};

int findN(int n){
    long long int power=1;
    for(int i=1; ;i++){
        power *=2;
        if(power>=n)
            return power;
    }
}

void constructTree(char a[], struct node st[], int n){
    int i,j,index;
    for(i=0;i<n;i++)
        if( (int)a[i] >96 && (int)a[i]<123 ){
            index=(int)a[i]-97;
            st[n+i-1].f[index]+=1;
        }

    for(i=n-2; i>-1; i--)
        for(j=0;j<26;j++)
            st[i].f[j]+=st[2*i+2].f[j]+st[2*i+1].f[j];
}

void update(char a[], struct node st[], int i,char x[], int n){
    char prevchar=a[i];
    st[n-1+i].f[(int)a[i]-97]-=1;
    a[i]=x[0];
    st[n-1+i].f[(int)a[i]-97]+=1;

    i=((n-1+i)-1)/2;
    while(i>=0){
        st[i].f[(int)x[0]-97]+=1;
        if(st[i].f[(int)prevchar-97]!=0)
            st[i].f[(int)prevchar-97]-=1;

        if(i==0)
            break;
        i=(i-1)/2;
    }
}

struct node addArr(struct node ans, struct node l1, struct node l2){
    for(int i=0;i<26;i++)
        ans.f[i]=ans.f[i]+ l1.f[i]+ l2.f[i];
    return ans;
}

struct node query(struct node st[],struct node empty,struct node ans, int i, int j, int s, int e, int p){
    if(i>e || j<s)
        return empty;
    if(i<=s && j>=e)
        return st[p];

    int m=s+(e-s)/2;

    struct node l1=query(st,empty,ans,i,j,s,m,2*p+1);
    struct node l2=query(st,empty,ans,i,j,m+1,e,2*p+2);

    return addArr(ans,l1,l2);
}

char find(struct node ans,int lexo){
    for(int i=0;i<26;i++){
        lexo = lexo - ans.f[i];
        if(lexo<=0)
            return (char)(i+97);
    }
    if(lexo>0)
        return '0';
}


int main(){

    int n,t,i;
    scanf("%d",&n);
    scanf("%d",&t);
    int k=findN(n);
    char a[k];

    scanf("%s",a);
    for(i=n;i<k;i++)
        a[i]='0';

    long int size = 2*k-1;
    struct node st[size],empty,ans;

    for(i=0;i<26;i++){
        empty.f[i]=0;
        ans.f[i]=0;
    }

    for(int i=0;i<size;i++)
        for(int j=0;j<26;j++)
            st[i].f[j]=0;

    constructTree(a,st,k);

    int z=0,q,index,l,r,lexo;
    char x[1];

    while (z<t) {
        scanf("%d",&q);
        if(q==0){
            scanf("%d",&index);
            scanf("%s",x);
        }
        else
            scanf("%d %d %d",&l,&r,&lexo);

        if(q==0){
            update(a,st,index-1,x,k);
        }

        if(q==1){
            ans=query(st,empty,ans,l-1,r-1,0,(k-1),0);
            char answer=find(ans,lexo);
            if(answer != '0')
                printf("%c\n",answer);
            else
                printf("Out of range\n");
            for(int j=0;j<26;j++)
                ans.f[j]=0;
        }

        z++;
    }

    return 0;
}
