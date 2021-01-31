#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <algorithm> // std::swap
#include <climits>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include "Ordenadores.h"
//
#define TAMANHOMAX 1431490
#define NOMEARQUIVODATASET "brazil_covid19_cities.csv"

using namespace std;
using namespace std::chrono;



void ordenandoComMergeSort(Registro *registros, int N)
{
    Ordenadores *ord = new Ordenadores();

    registros->leArquivo(registros,N,"brazil_covid19_cities_processados.csv");
    // cout<<"----------------------------------------------------------------------"<<endl;
    //  int mediaComparacao=0;
    //  int mediaTrocas=0;
    //  double mediaTempo=0;

    // //5 = M
    // for(int i=0;i<5;i++){
    //     cout<<"----------------------------------------------------------------------"<<endl;

    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    //ord->mergeSort(registros, 0, N);
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    // transformaCasosAcumuladosEmCasosDiarios(registros,N);

    // cout<<"Exececucao: "<<i<<endl;
    // cout<<"----------------------------------------------------------------------"<<endl;
    // mediaTempo=mediaTempo+(duration_cast<duration<double>>(fim-inicio).count());
    cout << "Tempo:" << duration_cast<duration<double>>(fim - inicio).count() << "s" << endl;
    //     mediaComparacao= mediaComparacao + ord->getQuantidadeComparacoes();;
    //     cout<<"Foram feitas:"<<ord->getQuantidadeComparacoes()<< " comparacoes "<<endl;
    //     cout<<"Foram feitas:"<<ord->getQuantidadeTrocas()<< " trocas"<<endl;
    //     mediaTrocas= mediaTrocas + ord->getQuantidadeTrocas();
    //     cout<<"----------------------------------------------------------------------"<<endl;

    // }

    // cout<<"Media de Tempo em 5 execs: "<<mediaTempo/5<<endl;
    // cout<<"Media de Comparacao em 5 execs: "<<mediaComparacao/5<<endl;
    // cout<<"Media de Trocas em 5 execs: "<<mediaTrocas/5<<endl;
    //escreveArquivoSaida(registros,N,"brazil_covid19_cities_processados.csv");
}

