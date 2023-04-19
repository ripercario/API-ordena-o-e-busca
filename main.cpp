#include "crow.h"
#include "final.h"
#include<random>
#include<chrono>
#include<ctime>
//#include "crow_all.h"
using namespace std;
int main()
{
    crow::SimpleApp app; //define your crow application

    //define your endpoint at the root directory
    CROW_ROUTE(app, "/")([](){

        

    random_device rd;
    uniform_int_distribution<int> distTAM(10000, 1000000);

    int size = distTAM(rd);
    int* vet = new int[size];
    int* vetaux = new int[size];    // vetor auxiliar para podermos imprimir o tempo dos 3 sorts de uma vez
    int* vetaux2 = new int[size];   // vetor auxiliar 2 para podermos imprimir o tempo dos 3 sorts de uma vez

    CriaVetRand(vet, size);
    SavingVet(vet, vetaux, size);
    SavingVet(vet, vetaux2, size);

    string merge = PrintTime(1, "Merge Sort", vet, size);
    string quick = PrintTime(2, "Quick Sort", vetaux, size);
    string insertion = PrintTime(3, "Insertion Sort", vetaux2, size);
    string binary = PrintTime(4, "Binary Search", vet, size);
    string linear = PrintTime(5, "Linear Search", vet, size);

        return merge + quick + insertion + binary + linear;
    });

    //set the port, set the app to run on multiple threads, and run the app
    app.bindaddr("127.0.0.1").port(18080).multithreaded().run();
}


