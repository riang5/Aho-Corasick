#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AhoCor.h"

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

link insert(link h, Node node, int N, int id)
{
    Node fnode;
    Key v = Ckey(node, N);
    link k;
    //printf("process:in\n");
    if(v == '\0')
    {
        node.key = 's';
        node.id = id;
        h->node.key = 's';
        h->node.id = id;
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
            h -> a = insert(h -> a, node, N+1, id);
        }
        else insert(h -> a, node, N+1, id);
        
    }
    else if(v == 'b')
    {
        
        //printf("process:b\n");
        if(h -> b == z)
        {
            h -> b = NEW(fnode, z, z, z, z, N+1);
            h -> b = insert(h->b, node, N+1, id);
        }
        else insert(h->b, node, N+1, id);
       
    }
    else if(v == 'c')
    {
        //printf("process:c\n");
        if(h -> c == z)
        {
            h -> c = NEW(fnode, z, z, z, z, N+1);
            h -> c = insert(h->c, node, N+1, id);
        }
        else insert(h->c, node, N+1, id);
            
    }
    else
    {
        //printf("process:d\n");
        if(h -> d == z)
        {
            h -> d = NEW(fnode, z, z, z, z, N+1);
            h -> d = insert(h->d, node, N+1, id);
        }
        else insert(h->d, node, N+1, id);
    }
    //printf("finish!\n");
    return h;
}

void STinsert(Node node, int id){
    head = insert(head, node, 0, id);
}

link ahocorasick(link h, link k, int i, int j, int sw)
{
    if(sw == 0)
    {
        if(h == z)
        {
            return z;
        }
    }
    else if(k->N < 2)
    {
        return z;
    }
    else if(h == z)
    {
        return z;
    }
    else if(strcmp(Skey(h->node), Skey(k->node)+j) == 0)
    {     
        return h;
    }
    else if(Ckey(k->node, i+j) == 'a')
    {
        return ahocorasick(h->a, k, i+1, j, 1);
    }
    else if(Ckey(k->node, i+j) == 'b')
    {
        return ahocorasick(h->b, k, i+1, j, 1);
    }
    else if(Ckey(k->node, i+j) == 'c')
    {
        return ahocorasick(h->c, k, i+1, j, 1);
    }
    else
    {
        return ahocorasick(h->d, k, i+1, j, 1);
    }
    if(sw == 0)
    {
        while(1)
        {
            h -> x = ahocorasick(head, h, 0, j, 1);
            j++;
            if(h->x == z &&  j < h->N) continue;
            else break;
            
        }
        ahocorasick(h->a, k, 0, 1, 0);
        ahocorasick(h->b, k, 0, 1, 0);
        ahocorasick(h->c, k, 0, 1, 0);
        ahocorasick(h->d, k, 0, 1, 0);
    }
    return h;
}

void STahocorasick()
{
    head = ahocorasick(head, head, 0, 1, 0);
}

void throughPut(char *str, int *isAccepted, link h, int i, int *aclength)
{
    link k;
    while(1)
    {
        char c = str[i];
        if(i != 0){
            h = k;
        }
        if(c == '\0')
        {
            return;
        }
        if(h->node.key == 's')
        {
            isAccepted[h->node.id] = 1;
            aclength[h->node.id] = strlen(Skey(h->node));
            
        }
        if(c == 'a')
        {
            if(h->a == z) k = h->x;
            else 
            {
                k = h->a;
                i++;
            }
        }
        else if(c == 'b')
        {
            if(h->b == z) k = h->x;
            else 
            {
                k = h->b;
                i++;
            }
        }
        else if(c == 'c')
        {
            if(h->c == z) k = h->x;
            else 
            {
                k = h->c;
                i++;
            }
        }
        else if(c == 'd')
        {
            if(h->d == z) k = h->x;
            else 
            {
                k = h->d;
                i++;
            }
        }
    }
}

void STthroughPut(char *s, int *isAccepted, int i, int *aclength)
{
    throughPut(s, isAccepted, head, i, aclength);
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

/*int main(void)
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

    while(scanf("%s", Skey(node)) != EOF)
    {
        STinsert(node, 0);
    }

    STahocorasick();

    STshowAll();
}*/

/*
cccaabbbbbbcccddddccccbbbbbbaaaaaaacccccaabcbabcbabcbbcbababcbbdbbdbdbbdbdbdbbdbdbbdbdbdbdbbcabbabdbbabbdbbabbbdbbb
xxxxabbbxxbcccdddxccccbbxxxbaaxxaaaccxccaabcbabcbabcbbcbababcbbdbbdbdbbdbdbdbbdbdbbdbdbdbdbbcabbabdbbabbdbbabbbdbbb
c
cccaabb
bbabbbd
cccaabbbbbb
bdb
abbbbb
bbcccddddc
bb
abcbbdbbdbdbbdbdbdbb
ccbbbbbb
aacccccaabcbabcbabcbbcbababcbbdbbd
b
bbaaaaa
bbdbdbdbdbbcabbabdbbabb
bbbbbaaaaaaacccc
bbbdbbb
cc
*/