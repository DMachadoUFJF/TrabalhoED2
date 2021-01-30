#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <algorithm> // std::swap
#include<climits>
#include <stdio.h>
#include <string.h>
#include "Ordenadores.h"
#define TAMANHOMAX 1431490
#define NOMEARQUIVODATASET "brazil_covid19_cities.csv"

using namespace std;
using namespace std::chrono;

string TiraAcento(string paravla)
{
    for(int i=0; i<paravla.length(); i++)
    {
        if(int(paravla[i]) >= 192 && int(paravla[i]) <= 197)
            paravla[i] = 'A';
        if(int(paravla[i]) >= 224 && int(paravla[i]) <= 229)
            paravla[i] = 'a';
        if(int(paravla[i]) >= 200 && int(paravla[i]) <= 203)
            paravla[i] = 'E';
        if(int(paravla[i]) >= 232 && int(paravla[i]) <= 235)
            paravla[i] = 'e';
        if(int(paravla[i]) >= 204 && int(paravla[i]) <= 207)
            paravla[i] = 'I';
        if(int(paravla[i]) >= 236 && int(paravla[i]) <= 239)
            paravla[i] = 'i';
        if(int(paravla[i]) >= 210 && int(paravla[i]) <= 214)
            paravla[i] = 'O';
        if(int(paravla[i]) >= 242 && int(paravla[i]) <= 246)
            paravla[i] = 'o';
        if(int(paravla[i]) >= 217 && int(paravla[i]) <= 220)
            paravla[i] = 'U';
        if(int(paravla[i]) >= 249 && int(paravla[i]) <= 252)
            paravla[i] = 'u';
        if(int(paravla[i]) == 135)
            paravla[i] = 'c';
    }
    return paravla;
}
void leArquivo(Registro *r , int N , string nomeArquivo)
{

    ifstream arq(nomeArquivo);
    if (!arq.is_open())
    {
        cout << "Problema ao abrir o Arquivo!" << endl;
        return;
    }
    string dataCompleta, estado, cidade;
    int casos, mortes;
    int codigoCidade;
    string linha, stringTemporaria1, stringTemporaria2, stringTemporaria3;
    int cont=0;
    getline(arq,linha); //pula primeira linha
    while (getline(arq, linha))
    {

        stringstream ss(linha);
        getline(ss, dataCompleta, ',');
        r[cont].setDataCompleta(dataCompleta);
        getline(ss, estado, ',');
        r[cont].setEstado(estado);
        getline(ss, cidade, ',');
        r[cont].setCidade(cidade);
        getline(ss, stringTemporaria1, ',');
        istringstream(stringTemporaria1) >> codigoCidade;
        r[cont].setCodigoCidade(codigoCidade);
        getline(ss, stringTemporaria2, ',');
        istringstream(stringTemporaria2) >> casos;
        r[cont].setCasos(casos);
        getline(ss, stringTemporaria3, ',');
        istringstream(stringTemporaria3) >> mortes;
        r[cont].setMortes(mortes);

        if(cont>N)
        break;
        cont++;
        
    }
    cout << "Arquivo " << nomeArquivo<< " com "<<cont << " registros lido com sucesso!" << endl;
    arq.close();
}

void transformaCasosAcumuladosEmCasosDiarios(Registro *registros , int N){

    for(int i=1 ; i<N ; i++){
         
        if(registros[i].getCidade() == registros[i-1].getCidade()){
            registros[i].setCasos(registros[i].getCasos() - registros[i-1].getCasos());
        } 
    }
}
              
void escreveArquivoSaida(Registro *r, int size,string nomeSaidaArquivo)
{
   ofstream arq(nomeSaidaArquivo);
   cout<<"Escrevendo arquivo de saida..."<<endl;
    arq << "data,estado,nomeCidade,codigo,casos,mortes" << endl;
    for(int i = 1; i <= size; i++)
    {
        arq << r[i].getDataCompleta() << "," << r[i].getEstado()<<"," <<r[i].getCidade() <<","<<r[i].getCodigoCidade() <<
        "," <<r[i].getCasos()<<"," <<r[i].getMortes()<<endl;
    }
    arq.close(); 
}



