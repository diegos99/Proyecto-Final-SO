#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <list>   
#include <vector>   
#include <stdlib.h>	 
#include <ctime>
#include <algorithm>
#include <cctype>
#include <iterator>
using namespace std;

struct ticket {
    string fila;
    string asiento;
    string sala;
};

struct header {
    string numeroMagico;
    string tamanoTexto;
    string tamanoBytes;
    string horaCreacion;
    string horaUltimoAcceso;
    string horaUltimaModificacion;
    string banderaAscii;
    string banderaArchivo;
    string banderaSistema;
    string banderaOculto;
    string banderaLectura;
    string creador;
    string propietario;
};

void escritura(vector<ticket> tickets);
vector<ticket> lectura();
bool is_number(const std::string& s);
string currentHour();

template <class Container>
void split1(const std::string& str, Container& cont, char delim = '=')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

template <class Container>
void split2(const std::string& str, Container& cont, char delim = '&')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

template <class Container>
void split3(const std::string& str, Container& cont, char delim = '|')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

constexpr unsigned int str2int(const char* str, int h = 0) //metodo para convertir de string a int
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

int main() {
    std::vector<ticket> ticketsComprados;
    std::vector<header> headersComprados;

    std::vector<ticket> ticketsReservados;

    ticketsComprados = lectura();

    while (true) {
        cout<< "Hola! Bienvenido al sistema de boletos de cine!" << endl; 
        cout<< "Selecciona una opcion:" << endl;

        cout << "1. Comprar un voleto" << endl;
        cout << "2. Reservar un voleto" << endl;
        cout << "3. Confirmar reservacion" << endl;
        cout << "4. Cancelar reservaciones por sala" << endl;
        cout << "5. Limpiar sala" << endl;
        cout << "6. Salir" << endl;

        string opcion = "";
        cin >> opcion; 
        string sala, fila, asiento;
        ticket t;

        switch (str2int(opcion.c_str()))
        {
        case str2int("1"):
            
            bool existC; 
            bool existCR;
            cout << "Ingresa la sala:" << endl;
            cin >> sala;
            cout << "Ingresa la fila:" << endl;
            cin >> fila;
            cout << "Ingresa el numero de asiento:" << endl;
            cin >> asiento;

            if (!is_number(sala) || !is_number(fila) || !is_number(asiento)) {
                cout << "Debes ingresar un digito!" << endl;
                break;
            }

            for (int i = 0; i < ticketsComprados.size(); i++) {
                if (sala == ticketsComprados[i].sala && fila == ticketsComprados[i].fila && asiento == ticketsComprados[i].asiento) {
                    cout << "Este asiento ya se ha comprado!" << endl;
                    existC = true;
                    break;
                }
            }
            
            for (int i = 0; i < ticketsReservados.size(); i++) {
                if (sala == ticketsReservados[i].sala && fila == ticketsReservados[i].fila && asiento == ticketsReservados[i].asiento) {
                    cout << "Este asiento ya ha sido reservdo!" << endl;
                    existCR = true;
                    break;
                }
            }

            if (!existC && !existCR) {
                t.asiento = asiento;
                t.fila = fila;
                t.sala = sala;
                ticketsComprados.push_back(t);
                escritura(ticketsComprados);

                cout << "Listo! Tu compra se ha registrado!" << endl;
            }
            break;
        case str2int("2"):

            bool existR; 
            bool existRC;
            cout << "Ingresa la sala:" << endl;
            cin >> sala;
            cout << "Ingresa la fila:" << endl;
            cin >> fila;
            cout << "Ingresa el numero de asiento:" << endl;
            cin >> asiento;

            if (!is_number(sala) || !is_number(fila) || !is_number(asiento)) {
                cout << "Debes ingresar un digito!" << endl;
                break;
            }

            for (int i = 0; i < ticketsReservados.size(); i++) {
                if (sala == ticketsReservados[i].sala && fila == ticketsReservados[i].fila && asiento == ticketsReservados[i].asiento) {
                    cout << "Este asiento ya ha sido reservdo!" << endl;
                    existR = true;
                    break;
                }
            }

            for (int i = 0; i < ticketsComprados.size(); i++) {
                if (sala == ticketsComprados[i].sala && fila == ticketsComprados[i].fila && asiento == ticketsComprados[i].asiento) {
                    cout << "Este asiento ya se ha comprado!" << endl;
                    existRC = true;
                    break;
                }
            }

            if (!existR && !existRC) {
                t.asiento = asiento;
                t.fila = fila;
                t.sala = sala;
                ticketsReservados.push_back(t);

                cout << "Listo! Tu reservacion se ha registrado!" << endl;
            }
            break;    
        case str2int("3"):
            bool confirmado;
            cout << "Ingresa la sala:" << endl;
            cin >> sala;
            cout << "Ingresa la fila:" << endl;
            cin >> fila;
            cout << "Ingresa el numero de asiento:" << endl;
            cin >> asiento;

            if (!is_number(sala) || !is_number(fila) || !is_number(asiento)) {
                cout << "Debes ingresar un digito!" << endl;
                break;
            }

            for (int i = 0; i < ticketsReservados.size(); i++) {
                if (sala == ticketsReservados[i].sala && fila == ticketsReservados[i].fila && asiento == ticketsReservados[i].asiento) {
                    ticketsComprados.push_back(ticketsReservados[i]);
                    ticketsReservados.erase(ticketsReservados.begin() + i);
                    confirmado = true;
                }
            }
            escritura(ticketsComprados);
            if (confirmado){
                cout << "Listo! Tu reservacion se ha confirmado!" << endl;
            } else {
                cout << "No existe una reservacion con esos datos!" << endl;
            }
            
            break;
        case str2int("4"):
            cout << "Ingresa la sala:" << endl;
            cin >> sala;

            if (!is_number(sala)) {
                cout << "Debes ingresar un digito!" << endl;
                break;
            }

            for (int i = 0; i < ticketsReservados.size(); i++) {
                if (sala == ticketsReservados[i].sala) {
                    ticketsReservados.erase(ticketsReservados.begin() + i);
                }
            }

            cout << "Listo! Las reservaciones de la sala " << sala << " han sido canceladas!" << endl;
            break;
        case str2int("5"):
            cout << "Ingresa la sala:" << endl;
            cin >> sala;

            if (!is_number(sala)) {
                cout << "Debes ingresar un digito!" << endl;
                break;
            }

            for (int i = 0; i < ticketsReservados.size(); i++) {
                if (sala == ticketsReservados[i].sala) {
                    ticketsReservados.erase(ticketsReservados.begin() + i);
                }
            }

            for (int i = 0; i < ticketsComprados.size(); i++) {
                if (sala == ticketsComprados[i].sala) {
                    ticketsComprados.erase(ticketsComprados.begin() + i);
                }
            }
            escritura(ticketsComprados);

            cout << "Listo! La sala " << sala << " se ha limpiado completamente!" << endl;
            break;
        case str2int("6"):
            escritura(ticketsComprados);
            ticketsComprados.clear();
            ticketsReservados.clear();
            cout << "Hasta luego!" << endl;
            return 0;
            break;
        default:
            cout << "Por favor selecciona una opcion valida." << endl;
        }
    }
    return 0;
}

