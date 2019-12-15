#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

typedef struct STnode* link;
struct STnode{
    Node node;
    link a, b, c, d, x;
    int N;
};

static link head, z;
link NEW(Node node, link a, link b, link c, link d, int N){
    link x = malloc(sizeof *x);
    x -> node = node;
    x -> a = a;
    x -> b = b;
    x -> c = c;
    x -> d = d;
    x -> N = N;
    return x;
}

void STinit(){
    z = NEW(NULLnode, 0, 0, 0, 0, 0);
    head = NEW(NULLnode, z, z, z, z, 0);
}

link insert(link h, Node node, int N)
{
    Node fnode;
    Key v = Ckey(node, N);
    link k;
    //printf("process:in\n");
    if(v == '\0')
    {
        return NEW(node, z, z, z, z, N); 
    }
    strcpy(Skey(fnode), Skey(node));
    strcpy(Skey(fnode)+N+1, Skey(NULLnode));
    if(N == 0)
    {
        //printf("process:head\n");
        h -> node = NULLnode;
    }
    if(v == 'a')
    {
        //printf("process:a\n");
        
        if(h -> a == z)
        {
            h -> a = NEW(fnode, z, z, z, z, N+1);
            h -> a = insert(h -> a, node, N+1);
        }
        else insert(h -> a, node, N+1);
        
    }
    else if(v == 'b')
    {
        
        //printf("process:b\n");
        if(h -> b == z)
        {
            h -> b = NEW(fnode, z, z, z, z, N+1);
            h -> b = insert(h->b, node, N+1);
        }
        else insert(h->b, node, N+1);
       
    }
    else if(v == 'c')
    {
        //printf("process:c\n");
        if(h -> c == z)
        {
            h -> c = NEW(fnode, z, z, z, z, N+1);
            h -> c = insert(h->c, node, N+1);
        }
        else insert(h->c, node, N+1);
            
    }
    else
    {
        //printf("process:d\n");
        if(h -> d == z)
        {
            h -> d = NEW(fnode, z, z, z, z, N+1);
            h -> d = insert(h->d, node, N+1);
        }
        else insert(h->d, node, N+1);
    }
    //printf("finish!\n");
    return h;
}

void STinsert(Node node){
    head = insert(head, node, 0);
}

void STshow(link h){
    int i = 0;
    if(h == z)
    {
        return;
    }
    printf("node:%s %d %s ", Skey(h -> node), h -> N, Skey(h->x->node));
    printf("\n");
    STshow(h -> a);
    STshow(h -> b);
    STshow(h -> c);
    STshow(h -> d);
    
}

void STshowAll(void){
    STshow(head);
}

int main(void)
{
    Node node;
    char *s, *t;
    link k;
    s = malloc(sizeof(char)*100000000);
    t = malloc(sizeof(char)*100000000);
    scanf("%s", s);
    scanf("%s", t);
    STinit();
    strcpy(Skey(node), "abc");
    printf("insert:%s\n", Skey(node));
    STinsert(node);

    strcpy(Skey(node), "abaabb");
    printf("insert:%s\n", Skey(node));
    STinsert(node);

    strcpy(Skey(node), "cabaad");
    printf("insert:%s\n", Skey(node));
    STinsert(node);

    strcpy(Skey(node), "cabaddddd");
    printf("insert:%s\n", Skey(node));
    STinsert(node);

    strcpy(Skey(node), "dddabb");
    printf("insert:%s\n", Skey(node));
    STinsert(node);

    strcpy(Skey(node), "bbbcabaddd");
    printf("insert:%s\n", Skey(node));
    STinsert(node);

    STshowAll();
}