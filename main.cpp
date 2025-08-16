#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>  // Requiere la librería dos.h
#include <conio.h>//Esta libreria se utiliza para el getch()

#define AlturaMAX 20//Altura maxima del tablero
#define AnchoMAX 78//Anchura maxima del tablero

//Funcion que se encarga de filtrar si el numero que introdujo el usuario es correcto
void Filtro(int max, int min, int *num, int *cent){
    *cent=0;//se inicia con 0
    scanf("%d",&*num);//pide dato
    getchar();
    //El *num que mete el usuario no puede ser menor o igual a min
    //La variable *num puede ser mayor que el valor de max
    if(*num>max || *num<=min){//si el usuario mete un numero incorrecto
        *cent=1;//el valor cambia a 1
        printf("Error tamanyo incorrecto\n");//imprime mensaje de error
    }
    return;
}

//Funcion que repitira si el numero es incorrecto, y pedira los tres datos del usuario
void PedirAlturaAnchuraNivel(int *Alt, int *Ach, int *Niv){
    int cent=0;//centinela que se encarga de los bucles do-whiles
    //bucles que se repitiran en caso de que el usuario meta el dato de forma incorrecta

    do{//Pide Altura
        cent=0;//si el dato es correcto el bucle no se repitira
        printf("Introduzca alto del tablero (1-20):");
        Filtro(AlturaMAX,0,Alt,&cent);
    }while(cent==1);

    do{//Pide Anchura
        cent=0;
        printf("Introduzca ancho del tablero (1-78):");
        Filtro(AnchoMAX,0,Ach,&cent);
    }while(cent==1);

    do{//Pide Nivel de dificultad
        cent=0;
        printf("Introduzca nivel de dificultad  (1-10):");
        Filtro(10,0,Niv,&cent);
    }while(cent==1);
    return;
}

//Funcion que se encargara de calcular cuantos zombis, tps y minas se necesita. Tambien calculara el nivel
void Calculo(int Al, int An, int *Nv, int *z, int *tp, int *mina){
    int a;
    a=Al*An;//Total de las casillas del tablero
    *z=a*0.05;//calcula el 5% de zombies en funcion del total de casillas
    *tp=a*0.01;//calcula el 1% de teletransportadores en funcion del total de casillas
    *mina=a*0.1;//calcula el 10% de minas en funcion del total de casillas
    *Nv=(*Nv)*10;//El nivel determina con que probabilidad se mueve el zombie
    return;
}

//Funcion que se activa cuando el personaje entra en un teletransportador
void tpActivado(int Al, int An, int T[AlturaMAX][AnchoMAX]){
    int a=0,b=0,i=1;

    while(i==1){//se repite tantas veces como haga falta hasta que pueda ser teletransportado
        a=rand()%Al;//escoge una posicion random de la altura
        b=rand()%An;//escoge una posicion random de la anchura

        if(T[a][b]==0){//Si el sitio que escogio el tp esta vacio
            T[a][b]=4;//Se mueve al personaje
            i=0;//Y rompe el bucle
        }
    }
    return;
}

void MovCasos(int Al, int An, int T[AlturaMAX][AnchoMAX],int *n, int a,int b,int c,int d, int i, int j, int *cent){

    //se encargara de moverse por las columnas("j", izq. o derch.)
    //se encargara de moverse por las filas("i", arriba o abajo)
    if(T[i][j]==4){
        if(c!=d){//b determinara el limite de lo que puede avanzar el personaje por las filas
            //el movimiento lo determina la variable 'a' que sumara o restara en 1 a 'i'
            if(T[a][b]==3){//Si el usuario se mueve a una posicion con un zombie muere
                T[a][b]=5;//Mata al personaje
                T[i][j]=0;//Vacia la posicion
                *n=0;//Cambia valor para romper bucle de otra funcion y mostrar el fin del juego
                *cent=1;//Cambia de valor de cent, solo se requiere en el caso de que el usuario baje
                //ya que sirve como tope para parar el for
            }if(T[a][b]==2){//Si el usuario se mueve a una posicion con una mina muere
                T[a][b]=5;//Mata al personaje
                T[i][j]=0;//Vacia la posicion
                *n=2;
                *cent=1;
            }if(T[a][b]==1){//Si el usuario se mueve a una posicion con un tp se activa y lo mueve
                tpActivado(Al,An,T);//llama funcion
                T[i][j]=0;//Vacia la posicion
                *cent=1;
            }if(T[a][b]==0){//si el usuario se mueve a una posicion vacia
                T[a][b]=4;//mueve al usuario
                T[i][j]=0;//Vacia la posicion
                *cent=1;
            }
        }
    }
    return;
}


