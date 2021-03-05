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
   int tiempoPas;
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

//#include "Graficar.h"

/*INICIALIZACION FUNCIONES*/
void menu();
void inicializarParametros();
void printPaso();
int  getNumAleatorio0a100();
int  getNumAleatorio1a2();
void setNuevosClientes();
void crearPilasCarr();
void setNuevasCarretas();
void setClientesCompras();
void setNuevasCajas();
void setClientesColaPagos();
void setNuevosClientesEnColaPagos();
void setNuevosClientesEnCompras();
void siguientePaso();
void validaAcciones();
void validarSalidaCajas();
void validarAcciones();
void ingresarClientesAColaCompras();
void ingresarClientesACajas();
void ingresarClientesAColaPagos();
void ingresarClientesCompras();
int  contarCarretasEnPila();
void sacarClienteColaInicial();
void graficar();
void graficarColaInicial();
void graficarCarretas();
void graficarCompras();
void graficarColaPagos();
void graficarCajas();

/*INICIALIZACION PARAMETROS GLOBALES*/
int cantClientesIni;
int cantCarretPila;
int cantClientesComp;
int cantClientesColaP;
int cantCajas;
int numPaso;
int codigoClientes;
int codigosCarreta;
int MCarretas = 6;
int MCarretas2;

struct ColaEspera *colaInicial;
struct PilaCarr *pilaCarr1;
struct PilaCarr *pilaCarr2;
struct ListaCompras *listaCompras;
struct Caja *cajaInicial;
struct ColaEspera *colaPagosInicial;


int main(){    
    //revisar();
    srand (time(NULL));
    numPaso = 0;
    inicializarParametros();
    menu();
    siguientePaso();    
    return 0;    
}

/*Metodo inicial que inicializa la estructuras en memoria*/
void inicializarParametros(){
    cantClientesComp = MCarretas+1;
    cantClientesColaP = MCarretas+1;
    codigosCarreta = 0;
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
    int MCarretasTemp = MCarretas;
    printf("********************** MENU ********************** \n");
    printf("Ingrese los parametros requeridos \n");
    printf("Ingrese la cantidad de clientes inicial \n");
    scanf("%d", &cantClientesIni);
    while(cantCarretPila < MCarretas/2){
        printf("Ingrese la cantidad de carretas por pila \n");
        scanf("%d", &cantCarretPila);    
    }

    while(cantClientesComp > MCarretasTemp){
        printf("Ingrese la cantidad de clientes comprando \n");
        scanf("%d", &cantClientesComp);
        if (cantClientesComp > MCarretasTemp)
        {
            printf("No puede ingresar mas clientes que la cantidad de carretas restante\n");
        }
    }
    MCarretasTemp = MCarretasTemp-cantClientesComp;

    while(cantClientesColaP > MCarretasTemp){
        printf("Ingrese la cantidad de clientes en cola de pagos \n");
        scanf("%d", &cantClientesColaP);
        if (cantClientesColaP > MCarretasTemp)
        {
            printf("No puede ingresar mas clientes que la cantidad de carretas restante\n");
        }
    }
    MCarretasTemp = MCarretasTemp-cantClientesColaP;
    MCarretas2 = MCarretasTemp;


    printf("Ingrese la cantidad de cajas \n");
    scanf("%d", &cantCajas);
    printf("************** INICIO DE SIMULACION ************** \n");
    printPaso();
    setNuevosClientes(cantClientesIni);
    crearPilasCarr(pilaCarr1);
    crearPilasCarr(pilaCarr2);
    setNuevosClientesEnCompras();
    setNuevosClientesEnColaPagos();
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
    if(cantClientes > 0){

    
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
        if (estaLlena == 1){
            //Se ingresa la carreta en la pila 2 porque la 1 esta llena
            estaLlena = setCarretasEnPila(pilaCarr2,carretaNueva);                
        }
    }else{
        int estaLlena = setCarretasEnPila(pilaCarr2,carretaNueva);
        if (estaLlena ==1)
        {
            //Se ingresa la carreta en la pila 1 porque la 2 esta llena
            estaLlena = setCarretasEnPila(pilaCarr1,carretaNueva);
        } 
    }
    printf("Se inserto la carreta con codigo: %i en la pila %i\n",carretaNueva->codigoCar,numPila);
}

