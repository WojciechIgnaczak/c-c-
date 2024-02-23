
#include <stdio.h> /* dyrektywa preprocesora =biblioteka */

int main() /* funckja glowna- domyslnie zwraca liczbe calkowita */
{
    printf("Hello World\n");/* kazda instrukcja konczy sie srednikiem, '\'-kontynuuje instrukcje w nastepnej linii*/
    int x=3;
    
    if (x>5)
    {
    printf("ja");    /* || or, && and, ! zaprzeczenie*/
    }else
        {
        printf("d");
        }
    for (int i=0;i<4;i++)
    {
        printf("zmienna= %i\n",i);/* wypisanie zmiennych */
    }
    
    return 0; /* zakonczenie funckji main */

}