// void ordenandoComHeapSort(Registro *registros , int N){
//     Ordenadores *ord = new Ordenadores();
//     high_resolution_clock::time_point inicio = high_resolution_clock::now();
//     leArquivo(registros,N,NOMEARQUIVODATASET);
//     cout<<"-----------------------------------------------"<<endl;
//     ord->heapSort(registros, N);
//     high_resolution_clock::time_point fim = high_resolution_clock::now();
//     //printArray(registros,N);
//     escreveArquivoSaida(registros,N,"brazil_covid19_cities_processado.csv");
//     cout<<"Fim da ordenacao com HeapSort"<<endl;
//     cout<< duration_cast<duration<double>>(fim-inicio).count()<<"s"<<endl;

// }


//Mudar para mergeSort 2 (Por Casos) e mudar o nome do arquivo
void ordenandoComMergeSort(Registro *registros , int N){
    Ordenadores *ord = new Ordenadores();
    
    leArquivo(registros,N,NOMEARQUIVODATASET);
    // cout<<"----------------------------------------------------------------------"<<endl;
    //  int mediaComparacao=0;
    //  int mediaTrocas=0;
    //  double mediaTempo=0;     

    // //5 = M 
    // for(int i=0;i<5;i++){
    //     cout<<"----------------------------------------------------------------------"<<endl;

        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        ord->mergeSort(registros,0, N);
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        // transformaCasosAcumuladosEmCasosDiarios(registros,N);


        // cout<<"Exececucao: "<<i<<endl;
        // cout<<"----------------------------------------------------------------------"<<endl;
        // mediaTempo=mediaTempo+(duration_cast<duration<double>>(fim-inicio).count());
        cout<<"Tempo:" <<duration_cast<duration<double>>(fim-inicio).count()<<"s"<<endl;
    //     mediaComparacao= mediaComparacao + ord->getQuantidadeComparacoes();;
    //     cout<<"Foram feitas:"<<ord->getQuantidadeComparacoes()<< " comparacoes "<<endl;
    //     cout<<"Foram feitas:"<<ord->getQuantidadeTrocas()<< " trocas"<<endl;
    //     mediaTrocas= mediaTrocas + ord->getQuantidadeTrocas();
    //     cout<<"----------------------------------------------------------------------"<<endl;

    // }
  
    // cout<<"Media de Tempo em 5 execs: "<<mediaTempo/5<<endl;
    // cout<<"Media de Comparacao em 5 execs: "<<mediaComparacao/5<<endl;
    // cout<<"Media de Trocas em 5 execs: "<<mediaTrocas/5<<endl;
    escreveArquivoSaida(registros,N,"brazil_covid19_cities_processados");
    
}

