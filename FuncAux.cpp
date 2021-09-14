/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncAux.cpp
 * Author: jhenn
 * Codigo: 20182841
 * Created on 14 de septiembre de 2021, 04:19 PM
 */

#include "FuncAux.h"
#include <iostream>        
#include <iomanip>
#include <fstream>

#define MAX 150
using namespace std;

void muestraDatosArchBin() {

    ifstream RegBin("registro.bin", ios::in | ios::binary);
    if (!RegBin) {
        cout << "No se puede abrir el archivo Registro.txt" << endl;
        exit(1);
    }
    int cliente, dd, mm, aa, serie, sec, referencia;
    char doc[4];
    double monto;

    int tamArch, numReg, tamReg = sizeof (int)*7 + sizeof (char)*4 + sizeof (double);

    RegBin.seekg(0, ios::end);
    tamArch = RegBin.tellg();
    RegBin.seekg(0, ios::beg);

    numReg = tamArch / tamReg;

    for (int i = 0; i < numReg; i++) {
        RegBin.read(reinterpret_cast<char*> (&cliente), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&dd), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&mm), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&aa), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&doc), sizeof (char)*4);
        RegBin.read(reinterpret_cast<char*> (&serie), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&sec), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&monto), sizeof (double));
        RegBin.read(reinterpret_cast<char*> (&referencia), sizeof (int));

        cout << left << setw(15) << cliente << setw(3) << dd << setw(3) << setw(5) << mm << setw(15) <<
                aa << setw(15) << doc << setw(15) << serie << setw(15) << sec << setw(15) << monto <<
                setw(15) << referencia << endl;
    }

    cout << endl << endl;

}

void generarArchBin() {

    ifstream ArchReg("Registro.txt", ios::in);
    if (!ArchReg) {
        cout << "No se puede abrir el archivo Registro.txt" << endl;
        exit(1);
    }

    ofstream RegBin("registro.bin", ios::out | ios::binary);
    if (!RegBin) {
        cout << "No se puede abrir el archivo registro.bin" << endl;
        exit(1);
    }

    int cliente, dd, mm, aa, serie, sec, referencia;
    char doc[4], aux;
    double monto;

    while (1) {
        ArchReg>>cliente;
        if (ArchReg.eof()) break;
        ArchReg >> dd >> aux >> mm >> aux>>aa;
        ArchReg >> doc >> serie >> aux >> sec >> monto>>referencia;

        RegBin.write(reinterpret_cast<const char*> (&cliente), sizeof (int));
        RegBin.write(reinterpret_cast<const char*> (&dd), sizeof (int));
        RegBin.write(reinterpret_cast<const char*> (&mm), sizeof (int));
        RegBin.write(reinterpret_cast<const char*> (&aa), sizeof (int));
        RegBin.write(reinterpret_cast<const char*> (&doc), sizeof (char)*4);
        RegBin.write(reinterpret_cast<const char*> (&serie), sizeof (int));
        RegBin.write(reinterpret_cast<const char*> (&sec), sizeof (int));
        RegBin.write(reinterpret_cast<const char*> (&monto), sizeof (double));
        RegBin.write(reinterpret_cast<const char*> (&referencia), sizeof (int));

    }
    ArchReg.close();
    RegBin.close();

    muestraDatosArchBin();
}

double buscarPrecio(int mm, int aa, int prod) {

    ifstream ArchPrec("Precios.txt", ios::in);
    if (!ArchPrec) {
        cout << "No se puede abrir el archivo Precios.txt" << endl;
        exit(1);
    }

    int fecha = aa * 10000 + mm * 100, mmA, aaA, codprod;
    char aux;
    double precio;

    ArchPrec>>mmA;
    while (1) {
        if (ArchPrec.eof()) break;
        ArchPrec >> aux>>aaA;

        int fecha1 = mmA * 100 + aaA * 10000;
        while (1) {
            ArchPrec>>codprod;
            if (codprod < 13) { //es un mes
                mmA = codprod;
                break;
            }
            ArchPrec>>precio;
            if (fecha == fecha1 && codprod == prod) {
                return precio;
            }
        }
    }
    return -1.0;

}

