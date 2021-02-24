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
};

struct ColaEspera{
    struct Cliente *cliente;
    struct ColaEspera *sigCola;
};

struct PilaCarr{
    struct Carreta *carreta;
    struct PilaCarr *sigPila;
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
    printf("Se van a crear las pilas de las carretas con cantidad: %i\n",cantCarretPila);
    crearPilasCarr(pilaCarr1);
    printf("Se crearon las pilas de las carretas1\n");
    crearPilasCarr(pilaCarr2);
    printf("Se crearon las pilas de las carretas2\n");
    setNuevasCarretas();
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

