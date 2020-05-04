#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct bst {
	int key;
	struct bst* right;
	struct bst* left;
};

struct QNode {
	struct bst* ptr;
	int min, max;
	struct QNode* next;
};

struct Queue{
    struct QNode *front,*rear;
};

struct QNode* newNode(struct bst* node, int miN, int maX){
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->ptr = node;
	temp->min = miN;
	temp->max = maX;
    temp->next = NULL;
    return temp;
}

struct Queue* createQueue(){
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enQueue(struct Queue* q, struct bst* node, int miN, int maX){
    struct QNode* temp = newNode(node,miN,maX);

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

void deQueue(struct Queue* q){
    if (q->front == NULL)
        return;

    struct QNode* temp = q->front;

    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}

struct bst* getNode(int key){
    struct bst *temp = (struct bst*)malloc(sizeof(struct bst));
    temp-> key = key;
    temp-> left = temp->right = NULL;
    return temp;
}

struct bst* constructTree(int a[], int n){
	if (n == 0)
		return NULL;

	struct Queue* q = createQueue();

	int i = 0;
	struct bst* root = getNode(a[i++]);
	enQueue(q,root,INT_MIN,INT_MAX);

	while (i != n) {

		struct QNode temp ;
		temp = *(q->front);
		deQueue(q);

		if (i<n && (a[i]<temp.ptr->key && a[i]>temp.min)) {

			struct bst* newn = getNode(a[i++]);
			enQueue(q,newn,temp.min,temp.ptr->key);
			temp.ptr->left = newn;
		}

		if (i<n && (a[i]>temp.ptr->key && a[i]<temp.max)) {

			struct bst* newn = getNode(a[i++]);
			enQueue(q,newn,temp.ptr->key,temp.max);
			temp.ptr->right = newn;
		}
	}
	return root;
}


void preorder(struct bst* node){
	if(node){
		printf("%d ",node->key);
		preorder(node->left);
		preorder(node->right);
	}
}

int main()
{
	int n;
	printf("enter size :");
	scanf("%d",&n);
	int a[n];

	for(int i=0; i<n; i++)
		scanf("%d",&a[i]);

	struct bst* root = constructTree(a, n);

	preorder(root);

	return 0;
}
