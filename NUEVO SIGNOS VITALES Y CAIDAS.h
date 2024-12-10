#ifndef DETECTORDECAIDAS_H
#define DETECTORDECAIDAS_H
#include <iostream>
#include <string>
using namespace std;

void SignosVitales(string UserCode);
void SimularSignos(string UserCode);
void PacienteSignos(string Name, string UserCode);
void Alertas(int RCardi, int Respir, int Temp, int PArteri, int Caida);
#endif 
#include <cstdlib>
#include <fstream>
#include "sqlite3.h"
#include "DBRegister.h"


void SignosVitales(string UserCode) {
    ifstream SignosLeer(UserCode);
    int dat1 = 0, dat2 = 0, dat3 = 0, dat4 = 0, dat5 = 0;
    if (SignosLeer.is_open()) {
        SignosLeer >> dat1;
        SignosLeer >> dat2;
        SignosLeer >> dat3;
        SignosLeer >> dat4;
        SignosLeer >> dat5;
        SignosLeer.close();
    }
    Alertas(dat1, dat2, dat3, dat4, dat5);
    cout << "\tRITMO CARDIACO " << dat1 << endl;
    cout << "\tFRECUENCIA RESPIRATORIA " << dat2 << endl;
    cout << "\tTEMPERATURA " << dat3 << endl;
    cout << "\tPRESION ARTERIAL " << dat4 << endl;
}

void SimularSignos(string UserCode) {
    int option;
    ifstream SignosLeer(UserCode);
    int data1, data2, data3, data4, data5;
    if (SignosLeer.is_open()) {
        SignosLeer >> data1;
        SignosLeer >> data2;
        SignosLeer >> data3;
        SignosLeer >> data4;
        SignosLeer >> data5;
        SignosLeer.close();
    }
    do {
        cout << "\t\t\t\t" << endl;
        cout << "\t*-*-*-*-*-*-*\t" << endl;
        cout << "\tHealth-Grand\t" << endl;
        cout << "\t1.simular ritmocardiaco\t" << endl;
        cout << "\t2.simular frecuencia respiratoria\t" << endl;
        cout << "\t3.simular temperatura\t" << endl;
        cout << "\t4.simular presion arterial\t" << endl;
        cout << "\t5.simular caida\t" << endl;
        cout << "\t0.atras\t" << endl;
        cout << "\t*-*-*-*-*-*-*\t" << endl;
        cout << "\t\t\t\t" << endl;
        cin >> option;
        cin.ignore();
        system("cls");
        switch (option)
        {
        case 1:
            cout << "\tINGRESE RITMO CARDIACO" << endl;
            cin >> data1;
            cin.ignore();
            system("cls");
            break;
        case 2:
            cout << "\tINGRESE FRECUENCIA RESPIRATORIA" << endl;
            cin >> data2;
            cin.ignore();
            system("cls");
            break;
        case 3:
            cout << "\tINGRESE TEMPERATURA" << endl;
            cin >> data3;
            cin.ignore();
            system("cls");
            break;
        case 4:
            cout << "\tINGRESE PRESION ARTERIAL" << endl;
            cin >> data4;
            cin.ignore();
            system("cls");
            break;
        case 5:
            do {
                cout << "\t1.SIMULAR CAIDA" << endl;
                cout << "\t0.PARAR SIMULAR CAIDA" << endl;
                cin >> data5;
                cin.ignore();
                system("cls");
            } while (data5 > 1 && data5 < 0);
            break;
        case 0:
            cout << "\tSaliendo" << endl;
            break;
        default:
            cout << "\tOpcion no permitida";
            break;
        }
        ofstream SignosEscribir(UserCode);
        if (SignosEscribir.is_open()) {
            SignosEscribir << data1 << "\n";
            SignosEscribir << data2 << "\n";
            SignosEscribir << data3 << "\n";
            SignosEscribir << data4 << "\n";
            SignosEscribir << data5 << "\n";
        }

    } while (option != 0);
}

void PacienteSignos(string Name, string UserCode) {
    int option;

    do {

        cout << "\t\t\t\t" << endl;
        cout << "\t*-*-*-*-*-*-*\t" << endl;
        cout << "\tHealth-Grand\t" << endl;
        cout << "\t" << Name << endl;
        cout << "\tSignos Vitales\t" << endl;
        SignosVitales(UserCode);
        cout << "\t1.Actualizar\t" << endl;
        cout << "\t2.Atras\t" << endl;
        cout << "\t0.Salir\t" << endl;
        cout << "\t*-*-*-*-*-*-*\t" << endl;
        cout << "\t\t\t\t" << endl;
        cin >> option;
        cin.ignore();
        system("cls");
        switch (option)
        {
        case 1:

            break;
        case 2:
            break;
        case 0:
            cout << "\tSaliendo" << endl;
            exit(0);
            break;
        default:
            cout << "\tOpcion no permitida";
            break;
        }
    } while (option != 2);
}

void Alertas(int RCardi, int Respir, int Temp, int PArteri, int Caida) {
    if (RCardi > 110 || RCardi < 60 || Respir > 20 || Respir < 12 || Temp > 37 || Temp < 37 || PArteri > 120 || PArteri < 90)
        cout << "\tSignos Vitales anormales porfavor Revisar" << endl;
    if (Caida == 1) {
        cout << "\tPosible Caida detectada" << endl;
    }
}