//Funcion principal de movimiento del Personaje
void MovPersonaje(int Al, int An, int T[AlturaMAX][AnchoMAX],int *n){
    char tecla = getch();//recoge la tecla que el usuario eligio para moverse
    int cent=0;//centinela para parar el bucle del for
    if(tecla==-32 || tecla==0){
        tecla=getch();
    }
    switch(tecla){
    //Casos para moverse, hay 4(Arriba,Abajo,Derch,Izq)

    //Arriba
    case 72:
    case '8':
    case 'w':
    case 'W':
        for(int i=0;i<Al && cent==0;i++){
            for(int j=0;j<An && cent==0;j++){//llama la funcion de movimiento longitudinal
                MovCasos(Al,An,T,n,i-1,j,i,0,i,j,&cent);
                //Se determina la a(i-1) que es el movimiento deseado
                //Y b(0) que es el limite al cual puede avanzar el usuario
            }
        }
        break;

        //Abajo
    case 80:
    case '2':
    case 's':
    case 'S':
        for(int i=0;i<Al && cent==0;i++){//el centinela 'cent' sirve para parar el bucle
            //ya que si se sigue sumando 1 a la i el personaje se movera constantemente hasta llegar al final
            for(int j=0;j<An && cent==0;j++){
                MovCasos(Al,An,T,n,i+1,j,i,Al-1,i,j,&cent);
                //Se determina la a(i+1) que es el movimiento deseado
                //Y b(Al-1) que es el limite al cual puede avanzar el usuario
            }
        }
        break;

        //Izquierda
    case 75:
    case '4':
    case 'a':
    case 'A':
        for(int i=0;i<Al && cent==0;i++){
            for(int j=0;j<An && cent==0;j++){//llama la funcion de movimiento lateral
                MovCasos(Al,An,T,n,i,j-1,j,0,i,j,&cent);
                //Se determina la a(j-1) que es el movimiento deseado
                //Y b(0) que es el limite al cual puede avanzar el usuario
            }
        }
        break;

        //Derecha
    case 77:
    case '6':
    case 'd':
    case 'D':
        for(int i=0;i<Al && cent==0;i++){
            for(int j=0;j<An && cent==0;j++){//'cent'para el bucle
                //ya que si se sigue sumando 1 a la j el personaje se movera constantemente hasta llegar al final
                MovCasos(Al,An,T,n,i,j+1,j,An-1,i,j,&cent);
                //Se determina la a(j+1) que es el movimiento deseado
                //Y b(An-1) que es el limite al cual puede avanzar el usuario
            }
        }
        break;
    }
    return;
}

//Funcion que Comprueba si un zombie se come al personaje
void ComprobacionMuerte(int *n, int T[AlturaMAX][AnchoMAX],int posi, int posj){

    if(T[posi][posj]==-3 ||T[posi][posj]==3 ){//Si la posicion del jugador coincide con el valor del zombie(3)
        *n=0;//Se cambia el valor de n para acabar el juego
        T[posi][posj]=5;//Y se muestra la muerte por pantalla
    }
    return;
}

void ZombiMovCasos(int i, int j, int a, int b, int T[AlturaMAX][AnchoMAX], int *z){
    //a y b se encargaran de determinar en que direccion se movera el zombie
    if(T[a][b]==2){//si en el movimiento diagonal pisa una mina el xombie muere
        T[i][j]=0;//Vacia la casilla del zombie
        T[a][b]=0;//Vacia a la mina
        *z=(*z)-1;//resta una z ya que muere
    }else if(T[a][b]==-3 || T[a][b]==3){//si en el movimiento diagonal colapsa con otro xombie, se lo come
        T[i][j]=0;//Vacia la casilla
        T[a][b]=-3;//mueve al restante
        *z=(*z)-1;//resta una z ya que muere
    }else{//si en el movimiento diagonal no se cumplen las anteriores condiciones el zombie se mueve
        T[i][j]=0;
        T[a][b]=-3;
        //Al igual que en los movimientos longitudinales y laterales para pasar al siguiente zombi
        //y no seguir siempre en el mismo se incremneta en 1 i o j, dependera de a y b

    }
    return;
}

