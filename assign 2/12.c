#include<stdio.h>
#include<stdlib.h>

struct bst{
    long long int key;
    long long int count;
    struct bst *left, *right;
};

struct point {
    long long int value;
    long long int index;
};

long long int Count (struct bst *node){
    if (node){
        if (node->left && node->right)
            return 1 + node->left->count + node->right->count;

        else if (node->left)
            return 1 + node->left->count;
        else if (node->right)
            return 1 + node->right->count;
        else
            return 1;
    }
    else
        return 0;
}

struct bst* buildTree(struct point a[],long long int l,long long int r){
    struct bst *node = NULL;
    if(l<=r){
        int m = (l+r)/2;

        node=(struct bst*)malloc(sizeof(struct bst));
        node->key = m;
        node->left = buildTree(a,l,m-1);
        node->right = buildTree(a,m+1,r);
        node->count = Count(node);
    }
    return node;
}

long long int Rank (struct bst *node, long long int X){

    long long int rank = 1;
    while (node){
        if (X == node->key){
            if (node->right)
                rank += node->right->count;
            return rank;
        }
        else if (X < node->key){
            rank++;
            if (node->right)
                rank += node->right->count;
            node = node->left;
        }
        else
            node = node->right;
    }
    return rank;
}

struct bst * Delete (struct bst *node, long long int X){
    if (!node)
        return node;

    if (node->key > X){
        node->left = Delete (node->left, X);
        node->count = 0;
        node->count =  Count (node);
        return node;
    }
    else if (node->key < X){
        node->right = Delete (node->right, X);
        node->count = 0;
        node->count = Count (node);
        return node;
    }

    if (node->left && node->right){
        struct bst *temp = node->left;
        while (temp->right)
            temp = temp->right;
        node->key = temp->key;
        node->left = Delete (node->left, temp->key);
    }
    else{
        struct bst *child;
        if (node->left)
            child = node->left;
        else
            child = node->right;
        free (node);
        return child;
    }
}

void heapify(struct point a[],long long int n,long long int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && a[l].value > a[largest].value)
        largest = l;

    if (r < n && a[r].value > a[largest].value)
        largest = r;

    struct point temp;
    if (largest != i){
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        heapify(a, n, largest);
    }
}

void heapSort(struct point a[],long long int n){
    for (long long int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    struct point temp;
    for (long long int i=n-1; i>0; i--){
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

int main(){

    long long int n;
    scanf("%lld",&n);
    struct point a[n];

    for(long long int i=0; i<n; i++){
        scanf("%lld",&a[i].value);
        a[i].index = i;
    }

    heapSort(a,n);
    struct bst *root = buildTree(a,0,n-1);

    long long int rank,sum=0;

    for(long long int i=0; i<n; i++){
        rank = Rank(root,a[i].index);
        sum += rank  -1;
        root=Delete(root,a[i].index);
    }

    printf("%lld",sum);


    return 0;
}
