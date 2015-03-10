#include <omp.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef N
#define N 1000 
#endif

struct node {
   int k; 
   double alt_harmonic_sum;
   struct node* next;
};

struct node* init_list(struct node* p);
void processwork(struct node* p); 
int fib(int n); 

double process(int k) 
{
   double harmonicSum=0;
   int i;
   int flag;
   for (i=0; i<k; i++) {
     if (i%2 == 0) 
         flag = 1;
     else
         flag = -1;
     harmonicSum += flag*1.0/(i+1);
   }
   return harmonicSum;

}

void processwork(struct node* p) 
{
   int k;
   double temp;
   k = p->k;
   temp = process(k);

   p->alt_harmonic_sum = temp;

}

struct node* init_list(struct node* p) 
{
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = malloc(sizeof(struct node));
    p = head;
    p->k = 1; 
    p->alt_harmonic_sum = 0;
    for (i=2; i<= N; i++) {
       temp  = malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->k = i;
       p->alt_harmonic_sum = 0;
    }
    p->next = NULL;
    return head;
}

int main() 
{
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;

     printf("Process linked list\n");
     printf("  Each linked list node will be processed by function 'processwork()'\n");
     printf("  Each ll node will compute alternate harmonic series sum up to the k value");      

     p = init_list(p);
     head = p;

     start = omp_get_wtime();

			p=head;
			while (p)  {
			  processwork(p);
			  p = p->next;
            }

     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %f\n",p->k, p->alt_harmonic_sum);
        temp = p->next;
        free (p);
        p = temp;
     }  
	 free (p);

     printf("Compute Time: %f seconds\n", end - start);

     return 0;
}

