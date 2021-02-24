#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
 
 /*INICIALIZACION DE ESTRUCTURAS A UTILIZAR*/
struct Carreta {
   int  codigoCar;
};

struct Cliente {
   int  codigoCli;
   struct Carreta *carretaU;
};

struct Caja {
   int  codigoCaja;
   int  tiempo;
   short int  estado;
   struct Cliente *clienteA;
   struct Carreta *carretaU;
   struct Caja *sigCaja;   
   struct Caja *antCaja;
};

struct ColaEspera{
    struct Cliente *cliente;
    struct ColaEspera *sigCola;
};

struct PilaCarr{
    struct Carreta *carreta;
    struct PilaCarr *sigPila;
};

struct ListaCompras{
    struct Cliente *cliente;
    struct ListaCompras *sigLis;
    struct ListaCompras *antLis;
};

/*INICIALIZACION FUNCIONES*/
void menu();
void inicializarParametros();
void printPaso();
int getNumAleatorio0a100();
int getNumAleatorio1a2();
void setNuevosClientes();
void crearPilasCarr();
void setNuevasCarretas();
void setClientesCompras();
void setNuevasCajas();
void setClientesColaPagos();
void setNuevosClientesEnColaPagos();
void setNuevosClientesEnCompras();

/*INICIALIZACION PARAMETROS GLOBALES*/
int cantClientesIni;
int cantCarretPila;
int cantClientesComp;
int cantClientesColaP;
int cantCajas;
int numPaso;
int codigoClientes;
int MCarretas = 4;

struct ColaEspera *colaInicial;
struct PilaCarr *pilaCarr1;
struct PilaCarr *pilaCarr2;
struct ListaCompras *listaCompras;
struct Caja *cajaInicial;
struct ColaEspera *colaPagosInicial;


int main(){    
    srand (time(NULL));
    numPaso = 0;
    inicializarParametros();
    menu();
    return 0;    
}

/*Metodo inicial que inicializa la estructuras en memoria*/
void inicializarParametros(){
    colaInicial = (struct ColaEspera *)malloc(sizeof(struct ColaEspera));
    colaInicial->cliente = NULL;
    colaInicial->sigCola = NULL;
    pilaCarr1 = (struct PilaCarr *)malloc(sizeof(struct PilaCarr));
    pilaCarr1->carreta = NULL;
    pilaCarr1->sigPila = NULL;
    pilaCarr2 = (struct PilaCarr *)malloc(sizeof(struct PilaCarr));
    pilaCarr2->carreta = NULL;
    pilaCarr2->sigPila = NULL;
    listaCompras = (struct ListaCompras *)malloc(sizeof(struct ListaCompras));
    listaCompras->sigLis = NULL;
    listaCompras->antLis = NULL;
    listaCompras->cliente = NULL;
    cajaInicial = (struct Caja *)malloc(sizeof(struct Caja));
    cajaInicial->sigCaja = NULL;
    cajaInicial->antCaja = NULL;
    cajaInicial->clienteA = NULL;
    cajaInicial->carretaU = NULL;
    cajaInicial->codigoCaja = 1;
    cajaInicial->estado = 0;
    cajaInicial->tiempo = rand () % (5)+1;
    colaPagosInicial = (struct ColaEspera *)malloc(sizeof(struct ColaEspera));
    colaPagosInicial->cliente = NULL;
    colaPagosInicial->sigCola = NULL;
}

/* Menu de inicio 
 *  Metodo que se utiliza para pedir los parametros iniciales
*/
void menu(){
    cantCarretPila = 0;
    printf("********************** MENU ********************** \n");
    printf("Ingrese los parametros requeridos \n");
    printf("Ingrese la cantidad de clientes inicial \n");
    scanf("%d", &cantClientesIni);
    while(cantCarretPila < MCarretas/2){
        printf("Ingrese la cantidad de carretas por pila \n");
        scanf("%d", &cantCarretPila);    
    }    
    printf("Ingrese la cantidad de clientes comprando \n");
    scanf("%d", &cantClientesComp);
    printf("Ingrese la cantidad de clientes en cola de pagos \n");
    scanf("%d", &cantClientesColaP);
    printf("Ingrese la cantidad de cajas \n");
    scanf("%d", &cantCajas);
    printf("************** INICIO DE SIMULACION ************** \n");
    printPaso();
    setNuevosClientes(cantClientesIni);
    crearPilasCarr(pilaCarr1);
    crearPilasCarr(pilaCarr2);
    setNuevosClientesEnColaPagos();
    setNuevosClientesEnCompras();
    setNuevasCarretas();
    setNuevasCajas();
}

