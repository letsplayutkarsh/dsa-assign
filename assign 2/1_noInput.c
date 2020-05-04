
#include <stdio.h>
#include <stdlib.h>

struct bst {
    int key;
    struct bst *left,*right;
    struct bst *parent;
};

int indexx=0;

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

void sortarray(struct bst *node,int a[]){
    if(node){
        sortarray(node->left,a);
        a[indexx++] = node->key;
        sortarray(node->right,a);
    }
}

int size(struct bst* node){
    if (node==NULL)
        return 0;
    else
        return(size(node->left) + 1 + size(node->right));
}

void inorder(struct bst *node){
    if(node){
        inorder(node->left);
        printf("%d ",node->key);
        inorder(node->right);
    }
}

struct bst* mergeTree(struct bst* root1, struct bst* root2){
    int len1,len2,len;

    len1=size(root1);
    len2=size(root2);

    len=len1+len2;
    int a[len1],b[len2],merge[len];

    sortarray(root1,a);  indexx=0;
    sortarray(root2,b);

    int temp1=0,temp2=0;
    for(int i=0;i<len;i++){
        if(a[temp2]>b[temp1] && temp1<len2)
            merge[i] = b[temp1++];

        else if(a[temp2]<b[temp1] && temp2<len1)
            merge[i] = a[temp2++];
    }

    struct bst *root = buildTree(merge,0,len-1);
    return root;
}

int main(){

    struct bst *root1,*root2;

    struct bst* root =mergeTree(root1,root2);
    inorder(root);
}
