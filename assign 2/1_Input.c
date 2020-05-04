#include <stdio.h>
#include <stdlib.h>

struct bst {
    int key;
    struct bst *left,*right;
    struct bst *parent;
};

struct bst* buildTree(int a[], int l, int r){
    struct bst *node = NULL;
    if(l<=r){
        int m = (l+r)/2;

        node=(struct bst*)malloc(sizeof(struct bst));
        node->key = a[m];
        node->left = buildTree(a,l,m-1);
        node->right = buildTree(a,m+1,r);

        if(node->right)
            node->right->parent = node;
        if(node->left)
            node->left->parent = node;
    }
    return node;
}

void inorder(struct bst *node){
    if(node){
        inorder(node->left);
        printf("%d ",node->key);
        inorder(node->right);
    }
}


void heapify(int a[], int n, int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && a[l] > a[largest])
        largest = l;

    if (r < n && a[r] > a[largest])
        largest = r;

    int temp;
    if (largest != i){
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    int temp;
    for (int i=n-1; i>0; i--){
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

int main(){

    int len1,len2;
    printf("enter size of tree 1: ");
    scanf("%d",&len1);
    printf("enter size of tree 2: ");
    scanf("%d",&len2);

    printf("\nenter distinct values\n");
    int len=len1+len2;
    int a_1[len1],a_2[len2],a[len];

    printf("enter elements of tree 1: ");
    for(int i=0; i<len1; i++)
        scanf("%d",&a_1[i]);

    printf("enter elements of tree 2: ");
    for(int i=0; i<len2; i++)
        scanf("%d",&a_2[i]);

    heapSort(a_1,len1);
    heapSort(a_2,len2);

    int c=0,b=0;
    for(int i=0;i<len;i++){
        if(a_1[b]>a_2[c] && c<len2)
            a[i] = a_2[c++];

        else if(a_1[b]<a_2[c] && b<len1)
            a[i] = a_1[b++];
    }

    struct bst *root = buildTree(a,0,len-1);

    inorder(root);
}