void printPaso(){
    printf("******************** Paso %3i ******************** \n",numPaso);
}

/*Metodo que se utiliza para obtener un numero aleatorio de 0 a 100*/
int getNumAleatorio0a100(){
    int numA;
    numA = rand () % (100-0+1)+0;
    return numA;
}

/*Metodo que se utiliza para obtener un numero aleatorio de 1 a 2*/
int getNumAleatorio1a2(){
    int numA;
    numA = rand () % (2-1+1)+1;
    return numA;
}

/*Metodo que agrega a los nuevos clientes a la cola de espera de carretas*/
void setNuevosClientes(int cantClientes){    
    struct ColaEspera *ct; 
    struct Cliente *clienteNuevo;

    if (colaInicial->sigCola == NULL)
    {
        clienteNuevo = (struct Cliente *)malloc(sizeof(struct Cliente));
        clienteNuevo->codigoCli = codigoClientes;
        ct = (struct ColaEspera *)malloc(sizeof(struct ColaEspera));
        ct->sigCola = NULL;
        ct->cliente = NULL;
        colaInicial->cliente = clienteNuevo;
        colaInicial->sigCola = ct;       
        codigoClientes++;
        printf("Se ingreso el cliente con codigo %i exitosamente\n",clienteNuevo->codigoCli); 
        setNuevosClientes(cantClientes-1);
    }else{
        ct = colaInicial;
        while(ct != NULL){
            if(ct->sigCola == NULL){
                break;  
            }              
            ct = ct->sigCola;        
        }
        for(int i = 0; i < cantClientes; i++){
            struct ColaEspera *colaNueva;       
            struct Cliente *clienteNuevo2;
            clienteNuevo2 = (struct Cliente *)malloc(sizeof(struct Cliente));         
            colaNueva = (struct ColaEspera *)malloc(sizeof(struct ColaEspera));  
            clienteNuevo2->codigoCli = codigoClientes;                
            colaNueva->cliente = NULL;
            colaNueva->sigCola = NULL;
            ct->cliente = clienteNuevo2;
            ct->sigCola = colaNueva;
            ct = colaNueva;
            codigoClientes++;
            printf("Se ingreso el cliente con codigo %i exitosamente\n",clienteNuevo2->codigoCli);             
        }
    } 
}

/*Metodo que inicializa alguna pila en su cantidad maxima de espacios*/
void crearPilasCarr(struct PilaCarr *pilaUsar){
    struct PilaCarr *pilaTemp;
    pilaTemp = pilaUsar;
    for(int i = 0; i < cantCarretPila ; i++){
        struct PilaCarr *pilaNueva;
        pilaNueva = (struct PilaCarr *)malloc(sizeof(struct PilaCarr));
        pilaNueva->carreta = NULL;
        pilaNueva->sigPila = NULL;
        pilaTemp->sigPila = pilaNueva;
        pilaTemp = pilaNueva;
    }    
}

/*Metodo que se usa para ingresar una carreta al final de una pila*/
int setCarretasEnPila(struct PilaCarr *pilaC,struct Carreta *carretaIns){
    short int estaLlena = 1;
    struct PilaCarr *pilaTemp;
    pilaTemp = pilaC;     
    for(int i = 0; i < cantCarretPila ; i++){
        if(pilaTemp->carreta == NULL){
            pilaTemp->carreta = carretaIns;
            estaLlena = 0;
            break;  
        }              
        pilaTemp = pilaTemp->sigPila;
    }
    return estaLlena;
}

/*Metodo que solicita el numero de pila a insertar la carreta
 *y la inserta, si la pila esta llena escoge la otra pila.
*/
void setCarretaEnPila(struct Carreta *carretaNueva){    
    int numPila = getNumAleatorio1a2();        
    if (numPila == 1)
    {            
        int estaLlena = setCarretasEnPila(pilaCarr1,carretaNueva);
        if (estaLlena = 1){
            //Se ingresa la carreta en la pila 2 porque la 1 esta llena
            estaLlena = setCarretasEnPila(pilaCarr2,carretaNueva);                
        }
    }else{
        int estaLlena = setCarretasEnPila(pilaCarr2,carretaNueva);
        if (estaLlena = 1)
        {
            //Se ingresa la carreta en la pila 1 porque la 2 esta llena
            estaLlena = setCarretasEnPila(pilaCarr1,carretaNueva);
        } 
    }
    printf("Se inserto la carreta con codigo: %i en la pila %i\n",carretaNueva->codigoCar,numPila);
}

