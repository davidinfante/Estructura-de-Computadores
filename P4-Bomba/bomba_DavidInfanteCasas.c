// gcc -Og -no-pie bomba_DavidInfanteCasas.c -o bomba_DavidInfanteCasas

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 60

char password[]="egallas\n";	// contraseña
int  passcode  = 1024;		// pin

void boom(void){
	printf(	"\n"
		"***************\n"
		"*** BOOM!!! ***\n"
		"***************\n"
		"\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
		"Â·Â·Â·Â·Â·Â bomba desactivada Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
		"Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
		"\n");
	exit(0);
}

void yoNoModificoPwd(char* pwd) {
	pwd[0] = 'e';
}

int yoNoModificoPin(int pin) {
	return pin+24;
}

int main(){
	char pw[SIZE];
	int  pc, n;

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	do	printf("\nIntroduce la contraseÃ±a: ");
	while (	fgets(pw, SIZE, stdin) == NULL );	// fgets lee una cadena que introduzca el usuario pw puntero, SIZE tamaño, stdin fichero -> teclado (solo falla si hacemos ctrl+D)
	//devuelve > 0 si la primera cadena esta despues en el diccionario que la segunda -> != no coinciden las contraseñas

	// Modificamos la password
	yoNoModificoPwd(pw);

	// sizeof es para que cuente los valores de toda la cadena incluyendo \0
	if    (	strncmp(pw,password,sizeof(password)) )
	    boom();

	// Comprobar que no hemos tardado demasiado en meter la pass (TLIM = 60 segundos)
	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();

	// Lee con scanf (array.toInteger()) un pin introducido
	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;         }
	while (	n!=1 );

	// Modificamos el pin
	pc = yoNoModificoPin(pc);

	// Comprueba que coincide el pin
	if    (	pc != passcode )
	    boom();
	
	// Comprueba que no ha pasado demasiado tiempo
	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();

	defused();
}