//Funcion Principal de movimiento de los zombies del juego
void Zombis(int Nv, int T[AlturaMAX][AnchoMAX], int *n, int an, int al, int *z){
    int random=0, posi=0, posj=0;

    for(int i=0;i<al;i++){
        for(int j=0;j<an;j++){
            if(T[i][j]==4){
                posi=i;//Posicion del personaje en i(Filas)
                posj=j;//Posicion del personaje en j(Columnas)
            }
        }
    }

    for(int i=0;i<al;i++){
        for(int j=0;j<an;j++){
            if(T[i][j]==3){
                random = rand()% 100;
                //se le da un valor al azar a la varible 'a'
                if(random<=Nv){//si el valor de a es menor o igual al Nivel el zombi se mueve
                    if(i==posi){//determina si el xombie se encuentra en la misma fila que el Personaje
                        if(j>posj){//si el jugador se encuentra a la derecha del zombie
                            //llama al movimiento lateral
                            ZombiMovCasos(i,j,i,j-1,T,z);
                        }else if(j<posj){//si el jugador se encuentra a la izquierda del zombie
                            ZombiMovCasos(i,j,i,j+1,T,z);
                        }
                    }else if(j==posj){//determina si el xombie se encuentra en la misma columna que el Personaje
                        if(i>posi){//si el jugador se encuentra por encima del zombie
                            ZombiMovCasos(i,j,i-1,j,T,z);
                        }else if(i<posi){//si el jugador se encuentra por debajo del zombie
                            ZombiMovCasos(i,j,i+1,j,T,z);
                        }
                    }else if(posi!=i && posj!=j){//si no se encuentra ni en la misma fila y columna
                        //el movimiento mas optimo para llegar al jugador es de forma diagonal
                        if(posi>i){//determinamos si  el personaje esta en una fila inferior
                            if(posj>j){//si el personaje se encuentra mas a la derecha
                                ZombiMovCasos(i,j,i+1,j+1,T,z);
                            }else if(posj<j){//si el personaje se encuentra mas a la izquierda
                                ZombiMovCasos(i,j,i+1,j-1,T,z);
                            }
                        }if(posi<i){//determinamos si el personaje esta en una fila superior
                            if(posj>j){//si el personaje se encuentra mas a la derecha
                                ZombiMovCasos(i,j,i-1,j+1,T,z);

                            }else if(posj<j){//si el personaje se encuentra mas a la izquierda
                                ZombiMovCasos(i,j,i-1,j-1,T,z);

                            }
                        }
                    }
                    ComprobacionMuerte(n,T,posi,posj);//comprueba si el zombie llego al jugador
                }

            }
        }
    }
    //Para que en el doble bucle anterior los zombies no repitan el movimiento se les da el valor de -3, asi no los vuelve a seleccionar
    //Una vez acabado sus movimientos respectivos este doble bucle les devuelve el valor 3 para que se muestren por pantalla
    for(int i=0;i<al;i++){
        for(int j=0;j<an;j++){
            if(T[i][j]==-3){//si ha habido un zombie que se ha movido su valor sera -3
                T[i][j]=3;//se cambia el valor a 3 para que se muestre por pantalla
            }
        }
    }
    return;
}

//Funcion que inicializa la matriz
void Inicializar (int Al, int An, int T[AlturaMAX][AnchoMAX]){
    //se recorre toda la Matriz dandole el valor 0 para crear las casillas vacias
    for(int i=0; i<Al;i++){
        for(int j=0; j<An;j++){
            T[i][j]=0;
        }
    }
    return;
}

//Funcion con bucle que crea posiciones de los objetos y entidades del juego
void CreacionObj(int cont,int tipo, int T[AlturaMAX][AnchoMAX], int Al, int An){
    //un bucle que se repetira tantas como nos diga la variable de 'cont'
    while(cont!=0){
        int i=rand()%Al;//se escoge una fila al azar
        int j=rand()%An;//se escoge una columna al azar

        if(T[i][j]==0){//si la casilla escogida esta vacia
            T[i][j]=tipo;//tipo tendra valor que determinara si es mina,tp o zombie
            cont=(cont)-1;//al estar la casilla vacia el contador se resta para parar el bucle
        }
    }
    return;
}

