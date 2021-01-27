#include "Ordenadores.h"
using namespace std;
#include <random>
#include <chrono>
Ordenadores::Ordenadores()
{
    quantidadeComparacoes = 0;
    quantidadeTrocas =0;
}

Ordenadores::~Ordenadores() {}

void Ordenadores::intercala(Registro* registros,int inicio, int meio, int fim)
{
    //int numComparacao, numTroca;//
    int i,j,k;
    int tamVetL = meio-inicio+1; //tamanho do vetor temporario L
    int tamVetR = fim - meio; //tamanho do vetor temporario R

    // cria vetores temporarios
    Registro * L = new Registro[tamVetL];
    Registro * R = new Registro[tamVetR];


    //copia os dados para as arrays L e R
    for (i = 0; i < tamVetL; i++)
        L[i] = registros[inicio + i];
    for (j = 0; j < tamVetR; j++)
        R[j] = registros[meio + 1 + j];

    //Junta os vetores temporarios no vetor principal
    i = 0; // index inicial para a primeira subarray
    j = 0; // index inicial para a segunda subarray
    k = inicio; // index inicial para a merge subarray

    while (i < tamVetL && j < tamVetR)
    {
        // se cidade de L vier antes da cidade de R
        if (L[i].getEstado() < R[j].getEstado())
        {
            registros[k] = L[i];
            i++;
            k++;
            continue;
        }
        if (L[i].getEstado() == R[j].getEstado())
        {
            if(L[i].getCidade() < R[j].getCidade()){
                registros[k] = L[i];
                i++;
                k++;
                continue;
            }
            
        }
        if (L[i].getEstado() == R[j].getEstado() && L[i].getCidade() == R[j].getCidade())
        {
            if(L[i].getDataCompleta() < R[j].getDataCompleta()){
                registros[k] = L[i];
                i++;
                k++;
                continue;
            }
            
        }
        //else
        //{
            
            registros[k] = R[j];
            j++;
        //}


        k++;
    }

    // Copia os elementos restantes de L[ ]
    while (i < tamVetL)
    {
        
        registros[k] = L[i];
        i++;
        k++;
    }
    // Copia os elementos restantes de R[ ]
    while (j < tamVetR)
    {
        
        registros[k] = R[j];
        j++;
        k++;
    }
    delete [] L;
    delete [] R;
}

void Ordenadores::mergeSort(Registro* registros, int indexInicio, int indexFim)
{
    
    if(indexFim > indexInicio)
    {
        int meio = (indexInicio + indexFim)/2;      // pega o meio como parametro de index para as duas metades 
        mergeSort(registros, indexInicio, meio);   // na primeira metade ele vira o indexFim
        mergeSort(registros, meio+1, indexFim );  //na segunda metade ele+1 vira o indexInicio
        intercala(registros, indexInicio, meio, indexFim);
    }
    else return;

}
// Funcao serve para Heapifyzar uma subarvore com raiz que tem indice i
// obs : i eh um indice , n eh o tamanho da heap
void Ordenadores::heapify(Registro *registros , int n, int i)
{
	int maior = i;       // Maior eh iniciado como raiz
	int l = 2 * i + 1;  // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	if (l < n && registros[l].getEstado() > registros[maior].getEstado())
		maior = l;

	if (r < n && registros[r].getEstado() > registros[maior].getEstado())
		maior = r;

	// caso a maior nao seja igual a raiz mais por ter sido trocada
	if (maior != i) {
		swap(registros[i], registros[maior]);

		// vai descendo
		heapify(registros, n, maior);
	}
}

// Funcao principal para a heapSort
void Ordenadores::heapSort(Registro *registros , int n)
{
	// Constroi a heap maxima dentro do array
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(registros, n, i);

	// Vai ordenando um por um e parando de verificar oq ja esta ordenado
	for (int i = n - 1; i > 0; i--) {
		// manda a raiz atual que eh o maior valor para o final
		swap(registros[0], registros[i]);

		// rearranja a heap
		heapify(registros, i, 0);
	}
}



void Ordenadores::quickSort(Registro *registros,int inicio,int fim){
    int i, j;
	i = inicio;
	j = fim-1;
	int meio= (inicio + fim)/2;

        Registro a = registros[inicio];
        Registro b = registros[meio];
        Registro c = registros[fim];
        int medianaIndice; 
        
        if(a.getCasos() < b.getCasos()){
            if(b.getCasos() < c.getCasos()){
                //a < b && b < c
                medianaIndice = meio;
            }else{                
                if(a.getCasos() < c.getCasos()){
                    //a < c && c <= b
                    medianaIndice = fim;
                }else{
                    //c <= a && a < b
                    medianaIndice = inicio;
                }
            }
        }else{
            if(c.getCasos() < b.getCasos()){
                //c < b && b <= a
                medianaIndice = meio;
            }else{
                if(c.getCasos() < a.getCasos()){
                    //b <= c && c < a
                    medianaIndice = fim;
                }else{
                    //b <= a && a <= c
                    medianaIndice = inicio;
                }
            }
        }

    Registro pivo= registros[medianaIndice];

    
	while(i <= j)
	{
		while(registros[i].getCasos() < pivo.getCasos() && i < fim)
		{
			i++;
		}
		while(registros[j].getCasos() > pivo.getCasos() && j > inicio)
		{
			j--;
		}
		if(i <= j)
		{
            swap(registros[i],registros[j]);
			i++;
			j--;
		}
	}
	if(j > inicio)
		quickSort(registros, inicio, j+1);
	if(i < fim)
		quickSort(registros, i, fim);
}

int Ordenadores::getMax(Registro *registros, int n) 
{ 
    int mx = registros[0].getCasos(); 
    for (int i = 1; i < n; i++) 
        if (registros[i].getCasos() > mx) 
            mx = registros[i].getCasos(); 
    return mx; 
} 
  

void Ordenadores::countSort(Registro *registros, int n, int exp) 
{ 
    
    int i, cont[10] = {0}; 
    Registro *saida =  new Registro[n];
    
    for (i = 0; i < n; i++) 
        cont[(registros[i].getCasos() / exp) % 10]++; 
  
    
    for (i = 1; i < 10; i++) 
        cont[i] += cont[i - 1]; 
  
    
    for (i = n - 1; i >= 0; i--) { 
        saida[cont[(registros[i].getCasos() / exp) % 10] - 1] = registros[i]; 
        cont[(registros[i].getCasos() /exp) % 10]--; 
    } 
  
    
    for (i = 0; i < n; i++) 
        registros[i] = saida[i]; 
} 
  

void Ordenadores::radixsort(Registro *registros, int n) 
{ 
    
    int m = getMax(registros, n); 
  
    
    for (int exp = 1; m / exp > 0; exp *= 10) 
        countSort(registros, n, exp); 
} 