void ordenandoComQuickSort(Registro *registros , int N){
    Ordenadores *ord = new Ordenadores();
    leArquivo(registros,N,"brazil_covid19_cities_processados");
    cout<<"----------------------------------------------------------------------"<<endl;
     int mediaComparacao=0;
     int mediaTrocas=0;
     double mediaTempo=0;     

    //5 = M 
    for(int i=0;i<5;i++){
        cout<<"----------------------------------------------------------------------"<<endl;

        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        ord->quickSort(registros,0, N);
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        transformaCasosAcumuladosEmCasosDiarios(registros,N);


        cout<<"Exececucao: "<<i<<endl;
        cout<<"----------------------------------------------------------------------"<<endl;
        mediaTempo=mediaTempo+(duration_cast<duration<double>>(fim-inicio).count());
        cout<<"Tempo:" <<duration_cast<duration<double>>(fim-inicio).count()<<"s"<<endl;
        mediaComparacao= mediaComparacao + ord->getQuantidadeComparacoes();;
        cout<<"Foram feitas:"<<ord->getQuantidadeComparacoes()<< " comparacoes "<<endl;
        cout<<"Foram feitas:"<<ord->getQuantidadeTrocas()<< " trocas"<<endl;
        mediaTrocas= mediaTrocas + ord->getQuantidadeTrocas();
        cout<<"----------------------------------------------------------------------"<<endl;

    }
  
    cout<<"Media de Tempo em 5 execs: "<<mediaTempo/5<<endl;
    cout<<"Media de Comparacao em 5 execs: "<<mediaComparacao/5<<endl;
    cout<<"Media de Trocas em 5 execs: "<<mediaTrocas/5<<endl;
    
   

}
void ordenandoComShellSort(Registro *registros , int N){
    Ordenadores *ord = new Ordenadores();
    
   leArquivo(registros,N,"brazil_covid19_cities_processados");
    cout<<"----------------------------------------------------------------------"<<endl;
     int mediaComparacao=0;
     int mediaTrocas=0;
     double mediaTempo=0;     

    //5 = M 
    for(int i=0;i<5;i++){
        cout<<"----------------------------------------------------------------------"<<endl;

        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        ord->mergeSort(registros,0, N);
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        transformaCasosAcumuladosEmCasosDiarios(registros,N);


        cout<<"Exececucao: "<<i<<endl;
        cout<<"----------------------------------------------------------------------"<<endl;
        mediaTempo=mediaTempo+(duration_cast<duration<double>>(fim-inicio).count());
        cout<<"Tempo:" <<duration_cast<duration<double>>(fim-inicio).count()<<"s"<<endl;
        mediaComparacao= mediaComparacao + ord->getQuantidadeComparacoes();;
        cout<<"Foram feitas:"<<ord->getQuantidadeComparacoes()<< " comparacoes "<<endl;
        cout<<"Foram feitas:"<<ord->getQuantidadeTrocas()<< " trocas"<<endl;
        mediaTrocas= mediaTrocas + ord->getQuantidadeTrocas();
        cout<<"----------------------------------------------------------------------"<<endl;

    }
    
    cout<<"Media de Tempo em 5 execs: "<<mediaTempo/5<<endl;
    cout<<"Media de Comparacao em 5 execs: "<<mediaComparacao/5<<endl;
    cout<<"Media de Trocas em 5 execs: "<<mediaTrocas/5<<endl;
    

}
void OrdenadoresMenu(){

    int tamanhoN[] = {10000,50000,100000,500000,1000000,TAMANHOMAX};
    Registro *registros = new Registro[tamanhoN[5]];

    cout<<"Tamanho de Registros:"<<endl;
    cout<<"*10.000"<<endl;
    cout<<"*50.000"<<endl;
    cout<<"*100.000"<<endl;
    cout<<"*500.000"<<endl;
    cout<<"*1.000.000"<<endl;






}

void menu(){


    int tamanhoN[] = {10000,50000,100000,500000,1000000,TAMANHOMAX};
    Registro *registros = new Registro[tamanhoN[5]];

    int men;
    cout<<"===============Menu==============="<<endl;
    cout<<"[1]->Pré-processamento dos dados"<<endl;
    cout<<"[2]->Modulo de Teste"<<endl;
    cout<<"[3]->Finzaliza execucao"<<endl;
    cin>>men;

    if(men==1){
        //Fazer o pre processamento atraves do MergeSort
        ordenandoComMergeSort(registros,tamanhoN[5]);
        menu();
    }
    if(men==2){
        cout<<"===============Modulo de Teste==============="<<endl;
        cout<<"[1]->Acesso ao Algoritmos de Ordenação(MergeSort/QuickSort/ShellSort)"<<endl;
        cout<<"[2]->Saida no Console do Teste N=10"<<endl;
        cout<<"[3]->Saida em um Arquivo Txt do Teste N=100"<<endl;
        cin>>men;

        if(men==1){
            OrdenadoresMenu();

        }
         if(men==2){
            cout<<"IR AQUI A SAIDA NO CONSOLE"<<endl;

        }
         if(men==3){
            cout<<"IR AQUI A SAIDA EM TXT"<<endl;

        }
    }

    
}



int main()
{
    // Para rodar o programa :
    //  g++ -o teste -O3 *.cpp
    // ./teste

    int tamanhoN[] = {10000,50000,100000,500000,1000000,TAMANHOMAX};
    Registro *registros = new Registro[tamanhoN[5]];

    ordenandoComMergeSort(registros,tamanhoN[5]);

    //ordenandoComQuickSort(registros,tamanhoN[0]);
   // ordenandoComShellSort(registros,tamanhoN[5]);

    //delete[] registros;
    //menu();

    return 0;
}

