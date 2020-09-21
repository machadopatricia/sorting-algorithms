#include <stdio.h>
#include <stdlib.h>

//heap comeca na posicao 1, para poder fazer operações
int N = 1;

void siftUp(int k, int * heap)
{
    //enquanto k não é a raiz da arvore
    //e não é maior que o pai
    while(k>1 && heap[k] > heap[k/2])
    {
        //troca com o pai
        int aux = heap[k];
        heap[k] = heap[k/2];
        heap[k/2] = aux;

        k = k/2;
    }

    N++;
}

void push(int N, int x, int * heap)
{
    //se estiver vazia, só insira
    if(heap[N] == -1)
        heap[N] = x;

    //else insere na proxima posicao e chama siftup para organizar como maxheap
    else
    {
        heap[(++N)] = x;
        siftUp(N, heap);
    }
}

void siftDown(int k, int * heap)
{
    int filhoDir = (2*k) + 1;
    int filhoEsq = 2*k;

    //enquanto k tem filhos
    while((heap[filhoDir] == -1 || heap[filhoEsq] != -1)
            //e v[k] nao eh maior que ambos
            && (heap[k] < heap[filhoDir] || heap[k] < heap[filhoEsq]))
    {
        int L = 0;

        //L é o maior filho de v[k]
        if(heap[filhoEsq] > heap[filhoDir])
            L = filhoEsq;
        else
            L = filhoDir;

        //troca
        int aux = heap[k];
        heap[k] = heap[L];
        heap[L] = aux;

        //atualiza posições
        k=L;
        filhoDir = (2*k) + 1;
        filhoEsq = 2*k;
    }
}

void pop(int k, int * heap)
{
    //remove v[1] - faz o que quiser (retorna, ignora, etc)

    //troca a raiz com o ultimo elemento da folha e chama siftdown para arrumar maxheap
    heap[1] = heap[N];
    heap[N] = -1;
    N--;

    siftDown(1, heap);
}

//transforma vetor qualquer em uma maxheap
void heapfy(int * heap)
{
    for(int i=N; i>=1; i--)
        siftDown(i, heap);
}

//para testar algoritmo:
int main()
{
    int vet[] = {53,12,23,34,42,61};
    int tam = sizeof(vet)/sizeof(vet[0]) + 1;//vetor inicia em 1 entao termina em tam+1
    int * heap = (int*)malloc(tam * sizeof(int));
    int i = 0;

    //inicializa vetor com -1
    for(i=0; i<tam; i++)
        heap[i] = -1;

    for(i=0; i<tam-1; i++)//tam-1 pois só está inserindo a qtde de elementos no vet
        push(N, vet[i], heap);

    //pop(vet[2], heap);
    heapfy(heap);

    for(i=1; i<=N; i++)
        printf("%d ", heap[i]);

    free(heap);

    return 0;
}
