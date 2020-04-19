#include <stdio.h>
#include <stdlib.h>

struct node {
    //to store freq
    int freq;
    //to store num
    int num;
    // to store corresponding index of leafnode
    int index;
    //to make link list
    struct node* next;
};

struct point{
    struct node* a;
};
//to find next power of 2
int findN(int n){
    long long int power=1;
    for(int i=1; ;i++){
        power *=2;
        if(power>=n)
            return power;
    }
}

//making hash table
//last n node(i.e leaf node) will have hashtable with link list for collison
//other nodes will form the tree

// chaining to prevent collision
//while chaining it will take care that elements are in decreasing order
struct point makehash(struct point ht[],int x,int n,int k){
    int index;
    index = k+ (x%n) -1;
    int flag=0;

    struct point new,send;
    new.a  = NULL;
    new.a  = (struct node*)malloc(sizeof(struct node));
    send.a  = NULL;
    send.a  = (struct node*)malloc(sizeof(struct node));

    //if node is empty add node
    if(ht[index].a->freq==0){
        ht[index].a->freq = 1;
        ht[index].a->num = x;
        ht[index].a->index =index;
        ht[index].a->next = NULL;
        //new node used for delete
        new.a->num = x;
        new.a->freq = 1;
        new.a->index = index;
        //send node is used to return new node made
        send.a->num = x;
        send.a->freq = 1;
        send.a->index = index;
    }
    //if node is already present
    else{
        //using dummy so that head of link list always remain same
        struct node* dummy;
        dummy= (struct node*) malloc(sizeof(struct node));
        dummy=ht[index].a;

        //travel through link list
        while(dummy != NULL){
            //if num is already there increase its freq
            if(dummy->num==x){
                dummy->freq++;

                new.a->num = x;
                new.a->freq = dummy->freq;
                new.a->index = index;

                send.a->num = x;
                send.a->freq = dummy->freq;
                send.a->index = index;
                flag=1;

                break;
            }
            //else add a node at end of link list
            if(dummy->next==NULL){
                struct node* new_node;
                new_node= (struct node*) malloc(sizeof(struct node));
                new_node->num = x;
                new_node->freq = 1;
                new_node->index = index;
                new_node->next = NULL;

                new.a->num = x;
                new.a->freq = 1;
                new.a->index = index;

                send.a->num = x;
                send.a->freq = 1;
                send.a->index = index;

                dummy->next = new_node;
                break;
            }
            dummy = dummy->next;
        }
        //if freq is changed then put that node is its decending order position
        if(flag){
            flag=0;
            dummy=ht[index].a;

            struct node* push;
            push= (struct node*) malloc(sizeof(struct node));
            push = new.a;
            //push-- if freq is largest in its link make it as head
            if(ht[index].a->freq <= new.a->freq){
                push->next = ht[index].a;
                ht[index].a = push;
            }
            // insert-- else put it in right place
            else{
                while((dummy->next) != NULL){
                    if((dummy->next)->freq <= new.a->freq){
                        push->next = dummy->next;
                        dummy->next = push;

                        dummy=dummy->next;
                        break;
                    }
                    dummy=dummy->next;
                }
            }
            // delete node-- delete the orignal node as its copy is made that is in order
            struct node* prev;
            prev= (struct node*) malloc(sizeof(struct node));

            dummy=ht[index].a;
            prev = dummy;
            int count=0;

            while(dummy != NULL){
                if(dummy->num == new.a->num)
                    count++;
                if(count == 2)
                    break;
                prev = dummy;
                dummy = dummy->next;
            }
            prev->next = dummy->next;
            free(dummy);
        }
    }
    return send;
}
//making segment tree of hashtable
void constructTree(struct point ht[], int n, int k){
    for(int i=k-2; i>-1; i--){
        if(ht[2*i+1].a->freq < ht[2*i+2].a->freq)
            ht[i].a=ht[2*i+2].a;

        else
            ht[i].a=ht[2*i+1].a;
    }
}
//if node is updated then update tree so that it maintains its property
void update(struct point ht[], int i, int k){
    i=((i)-1)/2;
    while(i>=0){

        if(ht[2*i+1].a->freq < ht[2*i+2].a->freq)
            ht[i].a =ht[2*i+2].a;

        else
            ht[i].a =ht[2*i+1].a;

        if(i==0)
            break;

        i=(i-1)/2;
    }
}
//add no to hashtable while adding it alawys adds node such that all
//lists in table are in decreasing order
//then update tree so that it maintains its property

