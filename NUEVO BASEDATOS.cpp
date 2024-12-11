#include <iostream>
#include "sqlite3.h"
#include <string>
#include <cstdlib>
#include "DBRegister.h"
using namespace std;

sqlite3* db;

//Abrir tabla y crear tablas
int OpenTable() {
    //abrir tabla
    int rc = sqlite3_open("mi_base_de_datos.db", &db);
    if (rc) {
        cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << endl;
        return rc;
    }
    else {
        cout << "Base de datos abierta correctamente." << endl;
    }

    // Crear las tablas
    const char* sqlCreatePacientes = "CREATE TABLE IF NOT EXISTS Pacientes (" \
        "NOMBRE TEXT NOT NULL," \
        "USUARIO TEXT NOT NULL," \
        "CONTRASENHA TEXT NOT NULL," \
        "CODIGO TEXT NOT NULL,";
    const char* sqlCreateCuidadores = "CREATE TABLE IF NOT EXISTS Cuidadores (" \
        "NOMBRE TEXT NOT NULL," \
        "USUARIO TEXT NOT NULL," \
        "CONTRASENHA TEXT NOT NULL," \
        "CODIGO TEXT NOT NULL);";

    const char* sqlCreateMedicos = "CREATE TABLE IF NOT EXISTS Medicos (" \
        "NOMBRE TEXT NOT NULL," \
        "USUARIO TEXT NOT NULL," \
        "CONTRASENHA TEXT NOT NULL," \
        "CODIGO TEXT NOT NULL);";


    char* errMsg = 0;
    rc = sqlite3_exec(db, sqlCreatePacientes, 0, 0, &errMsg);
    handleError(rc, errMsg);
    rc = sqlite3_exec(db, sqlCreateCuidadores, 0, 0, &errMsg);
    handleError(rc, errMsg);
    rc = sqlite3_exec(db, sqlCreateMedicos, 0, 0, &errMsg);
    handleError(rc, errMsg);
}

//Mensaje de error sql
void handleError(int rc, char* errMsg) {
    if (rc != SQLITE_OK) {
        cerr << "Error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

//Funcion para anhadir un nuevo paciente
void addPaciente(const string& nombre, const string& usuario, const string& contrasenha, const string& codigo) {
    string sql = "INSERT INTO Pacientes (NOMBRE, USUARIO, CONTRASENHA, CODIGO) VALUES ('" +
        nombre + "', '" + usuario + "', '" + contrasenha + "', '" + codigo + "');";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    handleError(rc, errMsg);
}

//Funcion para anhadir un nuevo cuidador
void addCuidador(const string& nombre, const string& usuario, const string& contrasenha, const string& codigo) {
    string sql = "INSERT INTO Cuidadores (NOMBRE, USUARIO, CONTRASENHA, CODIGO) VALUES ('" +
        nombre + "', '" + usuario + "', '" + contrasenha + "', '" + codigo + "');";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    handleError(rc, errMsg);
}

//Funcion apra anhadir un nuevo medico
void addMedico(const string& nombre, const string& usuario, const string& contrasenha, const string& codigo) {
    string sql = "INSERT INTO Medicos (NOMBRE, USUARIO, CONTRASENHA, CODIGO) VALUES ('" +
        nombre + "', '" + usuario + "', '" + contrasenha + "', '" + codigo + "');";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    handleError(rc, errMsg);
}

//Leer la base datos y comparar si es correcto las credenciales pacientes
bool readPacientes(const string& LoginUser, const string& LoginPass) {
    const char* sql = "SELECT * FROM Pacientes;";
    sqlite3_stmt* stmt;

    // Prepara la consulta SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Recorre los resultados de la consulta
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string Name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string User = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string Pass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        // Verifica si el usuario existe
        if (LoginUser == User) {
            // Verifica la contraseña
            if (LoginPass == Pass) {
                sqlite3_finalize(stmt);
                return true; // Inicio de sesión exitoso
            }
            else {
                cout << "\t**Contraseña incorrecta**" << endl;
                sqlite3_finalize(stmt);
                return false; // Contraseña incorrecta
            }
        }
    }

    cout << "\t**Usuario incorrecto**" << endl; // Usuario no encontrado
    sqlite3_finalize(stmt);
    return false; // Usuario no encontrado
}

//Leer la base datos y comparar si es correcto las credenciales cuidadores
bool readCuidadores(const string& LoginUser, const string& LoginPass) {
    const char* sql = "SELECT * FROM Cuidadores;";
    sqlite3_stmt* stmt;

    // Prepara la consulta SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Recorre los resultados de la consulta
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string Name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string User = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string Pass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        // Verifica si el usuario existe
        if (LoginUser == User) {
            // Verifica la contraseña
            if (LoginPass == Pass) {
                sqlite3_finalize(stmt);
                return true; // Inicio de sesión exitoso
            }
            else {
                cout << "\t**Contraseña incorrecta**" << endl;
                sqlite3_finalize(stmt);
                return false; // Contraseña incorrecta
            }
        }
    }

    cout << "\t**Usuario incorrecto**" << endl; // Usuario no encontrado
    sqlite3_finalize(stmt);
    return false; // Usuario no encontrado
}

