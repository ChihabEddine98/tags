#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <fcntl.h>
#include <string.h>
#include <asm/errno.h>
#include "biblio.h"

void mypause ( void )
{
    printf ( "Press [Enter] to continue . . ." );
    fflush ( stdout );
    getchar();
}
int main()
{
  //  const char *fichier = "../teest";
   // addCategorie("../teest","all");
 //  addTagInCategorie("../teest","all","color1");
//removeTag(fichier,"adem");
 //  removeTagCategory("../teest","adem","lina");
   // supprimerCategorie(fichier,"adem");
  // if (contientTag(fichier,"aymen")==1) printf("\n rana hna hbb");
   //listTag(fichier);
   //lienEntreTags(fichier,"all","blue");
  // lienhierarchique(fichier,"color1","blue");
   //char mot[]="Aymen";
    //low(mot);

    char fichier[85];
    char catName[45];
    char tagNAme[45];
    char tagNAme2[45];
    color3();
    printf("\n\n\t\tSysteme project - Best place to learn\n\n\n");
    int choice, num, i;
    char ch;
    char ch1[3];
    while(1)
    {
        color1();
        printf("\n1. ajouter catégorie  \n");
        printf("2. ajouter tag dans catégorie\n");
        printf("3. supprimer categorie\n");
        printf("4. supprimer tag dans catégorie \n");
        printf("5. supprimer tag\n");
        printf("6. lien hiérarchique entre deux tag\n");
        printf("7. Afficher les Tags\n");
        printf("8. Exit \n\n\n");
        yellow();
        printf("Enter your choice :  ");
        scanf("%s",ch1);
        choice=atoi(ch1);
        switch(choice)
        {
            case 1:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie:\n");
                scanf("%s", catName);
               // printf("%s",fichier);
                addCategorie(fichier,catName);
                printf("\n");
                getchar();

                break;

            case 2:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie:\n");
                scanf("%s", catName);
                printf("nom de tag :\n");
                scanf("%s", tagNAme);
                addTagInCategorie(fichier,catName,tagNAme);

                break;
            case 3:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie :\n");
                scanf("%s", catName);
                supprimerCategorie(fichier,catName);

                break;
            case 4:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie :\n");
                scanf("%s", catName);
                printf("nom de tag :\n");
                scanf("%s", tagNAme);
                removeTagCategory(fichier,catName,tagNAme);

                break;
            case 5:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de tag :\n");
                scanf("%s", tagNAme);
                removeTag(fichier,tagNAme);

                break;
            case 6:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de tag 1:\n");
                scanf("%s", tagNAme);
                printf("nom de tag 2:\n");
                scanf("%s", tagNAme2);
                lienhierarchique(fichier,tagNAme,tagNAme2);

                break;
            case 7:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("\n\n");
                listTag(fichier);
                printf("\n\n");

                break;

            case 8:
                blue();
                printf("\n\n\t\t\tCoding is Fun !\n\n\n");
                exit(0);    // terminates the complete program execution
            default:
                red();
                printf("default\n\n");
        }
    }
    printf("\n\n\t\t\tCoding is Fun !\n\n\n");
    reset();
    return 0;

}