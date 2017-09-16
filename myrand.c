#include "myrand.h"


//  0 << k << 40
int LCM (int Xn, int k){

int a[] = {106, 211, 421, 430, 936, 1366, 171, 859, 419, 967, 141, 625, 1541, 1741,
1291, 205, 421, 1255, 281, 1093, 421, 1021, 1277, 2041, 2311, 1597, 2661, 4081, 3661,
3877, 3613, 1366, 8121, 4561, 7141, 9301, 4096, 2416, 17221, 36261, 84589};

int c[] = {1283, 1663, 1663, 2531, 1399, 1283, 11213, 2531, 6173, 3041, 28411, 6571, 2957,
2731, 4621, 29573, 17117, 6173, 28411, 18257, 54773, 24631, 24749, 25673, 25367, 51749,
36979, 25673, 30809, 29573, 45289, 150889, 28411, 51349, 54773, 49297, 150889, 374441,
107839, 66037, 45989};

int m[] = {6075, 7875, 7875, 11979, 6655, 6075, 53125, 11979, 29282, 14406, 134456, 
31104, 14000, 12960, 21870, 139968, 81000, 29282, 134456, 86436, 259200, 116640, 117128, 
121500, 120050, 244944, 175000, 121500, 145800, 139968, 214326, 714025, 134456, 243000, 
259200, 233280, 714025, 1771875, 510300, 312500, 217728};
    return (a[k]*Xn + c[k]) % m[k];
}

int simple ( int n )
{
for ( int i = 2; i*i <= n; i ++ )
if ( n % i == 0 ) return 0;
return 1;
}

int mod_inv(int a, int n)
{
	int b0 = n, t, q;
	int x0 = 0, x1 = 1;
	if (n == 1) return 1;
	while (a > 1) 
    {
		q = a / n;
		t = n, n = a % n, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

void ICG(int n, int a, int c, int seed, int count, int* res)
{
    int x0 = seed;
    int reverse;
    static int N;
    res[0] = x0;
    for(int i = 1; i < count; ++i)
    {
        N = res[i-1];
        if(simple(N))
        {
            
            if(N == 0)
            res[i]=c;
            else
            {
                reverse  = mod_inv(N, n);
                res[i]=((a*reverse + c) % n);
            }  
        }
        else
        {
            reverse  = mod_inv(N, n);
            res[i]=((a*reverse + c) % n);
        }
    }    
}

void SICG(int n, int a, int c, int seed, int count, int p1, int p2, int* res)
{
    int res1[count], res2[count];
    ICG(n, a, c, seed, count, res1);
    ICG(n, a, c, seed, count, res2);

    for(int i = 0, k=p1*p2; i < count; res[i]=(res1[i]/p1 + res2[i]/p2)*k, ++i);
}

//based on  LCM
void GRA(int *res, int size) {
  int free_item[size];
  int lsize = size;
  
  for (int i = 0; i < size; ++i)
    free_item[i] = i;
  
  for (int i = 0; i < size; ++i) {
    int current_item = LCM(0, 20) % lsize;
    
    res[free_item[current_item]] = i;
    lsize--;
    free_item[current_item] = free_item[lsize];
  }
}

unsigned long MWC(void)
{
    static unsigned long x = 3456789, y = 362436069, z = 77465321, c = 13579;
    unsigned long long t;
    t = 6905990LL*x+c;
    x=y;
    y=z;
    c=(t>>32);
    return z=(t&0xffffffff);
}

unsigned long xor128(void)
{
    static unsigned long x = 3456789,
    y = 62436069,
    z = 1288629,
    w = 675123;
    unsigned long t;
    t=(x^(x<<11));
    x=y;
    y=z;
    z=w;
    return(w=(w^(w>>19))^(t^(t>>8)));
}

int FWL(int level, int cas, int seed){    
    int a[] = {24, 38, 37, 30, 83, 107, 273, 1029, 576, 4178};
    int b[] = {55, 89, 100, 127, 258, 378, 607, 2281, 3217, 9689};
    int M = max(a[level], b[level]);
    int array[M];
    int res;

    switch (cas){
         case 1:
    {
        for (int i = 0; i<M; i++)
            array[i] = MWC();
        break;
    }
    case 2:
    {
        srand(seed);
        for (int i = 0; i<M; i++)
            array[i] = rand();
        break;        
    } 
    }
    

    if(array[M-a[level]] >= array[M-b[level]])
    res = array[M-a[level]] - array[M-b[level]];
    else
    res = array[M-b[level]] - array[M-a[level]];  

    return res;  
}