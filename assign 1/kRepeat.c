#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int subStrLen;

//struct to store hash values
struct node {
    //to store freq
    int freq;
    // //to store start index
    int start_index;

    struct node* next;
};
//struct of pointer to make link list
struct point{
    struct node* a;
};

//compare string within given indices
int compareS(char s[],int f1,int f2,int k){
    int count=0;
    for(int i=0;i<k;i++)
        if(s[f1+i]==s[f2+i])
            count++;
    //if whole string matches return 1
    if(count==k)
        return 1;
    //else return 0
    else
        return 0;
}

//using chaining when collison to make hashTable also calculating frequency of every substring
int makehash(char s[],int n,int mid,int k){
    //dummy node is used so head of link link dont change while travesal
    struct node* dummy;
    dummy= (struct node*) malloc(sizeof(struct node));

    //initializing hashTable to empty
    struct point ht[n-mid+1];
    for(int i=0; i<n-mid+1 ;i++){
        ht[i].a  = NULL;
        ht[i].a  = (struct node*)malloc(sizeof(struct node));
        ht[i].a->freq = 0;
        ht[i].a->start_index = 0;
    }

    //calculating hash value for first index
    int hash=0,index;
    for(int i=0;i<mid;i++)
        hash += (int)s[i];
    //finding index from hash value
    index = hash%(n-mid+1);

    //making first node other nodes will be made with loop
    if(ht[index].a->freq==0){
        ht[index].a->freq = 1;
        ht[index].a->start_index =0;
        ht[index].a->next = NULL;
    }

    // making other nodes
    for(int i=1;i<n-mid+1;i++){
        //by using rolling hash finding hash value
        hash = hash + (int)s[mid+i-1] - (int)s[i-1];
        //finding index of hashed value
        index = hash%(n-mid+1);

        //if head node is empty add node
        if(ht[index].a->freq == 0){
            ht[index].a->freq = 1;
            ht[index].a->start_index =i;
            ht[index].a->next = NULL;
        }

        //if node is already present
        else if(ht[index].a != NULL){
            //using dummy so that head of link list always remain same
            dummy=ht[index].a;

            //travel through link list
            while(dummy != NULL){
                //if str is already there increase its freq
                if(compareS(s,i,dummy->start_index,mid)){
                    dummy->freq++;
                    break;
                }
                //else add a node
                if(dummy->next==NULL){
                    //making new node to add
                    struct node* new_node;
                    new_node= (struct node*) malloc(sizeof(struct node));
                    new_node->freq = 1;
                    new_node->start_index = i;
                    new_node->next = NULL;
                    //adding new node
                    dummy->next = new_node;
                    break;
                }
                dummy = dummy->next;
            }
        }
    }

    int max=0;

    //check freq of any substring is greater then k
    for(int i=0;i<n-mid+1;i++){
        dummy = ht[i].a;
        //if node is not empty
        if(dummy->freq != 0){
            // checking in linklist
            while(dummy != NULL){
                // if freq is grater then k
                if(dummy->freq>=k){
                        max=1;
                }
                dummy=dummy->next;
            }
        }
    }

    //freeing memory allocted to pointers
    for(int i=0; i<n-mid+1;i++)
        free(ht[i].a);

    // returning value of max
    return max;
}

int main(){

    char s[100000];
    int k,len,i;
    scanf("%s",s);
    scanf("%d",&k);
    len = strlen(s);

    //binary search to find maxlen len which repeats atleat k times
    int first =0,last=len,l,mid,maxLen=1;
    while(first<=last){

        mid = (first + last)/2;
        // if we get a substring which repeats atleast k times
        if(makehash(s,len,mid,k)){
            //we to check a substring of higher length
            first = mid + 1 ;
            if(maxLen<mid)
                maxLen = mid ;
        }
        //else we to check a substring of lesser length
        else
            last = mid - 1 ;
    }
    printf("%d\n",maxLen);
    return 0;
}
