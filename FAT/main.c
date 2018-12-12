#include "term.h"

int main(int argc, char** argv)
{
	initialise_fat();

	printHello();

	while(!Run()) ;

	supprimer_tout();
}