//make hash is in average of O(1) time
//update is in O(log n) time
void addInteger(struct point ht[], int x, int n, int k){
    struct point new;
    new = makehash(ht,x,n,k);
    int i= new.a->index;
    update(ht,i,k);
}

//while deleting we know that top element is largest so extract it and make it free
//top node has index which represents its poistion in leaf node so delete head node
//of link present at that node and update tree

//when you delete a node that node will automaticaly will replaced by a num which
//has just smaller freq then other as all links are in decreasing order

//so extracting max is in O(1) time
//update is in O(log n) time
void delMax(struct point ht[], int n, int k){
    int index = ht[0].a->index;
    int freqDel = ht[0].a->freq;

    if(ht[index].a->freq==0){
        printf("All elements deleted\n");
        return;
    }

    printf("deleted -> num=%d freq=%d\n",ht[0].a->num,ht[0].a->freq);
    //if next node is not null then delete its head
    //move head to next node
    if(ht[index].a->next!= NULL)
        ht[index].a = ht[index].a->next;

    //else make that node null i.e everything 0
    else{
        ht[index].a  = NULL;
        ht[index].a  = (struct node*)malloc(sizeof(struct node));
        ht[index].a->freq = 0;
        ht[index].a->num = 0;
        ht[index].a->index = index;
    }
    //after deleting update tree so that it hold its property
    update(ht,index,k);

    //if after updating its top element has again same max freq as earlier then
    //deleting every node with same freq
    if(ht[0].a->freq==freqDel)
        delMax(ht,n,k);
}
void printHt(struct point ht[],int n,int k){
    //using dummy so that head of link list always remain same
    struct node* dummy;
    dummy= (struct node*) malloc(sizeof(struct node));

    for(int i=0;i<n;i++){
        dummy = ht[k+i-1].a;
        while(dummy != NULL){
            printf("-->(%d,%d,%d) ",dummy->num,dummy->freq,dummy->index);
            dummy=dummy->next;
        }
        printf("\n");
    }
}

int main(){

    int n,t,i,x;
    scanf("%d",&n);
    scanf("%d",&t);

    //making hashtable of size n
    int k=findN(n);
    int size = 2*k-1;
    struct point ht[size];

    //initializing all leaf node as zero or NULL
    for(i=0;i<k;i++){
        ht[k+i-1].a  = NULL;
        ht[k+i-1].a  = (struct node*)malloc(sizeof(struct node));
        ht[k+i-1].a->freq = 0;
        ht[k+i-1].a->num = 0;
        ht[k+i-1].a->index = k+i-1;
    }
    //taking input and storing them in hash table without using array to save space
    for(i=0;i<n;i++){
        scanf("%d",&x);
        makehash(ht,x,n,k);
    }
    //constructing Tree
    constructTree(ht,n,k);

    //using dummy so that head of link list always remain same
    //printing whole hashtable including links
    printHt(ht,n,k);

    //taking queries t time
    int z=0,q,yes;
    printf("if you want to see links changing enter 1 else 0\n");
    scanf("%d",&yes);
    while(z<t){
        scanf("%d",&q);
        if(q==1){
            scanf("%d",&x);
            addInteger(ht,x,n,k);
            if(yes)
                printHt(ht,n,k);
        }
        else if(q==2){
            delMax(ht,n,k);
            if(yes)
                printHt(ht,n,k);
        }
        z++;
    }
    return 0;
}