//leer la base datos y comparar si es correcto la credenciales medicos
bool readMedicos(const string& LoginUser, const string& LoginPass) {
    const char* sql = "SELECT * FROM Medicos;";
    sqlite3_stmt* stmt;

    // Prepara la consulta SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Recorre los resultados de la consulta
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        string Name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string User = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string Pass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        // Verifica si el usuario existe
        if (LoginUser == User) {
            // Verifica la contraseña
            if (LoginPass == Pass) {
                sqlite3_finalize(stmt);
                return true; // Inicio de sesión exitoso
            }
            else {
                cout << "\t**Contraseña incorrecta**" << endl;
                sqlite3_finalize(stmt);
                return false; // Contraseña incorrecta
            }
        }
    }

    cout << "\t**Usuario incorrecto**" << endl; // Usuario no encontrado
    sqlite3_finalize(stmt);
    return false; // Usuario no encontrado
}

//NO REGISTRAR USUSRAIOS DOBLES
bool RepeatUserPacientes(const string& RegisterUser) {
    
    const char* sql = "SELECT * FROM Pacientes;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Falla al preparar la consulta:" << sqlite3_errmsg(db) << endl;
        return false;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* UserBase = sqlite3_column_text(stmt, 1);

        string User = reinterpret_cast<const char*>(UserBase);

        if (RegisterUser == User) {
            cout << "\t**Este usuario ya ah sido registrado**" << endl;
            return true;
        }
    }
    return false;
}

// registrar dobles pacientes
bool RepeatUserCuidadores(const string& RegisterUser) {

    const char* sql = "SELECT * FROM Cuidadores;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Falla al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* UserBase = sqlite3_column_text(stmt, 1);

        string User = reinterpret_cast<const char*>(UserBase);

        if (RegisterUser == User) {
            cout << "\t**Este usuario ya ah sido registrado**" << endl;
            return true;
        }
    }
    return false;
}

void Escribirnombre(const string& LoginUser, int Typeofaccount,string& Name,string& UserCode) {
    const char* Selecti = "SELECT * FROM Pacientes;";
    if (Typeofaccount == 1) 
        Selecti = "SELECT * FROM Pacientes;";
    if (Typeofaccount == 2)
        Selecti = "SELECT * FROM Cuidadores;";
    if (Typeofaccount == 3)
        Selecti = "SELECT * FROM Medicos;";
    const char* sql = Selecti;
        sqlite3_stmt* stmt;
   
    // Prepara la consulta SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;
        
    }
 
    // Recorre los resultados de la consulta
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        UserCode = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string User = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        // Verifica si el usuario existe
        if (LoginUser == User) {
            break;
            }
        }
    }
//ver pacientes
void buscarpacientes(const string& UserCode,string& Name) {
    const char* sql = "SELECT * FROM Pacientes;";
    sqlite3_stmt* stmt;
    string Code;
    // Prepara la consulta SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << endl;

    }

    // Recorre los resultados de la consulta
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        Code = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        // Verifica si el usuario existe
        if (Code == UserCode) 
            break;
    }
    if (Code != UserCode)
    cout << "\tNo existe este paciente" << endl;
}
