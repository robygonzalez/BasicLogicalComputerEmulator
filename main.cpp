/*
 Roberta González Garza     A01570010
 Jorge Sosa                 A01039913
 Emulador.cpp  Es un programa que imita a un compilador de una máquina simple hipotética.
 Febrero 19, 2018
 */

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void Muestra (int AC, int IR, int PC, int MAR, int MDR, int FR) {
// función que recibe como parámetros los registros y los imprime
    cout << "AC: " << AC <<endl;
    cout << "IR: " << IR <<endl;
    cout << "PC: " << PC <<endl;
    cout << "MAR: " << MAR <<endl;
    cout << "MDR: " << MDR <<endl;
    cout << "FR: " << FR <<endl;
    cout << "-------" <<endl;
    cin.ignore();  //presiona enter para avanzar
}

/*
TODAS las funciones sirven para llevar acabo una microoperación
 Parámetros: reciben los registros con una referencia y la memoria principal
 Regresa: nada, es función void
*/


void LDA(int &AC, int &IR, int &PC, int &MAR, int &MDR, int &FR, int MM[]) {
    int dir;
    char op;
    
    cout << "Escriba el tipo de direccionamiento: " <<endl;
    cout << "1) Absoluto \t 2) Inmediato" <<endl;
    cout << "3) Indirecto \t 4) Relativo" <<endl;
    cin >> op;

    if (op == '1') {
        do {
            cout << "Escriba la dirección donde se encuentra el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 500)); //valida para que esté entre esos espacios de memoria
        MM[IR] += 2000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        AC = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '2') {
        do {
            cout << "Escriba el dato. Este debe tener 5 dígitos y 1 signo " <<endl;
            cin >> dir;
        } while (dir > 1000); //valida para que sea de máximo 3 dígitos
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        AC = dir;
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra el AC con la nueva dirección
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR);
    }
    else if (op == '3') {
        do {
            cout << "Escriba la dirección donde se encuentra la dirección que contiene el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 0)); //valida para que esté en la memoria
        MM[IR] += 3000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        MAR = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar con el nuevo mdr
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr con el nuevo dato
        AC = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac con el mdr
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '4') {
        do {
            cout << "Escriba la cantidad que quiere sumar al pc. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir; //no valida porque es un dato que puede ser negativo
        } while ((dir > 1000) || (dir < -1000)); //no es mayor a 3 dígitos
        MM[IR] += 1000; //guarda el tipo de direccionamiento en la memoria
        if (dir > 0) { //si es positivo
            MM[IR] += dir; //guarda el código de la dirección en la memoria
        }
        else {
            dir *= -1; //lo escribe positivo porque no se puede ponerlo negativo sin que todo el código de la MM cambie
            MM[IR] += dir;
        }
        MM[IR] += 1000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = PC + dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        AC = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
}

void STA(int &AC, int &IR, int &PC, int &MAR, int &MDR, int &FR, int MM[]) {
    int dir;
    char op;
    cout << "Escriba el tipo de direccionamiento: " <<endl;
    cout << "1) Absoluto \t 2) Indirecto \t 3) Relativo" <<endl;
    cin >> op;
    
    if (op == '1') {
        do {
            cout << "Escriba la dirección donde se encuentra el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 500)); //valida para que esté entre esos espacios de memoria
        MM[IR] += 2000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        MDR = AC;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr con el ac
        MM[MAR] = AC; //guarda el ac en la nueva dirección
        cout << "MMWrite" <<endl;
        cin.ignore();  //presiona enter para avanzar
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '2') {
        do {
            cout << "Escriba la dirección donde se encuentra la dirección que contiene el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 0)); //valida para que esté en la memoria
        MM[IR] += 3000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        MAR = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar con el nuevo mdr
        MDR = AC;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr con el ac
        MM[MAR] = MDR; //guarda el ac en la nueva dirección
        cout << "MMWrite" <<endl;
        cin.ignore();  //presiona enter para avanzar
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '3') {
        do {
            cout << "Escriba la cantidad que quiere sumar al pc. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir; //no valida porque es un dato que puede ser negativo
        } while ((dir > 1000) || (dir < -1000)); //no es mayor a 3 dígitos
        MM[IR] += 1000; //guarda el tipo de direccionamiento en la memoria
        if (dir > 0) { //si es positivo
            MM[IR] += dir; //guarda el código de la dirección en la memoria
        }
        else {
            dir *= -1; //lo escribe positivo porque no se puede ponerlo negativo sin que todo el código de la MM cambie
            MM[IR] += dir;
        }
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = PC + dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        MDR = AC;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        MM[MAR] = MDR; //guardas el acumulador en memoria
        cout << "MMWrite";
        cin.ignore();  //presiona enter para avanzar
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
}

void CLA(int &AC, int &IR, int &PC, int &MAR, int &MDR, int &FR, int MM[]) {
    AC = 0; //limpia el acumulador
    Muestra(AC, IR, PC, MAR, MDR, FR); //muestra registros
}

void ADD(int &AC, int &IR, int &PC, int &MAR, int &MDR, int &FR, int MM[]) {
    int dir;
    char op;
    cout << "Escriba el tipo de direccionamiento: " <<endl;
    cout << "1) Absoluto \t 2) Inmediato" <<endl;
    cout << "3) Indirecto \t 4) Relativo" <<endl;
    cin >> op;
    
    if (op == '1') { //absoluto
        do {
            cout << "Escriba la dirección donde se encuentra el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 500)); //valida para que esté entre esos espacios de memoria
        MM[IR] += 2000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        AC += MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '2') { //inmediato
            do {
            cout << "Escriba el dato. Este debe tener 5 dígitos y 1 signo " <<endl;
            cin >> dir;
        } while (dir > 100000); //valida para que sea menor a 6 dígitos
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        AC += dir;
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra el AC con la nueva dirección
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR);
    }
    else if (op == '3') { //indirecto
        do {
            cout << "Escriba la dirección donde se encuentra la dirección que contiene el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 0)); //valida para que esté en la memoria
        MM[IR] += 3000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        MAR = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar con el nuevo mdr
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr con el nuevo dato
        AC += MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac con el mdr
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '4') { //relativo
        cout << "Escriba la cantidad que quiere sumar al pc. Esta debe estar entre el espacio 500 y 999: " <<endl;
        cin >> dir; //no valida porque es un dato que puede ser negativo
        MM[IR] += 1000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = PC + dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        AC += MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
}

void SUB(int &AC, int &IR, int &PC, int &MAR, int &MDR, int &FR, int MM[]) {
    int dir;
    char op;
    cout << "Escriba el tipo de direccionamiento: " <<endl;
    cout << "1) Absoluto \t 2) Inmediato" <<endl;
    cout << "3) Indirecto \t 4) Relativo" <<endl;
    cin >> op;
    
    if (op == '1') {
        do {
            cout << "Escriba la dirección donde se encuentra el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 500)); //valida para que esté entre esos espacios de memoria
        MM[IR] += 2000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        AC -= MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '2') {
        do {
            cout << "Escriba el dato. Este debe tener 5 dígitos y 1 signo " <<endl;
            cin >> dir;
        } while (dir > 100000); //valida para que sea menor a 6 dígitos
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        AC -= dir;
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra el AC con la nueva dirección
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR);
    }
    else if (op == '3') {
        do {
            cout << "Escriba la dirección donde se encuentra la dirección que contiene el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 0)); //valida para que esté en la memoria
        MM[IR] += 3000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        MAR = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar con el nuevo mdr
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr con el nuevo dato
        AC -= MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac con el mdr
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '4') {
        cout << "Escriba la cantidad que quiere sumar al pc. Esta debe estar entre el espacio 500 y 999: " <<endl;
        cin >> dir; //no valida porque es un dato que puede ser negativo
        MM[IR] += 1000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = PC + dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        AC -= MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac
        IR++;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
}

void NOP(int &AC, int &IR, int &PC, int &MAR, int &MDR, int &FR, int MM[]) {
    Muestra(AC, IR, PC, MAR, MDR, FR); //muestra los registros originales
    cin.ignore(); //arregla un error con el muestra
    IR++;
    PC++;
    Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
}

void NEG(int &AC, int &IR, int &PC, int &MAR, int &MDR, int &FR, int MM[]) {
    Muestra(AC, IR, PC, MAR, MDR, FR); //muestra los registros originales
    cin.ignore(); //arregla un error con el muestra
    AC *= -1; //hace positivo el acumulador
    Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el acumulador
    IR++;
    PC++;
    Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
}

void JMP(int &AC, int &IR, int &PC, int &MAR, int &MDR, int &FR, int MM[]) {
    int dir;
    char op;
    
    cout << "Escriba el tipo de direccionamiento: " <<endl;
    cout << "1) Absoluto \t 2) Inmediato" <<endl;
    cout << "3) Indirecto \t 4) Relativo" <<endl;
    cin >> op;
    
    if (op == '1') {
        do {
            cout << "Escriba la dirección donde se encuentra el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 500)); //valida para que esté entre esos espacios de memoria
        MM[IR] += 2000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir;
        Muestra(AC, IR, PC, MAR, MDR, FR); //guarda la dirección en el mar
        cout << "MMRead" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //guarda el dato en el mdr
        PC = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //le suma el dato al pc
        IR = PC;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '2') {
        do {
            cout << "Escriba el dato. Este debe tener 5 dígitos y 1 signo " <<endl;
            cin >> dir;
        } while (dir > 1000); //valida para que sea de máximo 3 dígitos
        MM[IR] += 2000; //guarda el tipo de direccionamiento en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        PC = dir;
        Muestra(AC, IR, PC, MAR, MDR, FR); //le suma el dato al pc
        IR = PC;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
        
    }
    else if (op == '3') {
        do {
            cout << "Escriba la dirección donde se encuentra la dirección que contiene el dato. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir;
        } while ((dir > 1000) || (dir < 0)); //valida para que esté en la memoria
        MM[IR] += dir; //guarda el código de la dirección en la memoria
        Muestra(AC, IR, PC, MAR, MDR, FR); //muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        MAR = dir; //el mar es la nueva dirección
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr
        MAR = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mar con el nuevo mdr
        cout << "MMread" <<endl;
        cin.ignore();  //presiona enter para avanzar
        MDR = MM[MAR];
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el mdr con el nuevo dato
        PC = MDR;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el ac con el mdr
        IR = PC;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
    else if (op == '4') {
        do {
            cout << "Escriba la cantidad que quiere sumar al pc. Esta debe estar entre el espacio 500 y 999: " <<endl;
            cin >> dir; //no valida porque es un dato que puede ser negativo
        } while ((dir > 1000) || (dir < -1000)); //no es mayor a 3 dígitos
        MM[IR] += 1000; //guarda el tipo de direccionamiento en la memoria
        if (dir > 0) { //si es positivo
            MM[IR] += dir; //guarda el código de la dirección en la memoria
        }
        else {
            dir *= -1; //lo escribe positivo porque no se puede ponerlo negativo sin que todo el código de la MM cambie
            MM[IR] += dir;
        }
        Muestra(AC, IR, PC, MAR, MDR, FR); //Muestra los registros originales
        cin.ignore(); //arregla un error con el muestra
        PC += dir;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el pc
        IR = PC;
        PC++;
        Muestra(AC, IR, PC, MAR, MDR, FR); //actualiza el IR y PC
    }
}

int main() {
    int MM[1000] {}; //crea la memoria principal
    MM[900] =123;
    char op;
    int PC = 2, IR = 1, FR = 0, AC = 0, MAR = 0, MDR = 0;

    do {
        cout << "Eliga el número de la instrucción que quiere hacer: " <<endl;
        cout << "1) LDA \t 2) STA \t 3) CLA \t 4)ADD" <<endl;
        cout << "5) SUB \t 6) NOP \t 7) NEG \t 8)JMP \t 9)HLT" <<endl;
        cin >> op;
        
        if (op == '1') {
            MM[IR] = 100000; //guarda el código de LDA en la memoria
            LDA(AC, IR, PC, MAR, MDR, FR, MM) ;
            cout << "Acabó la operación LDA" <<endl;
        }
        else if (op == '2') {
            MM[IR] = 110000; //guarda el código de STA en la memoria
            STA(AC, IR, PC, MAR, MDR, FR, MM);
            cout << "Acabó la operación STA" <<endl;
        }
        else if (op == '3') {
            MM[IR] = 10000; //guarda el código de CLA en la memoria
            CLA(AC, IR, PC, MAR, MDR, FR, MM);
            cout << "Acabó la operación CLA" <<endl;
        }
        else if (op == '4') {
            MM[IR] = 200000; //guarda el código de ADD en la memoria
            ADD(AC, IR, PC, MAR, MDR, FR, MM);
            cout << "Acabó la operación ADD" <<endl;
        }
        else if (op == '5') {
            MM[IR] = 210000; //guarda el código de SUB en la memoria
            SUB(AC, IR, PC, MAR, MDR, FR, MM);
            cout << "Acabó la operación SUB" <<endl;
        }
        else if (op == '6') {
            //no guarda código en la memoria porque es un nop y el código es 00
            NOP(AC, IR, PC, MAR, MDR, FR, MM);
            cout << "Acabó la operación NOP" <<endl;
        }
        else if (op == '7') {
            MM[IR] = 20000; //guarda el código de NEG en la memoria
            NEG(AC, IR, PC, MAR, MDR, FR, MM);
            cout << "Acabó la operación NEG" <<endl;
        }
        else if (op == '8') {
            MM[IR] = 300000; //guarda el código de JMP en la memoria
            JMP(AC, IR, PC, MAR, MDR, FR, MM);
        }
        else if (op == '9') {
            MM[IR] = 990000; //guarda el código de HLT en la memoria
            cout << "Acabó el programa" <<endl;
        }
    }while (op != '9'); //Para cuando se eliga la opción de terminar
}
