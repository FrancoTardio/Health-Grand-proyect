#ifndef DBREGISTER_H 
#define DBREGISTER_H
#include <iostream>
#include <string>
using namespace std;

int OpenTable();
void addCuidador(const string& nombre, const string& usuario, const string& contrasenha, const string& codigo);
void addPaciente(const string& nombre, const string& usuario, const string& contrasenha, const string& codigo);
void handleError(int rc, char* errMsg);
bool RepeatUser(const string& RegisterUser, int TyperOfAccount);
bool readPacientes(const string& LoginUser, const string& LoginPass);
bool readCuidadores(const string& LoginUser, const string& LoginPass);

#endif 
