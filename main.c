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

/*INICIALIZACION PARAMETROS GLOBALES*/
int cantClientesIni;
int cantCarretPila;
int cantClientesComp;
int cantClientesColaP;
int cantCajas;
int numPaso;
int codigoClientes;
int MCarretas = 5;

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
    cantCarretPila = 1000;
    printf("********************** MENU ********************** \n");
    printf("Ingrese los parametros requeridos \n");
    printf("Ingrese la cantidad de clientes inicial \n");
    scanf("%d", &cantClientesIni);
    while(cantCarretPila/2 >= MCarretas){
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

void setNuevasCarretas(){    
    int codigosCarreta = 0;
    for(int i = 0 ; i < MCarretas ; i++){
        struct Carreta *carretaNueva;
        struct PilaCarr *pilaNueva;  
        int numPila = getNumAleatorio1a2;
        if (numPila == 1)
        {
            if (pilaCarr1->sigPila = NULL)
            {
                carretaNueva = (struct Carreta *)malloc(sizeof(struct Carreta));
                carretaNueva->codigoCar = codigosCarreta;
                pilaNueva = (struct PilaCarr *)malloc(sizeof(struct PilaCarr));
                pilaNueva->sigPila = NULL;
                pilaNueva->carreta = NULL;
                pilaCarr1->carreta = carretaNueva;
                pilaCarr1->sigPila = pilaNueva;                       
                printf("Se ingreso nueva carreta a pila 1 con codigo %i exitosamente\n",carretaNueva->codigoCar); 
            }else{
                struct PilaCarr *pilaTemp;
                pilaTemp = pilaCarr1;
                while(pilaTemp != NULL){
                    if(pilaTemp->sigPila == NULL){
                        break;  
                    }              
                    pilaTemp = pilaTemp->sigPila;        
                }
                carretaNueva = (struct Carreta *)malloc(sizeof(struct Carreta));
                carretaNueva->codigoCar = codigosCarreta;
                pilaNueva = (struct PilaCarr *)malloc(sizeof(struct PilaCarr));
                pilaNueva->sigPila = NULL;
                pilaNueva->carreta = NULL;
                pilaTemp->carreta = carretaNueva;
                pilaTemp->sigPila = pilaNueva;                       
                printf("Se ingreso nueva carreta a pila 1 con codigo %i exitosamente\n",carretaNueva->codigoCar); 
            }
            
        }else{

        }
        codigosCarreta++;
                  
    }
}