void ordenandoComQuickSort(Registro *registros, int N)
{
    Ordenadores *ord = new Ordenadores();
    registros->leArquivo(registros, N, "brazil_covid19_cities_processados");
    cout << "----------------------------------------------------------------------" << endl;
    int mediaComparacao = 0;
    int mediaTrocas = 0;
    double mediaTempo = 0;

    //5 = M
    for (int i = 0; i < 5; i++)
    {
        cout << "----------------------------------------------------------------------" << endl;

        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        ord->quickSort(registros, 0, N);
        high_resolution_clock::time_point fim = high_resolution_clock::now();

        cout << "Exececucao: " << i << endl;
        cout << "----------------------------------------------------------------------" << endl;
        mediaTempo = mediaTempo + (duration_cast<duration<double>>(fim - inicio).count());
        cout << "Tempo:" << duration_cast<duration<double>>(fim - inicio).count() << "s" << endl;
        mediaComparacao = mediaComparacao + ord->getQuantidadeComparacoes();
        ;
        cout << "Foram feitas:" << ord->getQuantidadeComparacoes() << " comparacoes " << endl;
        cout << "Foram feitas:" << ord->getQuantidadeTrocas() << " trocas" << endl;
        mediaTrocas = mediaTrocas + ord->getQuantidadeTrocas();
        cout << "----------------------------------------------------------------------" << endl;
    }

    cout << "Media de Tempo em 5 execs: " << mediaTempo / 5 << endl;
    cout << "Media de Comparacao em 5 execs: " << mediaComparacao / 5 << endl;
    cout << "Media de Trocas em 5 execs: " << mediaTrocas / 5 << endl;
}
void ordenandoComShellSort(Registro *registros, int N)
{
    Ordenadores *ord = new Ordenadores();

    registros->leArquivo(registros, N, "brazil_covid19_cities_processados");
    cout << "----------------------------------------------------------------------" << endl;
    int mediaComparacao = 0;
    int mediaTrocas = 0;
    double mediaTempo = 0;

    //5 = M
    for (int i = 0; i < 5; i++)
    {
        cout << "----------------------------------------------------------------------" << endl;

        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        ord->shellSort(registros, N);
        high_resolution_clock::time_point fim = high_resolution_clock::now();

        cout << "Exececucao: " << i << endl;
        cout << "----------------------------------------------------------------------" << endl;
        mediaTempo = mediaTempo + (duration_cast<duration<double>>(fim - inicio).count());
        cout << "Tempo:" << duration_cast<duration<double>>(fim - inicio).count() << "s" << endl;
        mediaComparacao = mediaComparacao + ord->getQuantidadeComparacoes();
        ;
        cout << "Foram feitas:" << ord->getQuantidadeComparacoes() << " comparacoes " << endl;
        cout << "Foram feitas:" << ord->getQuantidadeTrocas() << " trocas" << endl;
        mediaTrocas = mediaTrocas + ord->getQuantidadeTrocas();
        cout << "----------------------------------------------------------------------" << endl;
    }

    cout << "Media de Tempo em 5 execs: " << mediaTempo / 5 << endl;
    cout << "Media de Comparacao em 5 execs: " << mediaComparacao / 5 << endl;
    cout << "Media de Trocas em 5 execs: " << mediaTrocas / 5 << endl;
}
void OrdenadoresMenu()
{

    int tamanhoN[] = {10000, 50000, 100000, 500000, 1000000, TAMANHOMAX};
    Registro *registros = new Registro[tamanhoN[5]];

    cout << "Tamanho de Registros:" << endl;
    cout << "*10.000" << endl;
    cout << "*50.000" << endl;
    cout << "*100.000" << endl;
    cout << "*500.000" << endl;
    cout << "*1.000.000" << endl;
}

void menu()
{

    int tamanhoN[] = {10000, 50000, 100000, 500000, 1000000, TAMANHOMAX};
    Registro *registros = new Registro[tamanhoN[5]];
    Registro *registrosAux =new Registro[1000000];//tamanho máximo que pode ter

    int men;
    cout << "===============Menu===============" << endl;
    cout << "[1]->Pre-processamento dos dados" << endl;
    cout << "[2]->Modulo de Teste" << endl;
    cout << "[3]->Etapa 2 do Trab -> trocar nome dps" << endl;
    cout << "[4]->Finzaliza execucao" << endl;
    cin >> men;

    if (men == 1)
    {
        //Fazer o pre processamento atraves do MergeSort
        registros->preProcessamentoComMergeSort(registros, tamanhoN[5]);
        registros->selecionandoRegistrosAleatorios(registros,registrosAux,100000);// apagar
        registrosAux->escreveArquivoSaidaCsv(registrosAux,100000,"teste.csv");//apagar
        menu();
    }
    if (men == 2)
    {
        cout << "===============Modulo de Teste===============" << endl;
        cout << "[1]->Pre-processamento dos dados" << endl;
        cout << "[2]->Importação de N registros aleatórios" << endl;
        cout << "[3]->Cada um dos algoritmos de ordenação" << endl;
        cin >> men;

        if (men == 1)
        {
            cout << "[1]->Saida no Console do Teste N=10" << endl;
            cout << "[2]->Saida em um Arquivo Txt do Teste N=100" << endl;
        }
        if (men == 2)
        {
            cout << "[1]->Saida no Console do Teste N=10" << endl;
            cout << "[2]->Saida em um Arquivo Txt do Teste N=100" << endl;
        }
        if (men == 3)
        {
            cout << "[1]->Saida no Console do Teste N=10" << endl;
            cout << "[2]->Saida em um Arquivo Txt do Teste N=100" << endl;
        }
    }
}


int main()
{
    menu();
    
    return 0;
}

//  g++ -o teste -O3 *.cpp