double procesarDevoluciones(int mm, int aa, int referencia) {


    ifstream ArchDev("Devolucion.txt", ios::in);
    if (!ArchDev) {
        cout << "No se puede abrir el archivo Registro.txt" << endl;
        exit(1);
    }
    double sumaMonto = 0, precio;
    int docDev, ddA, mmA, aaA, prod, cant;
    char aux;

    while (1) {
        ArchDev>>docDev;
        if (ArchDev.eof()) break;
        ArchDev >> ddA >> aux >> mmA >> aux>>aaA;
        ArchDev >> prod>>cant;

        if (docDev == referencia) {
            precio = buscarPrecio(mm, aa, prod);
            if (precio != -1) sumaMonto += precio * cant;
        }
    }
    ArchDev.close();
    return sumaMonto;


}

void corregirArchBin() {

    fstream RegBin("registro.bin", ios::in | ios::out | ios::binary);
    if (!RegBin) {
        cout << "No se puede abrir el archivo registro.bin" << endl;
        exit(1);
    }
    int cliente, dd, mm, aa, serie, sec, referencia;
    char doc[4];
    double monto, montoCorrecto;

    int tamArch, numReg, tamReg = sizeof (int)*7 + sizeof (char)*4 + sizeof (double);

    RegBin.seekg(0, ios::end);
    tamArch = RegBin.tellg();
    RegBin.seekg(0, ios::beg);

    numReg = tamArch / tamReg;

    for (int i = 0; i < numReg; i++) {
        RegBin.read(reinterpret_cast<char*> (&cliente), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&dd), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&mm), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&aa), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&doc), sizeof (char)*4);
        RegBin.read(reinterpret_cast<char*> (&serie), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&sec), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&monto), sizeof (double));
        RegBin.read(reinterpret_cast<char*> (&referencia), sizeof (int));


        if (sec != referencia) { //es Nota de credito
            montoCorrecto = procesarDevoluciones(mm, aa, referencia);

            RegBin.seekg(i * tamReg + (sizeof (int)*6 + sizeof (char)*4), ios::beg); //retrocedo al monto
            RegBin.write(reinterpret_cast<const char*> (&montoCorrecto), sizeof (double));
            RegBin.read(reinterpret_cast<char*> (&referencia), sizeof (int));

        }

    }
    muestraDatosArchBin();
}

void imprimirLinea(ofstream &Rep, char c, int cant) {
    Rep.fill(c);
    Rep << setw(cant) << c << endl;
    Rep.fill(' ');
}

void generarRepRegistroVentas() {

    ifstream RegBin("registro.bin", ios::in | ios::binary);
    if (!RegBin) {
        cout << "No se puede abrir el archivo Registro.txt" << endl;
        exit(1);
    }

    ofstream Rep("reporte.txt", ios::out);

    int cliente, dd, mm, aa, serie, sec, referencia;
    char doc[4];
    double monto, sumaMont = 0;

    int tamArch, numReg, tamReg = sizeof (int)*7 + sizeof (char)*4 + sizeof (double);

    RegBin.seekg(0, ios::end);
    tamArch = RegBin.tellg();
    RegBin.seekg(0, ios::beg);

    numReg = tamArch / tamReg;

    Rep << left << "REGISTRO DE VENTAS" << endl;
    imprimirLinea(Rep, '=', MAX);
    Rep << setw(20) << "FECHA" << setw(20) << "CLIENTE" << setw(20) << "TIPO" << setw(20) << "DOCUMENTO" <<
            setw(20) << "MONTO" << setw(20) << "IGV" << setw(20) << "MONTO TOTAL" << "REFERENCIA" << endl;
    imprimirLinea(Rep, '-', MAX);

    for (int i = 0; i < numReg; i++) {
        RegBin.read(reinterpret_cast<char*> (&cliente), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&dd), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&mm), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&aa), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&doc), sizeof (char)*4);
        RegBin.read(reinterpret_cast<char*> (&serie), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&sec), sizeof (int));
        RegBin.read(reinterpret_cast<char*> (&monto), sizeof (double));
        RegBin.read(reinterpret_cast<char*> (&referencia), sizeof (int));


        Rep << right << setfill('0') << setw(2) << dd << '/' << setw(2) << mm << '/' << aa << setfill(' ');
        Rep << left << setw(10) << ' ';
        Rep << left << setw(20) << cliente << setw(20)<<doc << right << setfill('0') << setw(4) << serie << '-' << setfill(' ');
        Rep << left << setw(10) << sec << setprecision(2) << fixed << right << setw(10)<<monto;
        Rep << left << setw(20) << ' ' << referencia << endl;

        sumaMont += monto;
    }
    imprimirLinea(Rep, '=', MAX);
    Rep << "RESUMEN:" << endl;
    Rep << "SALDO FINAL:" << right << setw(15) << monto << endl;

}