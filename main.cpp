/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* LAB3-2019-2
 * File:   main.cpp
 * Author: Jhenny Cervera Vargas
 * Codigo: 20182841
 * Created on 13 de septiembre de 2021, 07:35 PM
 */


#include <iostream>
#include <iomanip>    
#include <fstream>
using namespace std;

#include "FuncAux.h"

/*
 * 
 */
int main(int argc, char** argv) {

    generarArchBin();
    corregirArchBin();    
    generarRepRegistroVentas();
    
    return 0;
}