/*Metodo se usa para crear todas las carretas solicitadas*/
void setNuevasCarretas(){    
    int codigosCarreta = 0;
    for(int i = 0 ; i < MCarretas ; i++){
        struct Carreta *carretaNueva;
        struct PilaCarr *pilaNueva;  
        carretaNueva = (struct Carreta *)malloc(sizeof(struct Carreta));
        carretaNueva->codigoCar = codigosCarreta;
        setCarretaEnPila(carretaNueva);
        codigosCarreta++;                  
    }
}

/*Metodo agrega a clientes a la lista de compras*/
void setClientesCompras(struct Cliente *clienteIns){
    struct ListaCompras *listTemp;
    if (listaCompras->sigLis == NULL){
        listTemp = (struct ListaCompras *)malloc(sizeof(struct ListaCompras));
        listTemp->sigLis = listaCompras;
        listTemp->antLis = listaCompras;
        listaCompras->cliente = clienteIns;
        listaCompras->sigLis = listTemp;  
        listaCompras->antLis = listTemp;
        printf("Se inserto el cliente con codigo: %i en compras\n",clienteIns->codigoCli);
    }else{                
        struct ListaCompras *nuevaList;
        nuevaList = (struct ListaCompras *)malloc(sizeof(struct ListaCompras));
        listTemp = listaCompras->antLis;
        listTemp->sigLis = nuevaList;            
        nuevaList->sigLis = listaCompras;
        nuevaList->antLis = listTemp;
        listaCompras->antLis = nuevaList;
        listTemp->cliente = clienteIns;
        printf("Se inserto el cliente con codigo: %i en compras\n",clienteIns->codigoCli);
    }
}

/*Metodo que crea la lista de las cajas*/
void setNuevasCajas(){
    struct Caja *cajaTemp;
    cajaTemp = cajaInicial;
    for(int i = 0 ; i < cantCajas ; i++){
        struct Caja *cajaNueva;
        cajaNueva = (struct Caja *)malloc(sizeof(struct Caja));
        cajaTemp->sigCaja = cajaNueva;        
        cajaNueva->antCaja = cajaTemp;
        cajaNueva->codigoCaja = i+2;
        cajaNueva->estado = 0;
        cajaNueva->tiempo = rand () % (5)+1;
        cajaTemp = cajaNueva;
    }
    printf("Se insertaron %i cajas\n",cantCajas);
}

/*Metodo que inserta a algun cliente en la cola de pagos*/
void setClientesColaPagos(struct Cliente *clienteIns){
    struct ColaEspera *colaTemp;
    if (colaPagosInicial->sigCola == NULL)
    {
        colaTemp = colaPagosInicial;
    }else{
        colaTemp = colaPagosInicial;
        while (colaTemp != NULL)
        {
            if (colaTemp->sigCola == NULL)
            {
                break;
            }            
            colaTemp = colaTemp->sigCola;            
        }        
    }    
    struct ColaEspera *colaNueva;
    colaNueva = (struct ColaEspera *)malloc(sizeof(struct ColaEspera));
    colaNueva->sigCola = NULL;
    colaNueva->cliente = NULL;
    colaTemp->sigCola = colaNueva;
    colaTemp->cliente = clienteIns;
    printf("Se inserto el cliente con codigo: %i en cola de Pagos\n",clienteIns->codigoCli);
}


void setNuevosClientesEnColaPagos(){
    for(int i = 0; i< cantClientesColaP; i++){
        struct Cliente *clienteNuevo;
        clienteNuevo = (struct Cliente *)malloc(sizeof(struct Cliente));
        clienteNuevo->codigoCli = codigoClientes;
        setClientesColaPagos(clienteNuevo);
        codigoClientes++;
    }
}

void setNuevosClientesEnCompras(){
    for(int i = 0; i< cantClientesComp; i++){
        struct Cliente *clienteNuevo;
        clienteNuevo = (struct Cliente *)malloc(sizeof(struct Cliente));
        clienteNuevo->codigoCli = codigoClientes;
        setClientesCompras(clienteNuevo);
        codigoClientes++;
    }
}