/*Metodo se usa para crear todas las carretas solicitadas*/
void setNuevasCarretas(){        
    for(int i = 0 ; i < MCarretas2 ; i++){
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
    if (cantCajas > 1)
    {
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

/*Metodo que inserta a los nuevos clientes en la cola de pagos*/
void setNuevosClientesEnColaPagos(){
    for(int i = 0; i< cantClientesColaP; i++){
        struct Cliente *clienteNuevo;
        struct Carreta *carretaIns;
        clienteNuevo = (struct Cliente *)malloc(sizeof(struct Cliente));
        carretaIns = (struct Carreta *)malloc(sizeof(struct Carreta));
        carretaIns->codigoCar = codigosCarreta;
        clienteNuevo->codigoCli = codigoClientes;
        clienteNuevo->carretaU = carretaIns;
        setClientesColaPagos(clienteNuevo);
        codigosCarreta++;
        codigoClientes++;
    }
}

/*Metodo que inserta a los nuevos clientes en la lista de compras*/
void setNuevosClientesEnCompras(){
    for(int i = 0; i< cantClientesComp; i++){
        struct Cliente *clienteNuevo;
        struct Carreta *carretaIns;
        clienteNuevo = (struct Cliente *)malloc(sizeof(struct Cliente));
        carretaIns = (struct Carreta *)malloc(sizeof(struct Carreta));        
        carretaIns->codigoCar = codigosCarreta;
        clienteNuevo->codigoCli = codigoClientes;
        clienteNuevo->carretaU = carretaIns;
        setClientesCompras(clienteNuevo);
        codigosCarreta++;
        codigoClientes++;
    }
}

/*Metodo que permite la continuidad de la simulacion 
 *Asi como tambien el ingreso de nuevos clientes a esta
*/
void siguientePaso(){
    int opcion = 3;
    while(opcion != 0){                
        printf("\n");
        printf("Si desea terminar la simulacion ingrese [0]\n");
        printf("Si desea ingresar nuevos clientes ingrese [1]\n");
        printf("Si desea graficar el paso actual ingrese[2]\n");
        printf("Si desea continuar sin ingresar nada ingrese [3]\n");
        scanf("%d",&opcion);        
        if (opcion == 1)
        {
            int cantClientesNuevos;
            printf("Ingrese la cantidad de clientes inicial \n");
            scanf("%d", &cantClientesNuevos);
            setNuevosClientes(cantClientesNuevos);
            numPaso++;
            printPaso();
            validarAcciones();
        }else if(opcion == 0){
            printf("Se finalizara la simulacion \n");
        }else if(opcion == 2){
            graficar();   
        }else{
            numPaso++;
            printPaso();
            validarAcciones();
        }                
    }
}

/*Metodo que valida las acciones de la simulacion
 * Llama a los demas metodos para simular el traslado de clientes
 * a sus respectivas pilas y colas.
*/
void validarAcciones(){
    validarSalidaCajas();
    ingresarClientesACajas();
    ingresarClientesAColaPagos();
    ingresarClientesCompras();
}

/*Suma un turno a las cajas que tienen algun cliente atendiendo*/
void sumarACajasTurno(){
    struct Caja *cajaTemp = cajaInicial;
    while (cajaTemp != NULL)
    {
        if (cajaTemp->estado == 1)
        {
            cajaTemp->tiempoPas++;
        }        
        cajaTemp = cajaTemp->sigCaja;
    }
}

/*Metodo que valida que cliente ya paso su tiempo en su caja
 *si el cliente ya supero el tiempo lo elimina y devuelve la carreta
*/
void validarSalidaCajas(){
    sumarACajasTurno();
    struct Caja *cajaTemp = cajaInicial;
    while (cajaTemp != NULL)
    {
        if (cajaTemp->estado == 1)
        {
            if (cajaTemp->tiempo <= cajaTemp->tiempoPas)
            {
                struct Cliente *cliente = cajaTemp->clienteA;
                struct Carreta *carreta = cajaTemp->clienteA->carretaU;
                //TODO
                //Devolver carreta
                setCarretaEnPila(carreta);
                //Devolver Parametros inciales
                cajaTemp->carretaU = NULL;
                cajaTemp->clienteA = NULL;
                cajaTemp->estado = 0;
                cajaTemp->tiempoPas = 0;
                //Matar al cliente que tiene dentro     
                printf("El cliente con codigo %i salio de la caja %i y dejo la carreta %i \n",cliente->codigoCli,cajaTemp->codigoCaja,carreta->codigoCar); 
                cliente->carretaU = NULL;                                  
                free(cliente);
            }            
        }        
        cajaTemp = cajaTemp->sigCaja;
    }
}

/*Metoto que verifica que caja esta vacia
 *e ingresa al primer cliente en ella
*/
void ingresarClientesACajas(){
    struct Caja *cajaTemp = cajaInicial;
    while (cajaTemp != NULL)
    {
        if (colaPagosInicial->cliente == NULL)
        {
            break;
        }
        if (cajaTemp->estado == 0)
        {
            struct Cliente *clienteIns;
            struct ColaEspera *colaTemp;
            colaTemp = colaPagosInicial;
            clienteIns = colaTemp->cliente;
            cajaTemp->clienteA = clienteIns;
            cajaTemp->carretaU = clienteIns->carretaU;
            cajaTemp->estado = 1;
            colaPagosInicial = colaPagosInicial->sigCola;
            colaTemp->cliente == NULL;
            colaTemp->sigCola == NULL;
            if (colaTemp != colaPagosInicial)
            {
                free(colaTemp);
            }
            printf("El cliente con codigo %i ingreso a la caja %i \n",clienteIns->codigoCli,cajaTemp->codigoCaja);                   
        }
        cajaTemp = cajaTemp->sigCaja;
    }
}

/*Metodo que recibe un numero aleatorio de 0 a 100
 *luego verifica si hay algun cliente con ese indice 
 *si lo existe lo envia a la cola de pagos
*/
void ingresarClientesAColaPagos(){
    if (listaCompras->cliente != NULL)
    {
        
    
    
    struct ListaCompras *listTemp;
    listTemp = listaCompras;
    int indice = 0;
    int numA;
    numA = getNumAleatorio0a100();
    //numA = 0;
    //printf("Se saco el num: %i \n",numA);
    while(listTemp->sigLis != listaCompras){
        if (numA == indice)
        {           
            if(indice == 0){
                //TODO
                struct ListaCompras *listAnt;
                struct ListaCompras *listSig;
                struct ListaCompras *listTemp2;
                setClientesColaPagos(listaCompras->cliente);
                listTemp2 = listaCompras;
                listAnt = listaCompras->antLis;
                listSig = listaCompras->sigLis;
                listAnt->sigLis = listSig;
                listSig->antLis = listAnt;
                listaCompras = listSig;
                free(listTemp2);
                break;
            }else{
                printf("El cliente con codigo: %i saldra de compras\n",listTemp->cliente->codigoCli);
                setClientesColaPagos(listTemp->cliente);
                struct ListaCompras *listAnt;
                struct ListaCompras *listSig;
                listAnt = listTemp->antLis;
                listSig = listTemp->sigLis;
                listAnt->sigLis = listSig;
                listSig->antLis = listAnt;
                free(listTemp);
                break;
            }
            
        }
        listTemp = listTemp->sigLis;
        indice++;
    }
    }
}

/*Metodo que verifica si hay carretas para enviar
 *a el primer cliente en la cola de espera a la lista de compras
*/
void ingresarClientesCompras(){
    //Ver cuantos clientes hay
    struct ColaEspera *ct;
    ct = colaInicial;
    int cantCarr1 = contarCarretasEnPila(pilaCarr1);
    int cantCarr2 = contarCarretasEnPila(pilaCarr2);
    //printf("Cant carretas en pila 1: %i\n",cantCarr1);
    //printf("Cant carretas en pila 2: %i\n",cantCarr2);
    
    
    while(ct != NULL){
        ct = colaInicial;
        if(ct->sigCola == NULL){
            break;  
        }
        if(ct->cliente == NULL){
            break;
        }
        //printf("Cliente cod: %i esta en cola espera\n",ct->cliente->codigoCli);
        struct PilaCarr *pilat;
        if (cantCarr1 > 0 || cantCarr2 > 0)
        {
            int numA = getNumAleatorio1a2();
            //printf("Se saco el num: %i\n",numA);
            switch (numA)
            {
            case 1:
                if (cantCarr1 == 0)
                {
                    numA = 2;
                }else{
                    pilat = pilaCarr1;
                    for (int i = 0; i < cantCarr1-1; i++)
                    {
                        pilat = pilat->sigPila;
                    }                    
                    //printf("Se le dara al cliente la carreta con codigo: %i\n",pilat->carreta->codigoCar);      
                    sacarClienteColaInicial(pilat->carreta);    
                    pilat->carreta = NULL;          
                    cantCarr1--;
                    break;
                }
                
            case 2:
                if (cantCarr2 == 0)
                {
                    numA = 1;
                }else{
                    pilat = pilaCarr2;
                    for (int i = 0; i < cantCarr2-1; i++)
                    {
                        pilat = pilat->sigPila;
                    }
                    //printf("Se le dara al cliente la carreta con codigo: %i\n",pilat->carreta->codigoCar);
                    sacarClienteColaInicial(pilat->carreta);
                    pilat->carreta = NULL;
                    cantCarr2--;
                    break;
                }
            }
        }else{
            break;
        }
        //ct = ct->sigCola;        
    }
}

/*Metodo que saca al primer cliente en la cola incial de espera
 *le asigna una carreta y lo ingresa en la lista de compras
*/
void sacarClienteColaInicial(struct Carreta *carretaAsign){
    struct Cliente *client;
    struct ColaEspera *ct;
    ct = colaInicial;
    client = ct->cliente;
    client->carretaU = carretaAsign;    
    setClientesCompras(client);
    colaInicial = colaInicial->sigCola;
    free(ct);
    /*if(colaInicial->sigCola != NULL){
        
    }else{
        colaInicial->cliente = NULL;
    }*/
}



/*Metodo que cuenta la cantidad de carretas que tiene la pila*/
int contarCarretasEnPila(struct PilaCarr *pilaCarr){
    struct PilaCarr *pilT;
    pilT = pilaCarr;
    int cant = 0;
    for(int i = 0; i < cantCarretPila;i++){
        if (pilT->carreta == NULL)
        {
            break;
        }
        cant++;
        pilT = pilT->sigPila;
    }
        
    return cant;
}

/*Metodo que se llama al ingresar la opcion de graficar
 *Se encarga de llamar a los demas metodo para
 *crear y modificar un archivo .dot que se utilizara
 *para crear el grafico en .png
*/
void graficar(){
    FILE* fichero;
    fichero = fopen("grafico.dot", "wt");
    fputs("digraph G {\n", fichero);
    fputs("subgraph cluster_1 {\n", fichero); 
    fputs("label = \"Cola Inicial\" \n", fichero);    
    graficarColaInicial(fichero);
    fputs("}\n", fichero);    
    fputs("subgraph cluster_2 {\n", fichero); 
    fputs("label = \"Carretas\" \n", fichero); 
    graficarCarretas(pilaCarr1,fichero);
    graficarCarretas(pilaCarr2,fichero);
    fputs("}\n", fichero);    
    fputs("subgraph cluster_3 {\n", fichero); 
    fputs("label = \"Lista Compras\" \n", fichero); 
    graficarCompras(fichero);
    fputs("}\n", fichero);    
    fputs("subgraph cluster_4 {\n", fichero); 
    fputs("label = \"Cola Pagos\" \n", fichero);
    graficarColaPagos(fichero);
    fputs("}\n", fichero);    
    fputs("subgraph cluster_5 {\n", fichero); 
    fputs("label = \"Cajas\" \n", fichero);
    graficarCajas(fichero);
    fputs("}\n", fichero);    
    fputs("}", fichero);
    fclose(fichero);
    printf("Proceso completado\n");
    system("dot -Tpng grafico.dot -o grafico.png");
}

/*Metodo encargado de escribir en el documento .dot
 *para agregar el grafico de los clientes en la cola inicial
*/
void graficarColaInicial(FILE* fichero){

    int cantClientes = 0;
    struct ColaEspera *ct;
    ct = colaInicial;
    while(ct->sigCola != NULL){
        if (ct->sigCola == NULL)
        {
            break;
        }
        fputs("nodeCI",fichero);
        fprintf (fichero, "%d",cantClientes);
        fputs(" [shape=oval, label=\"Cliente: ",fichero);
        fprintf (fichero, "%d",ct->cliente->codigoCli);
        fputs("\"];\n",fichero); 
        cantClientes++;
        ct = ct->sigCola;
    } 
    for(int i = 0; i < (cantClientes-1);i++){
        fputs("nodeCI",fichero);
        fprintf (fichero, "%d",i);
        fputs(" -> ",fichero);
        fputs("nodeCI",fichero);
        fprintf (fichero, "%d",(i+1));
        fputs(";\n",fichero);
    }
}

/*Metodo encargado de escribir en el documento .dot
 *para agregar el grafico de una pila de carretas
*/
void graficarCarretas(struct PilaCarr *pilaUsar,FILE* fichero){
    struct PilaCarr *pilaTemp;
    pilaTemp = pilaUsar;
    if (pilaUsar == pilaCarr1)
    {
        fputs("nodeP1 [shape=record, label=\"{ ",fichero);
    }else{
        fputs("nodeP2 [shape=record, label=\"{ ",fichero);
    }
    
    for(int i = 0; i < cantCarretPila; i++){
        if (pilaTemp->carreta != NULL)
        {
            fputs("Carreta: ",fichero);
            fprintf (fichero, "%d",pilaTemp->carreta->codigoCar);
        }
        fputs("|",fichero);
        pilaTemp = pilaTemp->sigPila;
    }
    fputs("}\"];\n",fichero);
}

/*Metodo encargado de escribir en el documento .dot
 *para agregar el grafico de los clientes que estan
 *en la lista de compras
*/
void graficarCompras(FILE* fichero){
    if(listaCompras->cliente != NULL){

    
    int numberNode = 0;
    struct ListaCompras *listTemp;
    listTemp = listaCompras;
    while(listTemp->sigLis != listaCompras){
        fputs("nodeL",fichero);
        fprintf (fichero, "%d",numberNode);
        fputs(" [shape=box, label=\"{ ",fichero);
        fputs(" Cliente: ",fichero);
        fprintf (fichero, "%d",listTemp->cliente->codigoCli);
        fputs(" Carreta: ",fichero);
        fprintf (fichero, "%d",listTemp->cliente->carretaU->codigoCar);
        fputs("}\"];\n",fichero);
        numberNode++;
        listTemp = listTemp->sigLis;
    }
    int cantClientes = numberNode;
    numberNode = 0;    
    for(int i = 0; i < cantClientes;i++){
        fputs("nodeL",fichero);
        fprintf (fichero, "%d",i);
        fputs(" -> ",fichero);
        fputs("nodeL",fichero);
        if(i == (cantClientes-1)){
            fprintf (fichero, "%d",0);
        }else{
            fprintf (fichero, "%d",(i+1));
        }
        fputs(";\n",fichero);
    }

    for(int i = cantClientes-1; i >= 0;i--){
        fputs("nodeL",fichero);
        fprintf (fichero, "%d",i);
        fputs(" -> ",fichero);
        fputs("nodeL",fichero);
        if(i == (0)){
            fprintf (fichero, "%d",cantClientes-1);
        }else{
            fprintf (fichero, "%d",(i-1));
        }
        fputs(";\n",fichero);
    }
    }
}

/*Metodo encargado de escribir en el documento .dot
 *para agregar el grafico de los clientes que estan
 *en la cola de pagos
*/
void graficarColaPagos(FILE* fichero){
    int cantClientes = 0;
    struct ColaEspera *ct;
    ct = colaPagosInicial;
    while(ct->sigCola != NULL){
        if (ct->sigCola == NULL)
        {
            break;
        }
        fputs("nodeCP",fichero);
        fprintf (fichero, "%d",cantClientes);
        fputs(" [shape=oval, label=\"Cliente: ",fichero);
        fprintf (fichero, "%d",ct->cliente->codigoCli);
        fputs("\"];\n",fichero); 
        cantClientes++;
        ct = ct->sigCola;
    } 
    for(int i = 0; i < (cantClientes-1);i++){
        fputs("nodeCP",fichero);
        fprintf (fichero, "%d",i);
        fputs(" -> ",fichero);
        fputs("nodeCP",fichero);
        fprintf (fichero, "%d",(i+1));
        fputs(";\n",fichero);
    }
}

/*Metodo encargado de escribir en el documento .dot
 *para agregar el grafico de todas las cajas
*/
void graficarCajas(FILE* fichero){
    struct Caja *cajat;
    cajat = cajaInicial;
    for(int i = 0; i < cantCajas; i++){
        fputs("nodeCA",fichero);
        fprintf (fichero, "%d",i);
        fputs(" [shape=box, label=\"Caja: ",fichero);
        fprintf (fichero, "%d",cajat->codigoCaja);
        fputs(" Turnos: ",fichero);
        fprintf (fichero, "%d",cajat->tiempo);
        if (cajat->estado == 0)
        {
            fputs(" LIBRE",fichero);    
        }else{
            fputs(" OCUPADO",fichero);    
        }
        fputs("\"];\n",fichero);
        cajat = cajat->sigCaja;
    }
    for(int i = 0; i < (cantCajas-1); i++){
        fputs("nodeCA",fichero);
        fprintf (fichero, "%d",i);
        fputs(" -> ",fichero);
        fputs("nodeCA",fichero);
        fprintf (fichero, "%d",(i+1));
        fputs(";\n",fichero);
    }
    
    for(int i = (cantCajas-1); i > 0; i--){
        fputs("nodeCA",fichero);
        fprintf (fichero, "%d",i);
        fputs(" -> ",fichero);
        fputs("nodeCA",fichero);
        fprintf (fichero, "%d",(i-1));
        fputs(";\n",fichero);
    }
}