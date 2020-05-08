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

    printf("\n\n\t\tSysteme project - Best place to learn\n\n\n");
    int choice, num, i;
    char ch;
    while(1)
    {
        printf("\n1. ajouter catégorie  \n");
        printf("2. ajouter tag dans catégorie\n");
        printf("3. supprimer categorie\n");
        printf("4. supprimer tag dans catégorie \n");
        printf("5. supprimer tag\n");
        printf("6. lien hiérarchique entre deux tag\n");
        printf("7. Afficher les Tags\n");
        printf("8. Exit \n\n\n");

        printf("Enter your choice :  ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie:\n");
                scanf("%s", catName);
                printf("%s",fichier);
                addCategorie(fichier,catName);

                break;

            case 2:
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie:\n");
                scanf("%s", catName);
                printf("nom de tag :\n");
                scanf("%s", tagNAme);
                addTagInCategorie(fichier,catName,tagNAme);

                break;
            case 3:
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie :\n");
                scanf("%s", catName);
                supprimerCategorie(fichier,catName);

                break;
            case 4:
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie :\n");
                scanf("%s", catName);
                printf("nom de tag :\n");
                scanf("%s", tagNAme);
                removeTagCategory(fichier,catName,tagNAme);

                break;
            case 5:
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de tag :\n");
                scanf("%s", tagNAme);
                removeTag(fichier,tagNAme);

                break;
            case 6:
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de tag 1:\n");
                scanf("%s", tagNAme);
                printf("nom de tag 2:\n");
                scanf("%s", tagNAme2);
                lienhierarchique(fichier,tagNAme,tagNAme2);

                break;
            case 7:
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("\n\n");
                listTag(fichier);
                printf("\n\n");

                break;

            case 8:
                printf("\n\n\t\t\tCoding is Fun !\n\n\n");
                exit(0);    // terminates the complete program execution
            default:
                printf("default\n\n");
        }
    }
    printf("\n\n\t\t\tCoding is Fun !\n\n\n");
    return 0;

}