#ifndef DJYNSKI_C
#define DJYNSKI_C
/*
#include <stdio.h>
#include <limits.h>

#include <header.h>
#include "global.h"
//V presumo q seja o destino final
#define P (wt[v] + t->wt)
void GRAPHpfs(adj *cidades, int s, int st[], int wt[])
{
    int v, w;
    link *t;
 
    PQinit(cidades->V);
    for (v = 0; v < N; v++)
    {
        st[v] = -1;
        wt[v] = INT_MAX;
        PQinsert(v);
    }
    wt[s] = 0.0;
    PQdec(s);
    while (!PQempty())
        if (wt[v = PQdelmin()] != INT_MAX)
            for (t = cidades -> next_cidade[v]; t != NULL; t = t->next)
                if (wt[w = t->v] > P)
                {
                    wt[w] = P;
                    PQdec(w);
                    st[w] = v;
                }
}
*/

#endif