//Funcion que se encarga de crear y posicinar todo lo necesario en el tablero
void CreacionTablero(int z, int tp, int mina,int Al,int An, int T[AlturaMAX][AnchoMAX]){
    int a=0,b=0;
    //Creacion ficha de salida del jugador
    a=rand()%Al;//posicion al azar de fila
    b=rand()%An;//posicion al azar de columna
    T[a][b]=4;//se crea al personaje

    //Creacion del resto de elementos
    CreacionObj(z,3,T, Al, An);
    CreacionObj(mina,2,T, Al, An);
    CreacionObj(tp,1,T, Al, An);
    return;
}

//Funcion que se encarga de mostrar por pantalla el tablero con todos sus datos
void Imprimir(int Al, int An, int T[AlturaMAX][AnchoMAX]){
    system("cls");
    printf("SUPERVIVENCIA ZOMBI\n");

    //La alambrada de x que rodeara a la matriz
    for(int x=0; x<An+2;x++){
        printf("x");
    }
    printf("\n");
    //los siguientes for se encargan de recorrer la matriz
    for(int i=0;i<Al;i++){
        printf("x");//al inicio de cada fila se imprime una x
        for(int j=0;j<An;j++){
            int a=T[i][j];
            //el switch dependiendo del valor de cada casilla
            //se encargara de mostrar por pantalla cada elemento del tablero
            switch (a){
            case 0:
                printf(" ");//vaxio
                break;
            case 1:
                printf("@");//tp
                break;
            case 2:
                printf("*");//mina
                break;
            case 3:
                printf("Z");//xombi
                break;
            case 4:
                printf("S");//tu
                break;
            case 5:
                printf("M");//Sitio de fallecimiento del superviviente
                break;
            }
        }
        printf("x\n");//cuando se acaba una fila se cubre con una x y un salto de linea
    }
    //al acabar de imprimir la matriz se cierra con la alambrada
    for(int x=0; x<An+2;x++){
        printf("x");
    }
    return;
}

//Funcion que una vez acaba el juego decide que final mostrar
void PantallaFinal(int n, int z, int Al, int An, int T[AlturaMAX][AnchoMAX]){
    system("cls");
    Imprimir(Al,An,T);//Imprime por ultima vez la pantalla
    //Y dependiendo de los datos determina que final ha tenido el usuario

    if(z==0 && n==0){//si el contador de zombies llego a 0 y el bucle se rompio, significa victoria
        printf("\nFelicidades, has ganado! Has conseguido sobrevivir a los zombis\n");
    }if(n==0 && z!=0){//si el contador de zombies no llego a 0 pero n si es 0, significa que un zombi se comio al jugador
        printf("\nHas perdido! Los zombis te han comido vivo\n");
    }if(n==2){//si el jugador piso una mina el valor de n sera 2 por tanto saldra este mensaje
        printf("\nHas perdido! Una mina te ha estallado\n");
    }
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < 5) {
        // Este bucle simplemente espera hasta que pasen 5 segundos
    }
    return;
}

//Funcion que se encarga de iniciar el juego y reunir al resto de funciones
void Game(){

    int n=1;//centinela
    int Al=0,An=0,Nv=0;//Pregunta a usuario
    int z=0,tp=0,mina=0;//Numero de zombis,tps y minas
    int Tablero[AlturaMAX][AnchoMAX];//matriz del tablero
    srand(time(NULL));

    PedirAlturaAnchuraNivel(&Al,&An,&Nv);//Se piden datos al usuario llamando a la funcion
    Calculo(Al,An,&Nv,&z,&tp,&mina);//se calcula el numero de elemnetos
    Inicializar(Al,An,Tablero);//se inicializa la matriz
    CreacionTablero(z,tp,mina,Al,An,Tablero);//se juntan todos los elementos
    //Este bucle se repetira constantemente hasta que el usuario pierda o gane
    do{
        Imprimir(Al,An,Tablero);//se muestra el tablero
        printf("\nUtilice los cursores para moverse\n");
        if(n==1){
            MovPersonaje(Al,An,Tablero,&n);//el usuario mueve al personaje
            Zombis(Nv,Tablero,&n,An,Al,&z);//turno de los xombies para moverse
            if(z==0){//si el contador de zombies llego a 0
                n=0;//Se rompe el bucle
            }
            //Al tratarse de un do-while se repitira por una ultima vez
            //Entrando al siguiente if
        }if(n!=1){
            PantallaFinal(n,z,Al,An,Tablero);//mostrando al acabar la pantalla final
        }
    }while(n==1);
    return;
}

//Funcion Principal
int main(){
    Game();//se llama a la funcion del juego
    return 0;
}

