#include <stdio.h>
#include <stdlib.h>

int N = 0;

void sift_up(int k, int * heap)
{
    //enquanto k não é a raiz da arvore
    //e for maior que o pai
    while(k>1 && heap[k] > heap[k/2])
    {
        //troca com o pai
        int aux = heap[k];
        heap[k] = heap[k/2];
        heap[k/2] = aux;

        k = k/2;
    }
}

void push(int x, int * heap)
{
    heap[(++N)] = x;
    sift_up(N, heap);
}

void sift_down(int k, int * heap)
{
    int filho_dir = (2*k) + 1;
    int filho_esq = 2*k;

    //enquanto k tem filhos
    while((filho_dir < N || filho_esq < N)
            //e heap[k] for menor que algum
            && (heap[k] < heap[filho_dir] || heap[k] < heap[filho_esq]))
    {
        int L = 0;

        //L é o maior filho de heap[k]
        if(heap[filho_esq] > heap[filho_dir])
            L = filho_esq;
        else
            L = filho_dir;

        //troca
        int aux = heap[k];
        heap[k] = heap[L];
        heap[L] = aux;

        //atualiza posições
        k=L;
        filho_dir = (2*k) + 1;
        filho_esq = 2*k;
    }
}

void pop(int * heap)
{
    //remove v[1] - faz o que quiser (retorna, ignora, etc)

    //troca a raiz com o ultimo elemento da folha e chama sift_down para arrumar maxheap
    int aux = heap[1];
    heap[1] = heap[N];
    heap[N] = aux;
    N--;

    sift_down(1, heap);
}

//transforma vetor qualquer em uma max-heap
void heapfy(int * heap)
{
    for(int i=N; i>=1; i--)
        sift_down(i, heap);
}

void heapsort(int *heap)
{
    int aux = N;

    //retira o primeiro (maior) elemento e o insere na ultima posição
    for(int i=0; i<aux; i++)
    {
        //se tiver só mais 2 numeros para comparar, checa
        //se já está ordenada para evitar de executar o sift_down
        //e colocar o numero maior na primeira posição de novo
        if(N <= 2 && heap[1] <= heap[2])
            break;

        pop(heap);
    }
}

//para testar algoritmo:
int main()
{
    int vet[] = {53,12,23,34,42,34,12,34,12,34,5,0,8,20,1,3,90,115,25,61};

    //vetor inicia em 1 entao termina em tam+1
    int tam = sizeof(vet)/sizeof(vet[0]) + 1;
    int * heap = (int*)malloc((tam) * sizeof(int));
    int i = 0;

    //inicializa vetor com -1
    for(i=0; i<tam; i++)
        heap[i] = -1;

    //tam-1 pois só está inserindo a qtde de elementos no vet (0 indexado)
    for(i=0; i<tam-1; i++)
        push(vet[i], heap);

    heapfy(heap);
    heapsort(heap);

    for(int i=1; i<tam; i++)
        printf("%d ", heap[i]);

    free(heap);

    return 0;
}