void escritura(vector<ticket> tickets) {
	
	int i; 
	
	ofstream documento("tickets.txt",ios::out); 	//Crear manejador (documento),abrir archivo creado (doc)
	
	
	if(documento.fail()){						//Verificar archivo creado correctamente, devuelve valor tipo bool
		printf("Falla al crear/abrir archivo"); //mensaje de falla del programa
		exit(1);								//salir de programa
	}

    string document;
    header encabezado;
    string encabezadoTexto;

	for(i=0; i<tickets.size(); i++) {
        document = tickets[i].sala+"|"+tickets[i].fila+"|"+tickets[i].asiento;
        
        encabezado.numeroMagico = to_string(i);
        encabezado.tamanoTexto = to_string(sizeof(document));
        encabezado.tamanoBytes = to_string(sizeof(document));
        encabezado.horaCreacion = currentHour();
        encabezado.horaUltimoAcceso = currentHour();
        encabezado.horaUltimaModificacion = currentHour();
        encabezado.banderaAscii = "0";
        encabezado.banderaArchivo = "0";
        encabezado.banderaSistema = "0";
        encabezado.banderaOculto = "0";
        encabezado.banderaLectura = "0";
        encabezado.creador = "DiegoJavier";
        encabezado.propietario = "DiegoJavier";

        encabezadoTexto = encabezado.numeroMagico+"|"+encabezado.tamanoTexto+"|"+encabezado.tamanoBytes+"|"+encabezado.horaCreacion+"|"+
            encabezado.horaUltimoAcceso+"|"+encabezado.horaUltimaModificacion+"|"+encabezado.banderaAscii+"|"+encabezado.banderaArchivo+"|"+
            encabezado.banderaSistema+"|"+encabezado.banderaOculto+"|"+encabezado.banderaLectura+"|"+encabezado.creador+"|"+encabezado.propietario;

		documento<<encabezadoTexto<<"&"<<document<<"=";
	}
	documento.close();							//Cerrar archivo por medio de manejador
}

vector<ticket> lectura() {
    int i; 									//contador
    vector<ticket> data;

	fstream documento("tickets.txt",ios::in);	//manejador (documento),abrir archivo a leer (doc)
	
	if (documento.fail()){
        
	}
	std::stringstream buffer;
    buffer << documento.rdbuf();
    string value = buffer.str();

    std::vector<std::string> tickets;
    split1(value, tickets);

    vector<string> values;
    vector<string> ticketValue;
    for (i = 0; i<tickets.size(); i++) {
        values.clear();
        ticketValue.clear();
        split2(tickets[i], values);

        split3(values[1], ticketValue);

        ticket t;
        t.sala = ticketValue[0];
        t.fila = ticketValue[1];
        t.asiento = ticketValue[2];

        data.push_back(t);
    }

    return data;
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

string currentHour() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string str(buffer);

    return str;
}