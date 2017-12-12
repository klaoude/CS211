#include "term.h"

int main(int argc, char** argv)
{
	system("clear");
	
	initialise_fat();

	printHello();

	while(!Run()) ;

	supprimer_tout();

	return 0;
}