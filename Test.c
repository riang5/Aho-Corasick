#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "AhoCor.h"


 int main(void) {
    char Data[400002];
    char *Data2;
    int i, n, k;
	FILE *fp,*fpb; 
	char fname[] = "dat0_in";
    char fnameb[] = "dat0_ref";
    char fnameo[] = "CheckFile.txt";
    clock_t start,end;
    Node node;
    int id, count, xcount, r, l;
    int isAccepted[100000];
    int *aclength;
    int *test;
    int *xpos;

    start=clock();
    aclength = malloc(sizeof(int)*100000);
    test = malloc(sizeof(int)*400002);
    Data2 = malloc(sizeof(char)*400002);
    xpos = malloc(sizeof(int)*400002);
	

    fp = fopen(fnameb, "r"); 
	if(fp == NULL) 
    {
		printf("%s file not open!\n", fnameb);
		return -1;
	} 
    else 
    {
		printf("%s file opened!\n", fnameb);
	}
    fscanf(fp, "%s" ,Data);
    fclose(fp);


    fpb = fopen(fname, "r"); 
	if(fpb == NULL)
    {
		printf("%s file not open!\n", fname);
		return -1;
	} 
    else 
    {
		printf("%s file opened!\n", fname);
	}
    id = 0;
    STinit();
    fscanf(fpb, "%s", Data2);
    while((fscanf(fpb,"%s", Skey(node))!=EOF))
    {
        STinsert(node, id);
        id++;
	}
    fclose(fpb);


    STahocorasick();
    //STshowAll();


    for(i = 0; i < id; i++)
    {
        isAccepted[i] = 0;
        aclength[i] = 0;
    }
    for(i = 0; i < 400002; i++)
    {
        test[i] = 0;
        xpos[i] = 0;
    }

    STthroughPut(Data, isAccepted, 0, aclength);


    for(i = 0; i < 400002; i++)
    {
        if(Data2[i] == 'x')
        {
            xpos[i] = 1;
        }
    }


    int NumOfx = 0, NumOfCover = 0, NumOfCoveredx = 0;
    for(i = 0; i < 400002; i++)
    {
        if(xpos[i] == 1 && test[i] != 0)
        {
            NumOfCoveredx++;
        }
        if(xpos[i] == 1)
        {
            NumOfx++;
        }
        if(test[i] != 0)
        {
            NumOfCover++;
        }
        if(i == 400001)
        {
            printf("x:%d cover:%d coveredx:%d ratio:%.6f\n", NumOfx, NumOfCover, NumOfCoveredx, (float)NumOfCoveredx/NumOfx);
        }
    }
    for(i =0 ; i < 1000; i++)
    {
        printf("%d", test[i]);
    }
    printf("\n");
    

    end = clock();

    printf("time is %d[ms]\n",end - start);

    free(aclength);
    free(test);
    free(xpos);
    free(Data2);
    return 0;
 }