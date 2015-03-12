//
//  main.c
//  graph
//
//  Created by Dina on 3/7/15.
//  Copyright (c) 2015 Dina. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    int i,j,nv,c=0;
    int k=0;
    double a;
    time_t t;
    srand ((unsigned) time(&t)  );
    nv=rand()%1000;
    if(nv!=0){
    int A[500000][2];
    for(i=0;i<nv-1;i++){
        for(j=i+1;j<nv-1;j++){
            a=rand()/(double)RAND_MAX;
            printf("%f\n", a);
            if(a>0.5){
                A[k][0]=i; A[k][1]=j;
                printf("%d %d\n", A[k][0], A[k][1]);
                k=k+1;
            }
        }
    }
    }
    else {
        printf("Empty Graph!");
    }
    
    printf("%d\n", nv);
    printf("%d",k);
    return 0;
}

