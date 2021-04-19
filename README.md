# Projet Système L3 "tags"

## Gestion de Tags sous unix (ubuntu 18.4) 
Le projet de L3 programmation systèmes **Tags** réalisé en trinome : 


## Par :

  
  |   Nom & Prénoms |N_Etudiant| ID_Gitlab | Groupe |
|----------------|-------------------------------|-----------------------------|-------|
|Benamara Abdelkader Chihab | `-- 71808027 --` | `benamara` |    Maths-Info     |
|Aknoun Mehdi | `-- 71970844 --` | `aknoun` |      Info4  |
|Djelid Aymen | `-- 71810771 --` | `djelid` |  Info4 |

---
# Pour la première fois ! 
Le projet est accompagné d'un `MakeFile` donc un petit `make` dans le répertoire du projet permettra de compiler le projet.Plusieurs maniéres d'utilisation sont possibles et nous les avons bien détaillés ci dessous : 
 
## Mode D'emploi  :
 Apres le **`make`**  un exécutable appelé  **`tags`**   est généré qui permet donc le test du projet !
### Option 1 : **` ./tags -options[Value] --flags FILE_PATH `**
Dans cette méthode si vous lancez **`./tags`** en lui donnant des option en argument (pareil qu'une commande du shell). et voici donc les différentes options :

  |   Option     |Flags|Arguments| Description|
|-------------------|----------------|-----------------------------|-------|
| **`--add`**  | **`-a`** | `TAG` :  nom du tag à ajouter  | ajoute le tag **TAG** à le fichier qui se trouve en **FILE_PATH**|
| **`--delete`**  | **`-d`** | `TAG` :  nom du tag à supprimer    | supprime le tag **TAG** du fichier qui se trouve en **FILE_PATH**|
| **`--category`**  | **`-c`** | `CATEGORY`:  nom de categorie à ajouter    | ajoute la catégorie **CATEGORY** à le fichier qui se trouve en **FILE_PATH**|
| **`--delete_category`**  | **`-x`** | `CATEGORY`:  nom de categorie à supprimer   | supprime la catégorie **CATEGORY** du fichier qui se trouve en **FILE_PATH**|
| **`--search_files`**  | **`-s`** | `CRITERIA`:  critere de recherche    | recherche tous les fichiers qui satisfont le critere   **CRITERIA** à partir d'un chemin donné ou du **`./`** si celui là n'est pas spécifié|
| **`--search_tags`**  | **`-l`** | `FILE`:  nom du fichier demandé    | affiche la liste de tout les tags lié au fichie **FILE** à le fichier qui se trouve en **FILE_PATH**|

#### La différence entre option & flag dans notre cas :
##### Exemple 1 : 
**`./tags -a "Red" -c "Color" ./tests/1.txt`**
---
##### Exemple 2: 
**`./tags --add=Red --category=Color ./tests/1.txt`**
---
Ces deux exemples permettront d'ajouter le tag **Red** à la categorie **Color**  dans le fichier **./tests/1.txt**

Les deux exemples sont équivalents ! donc n'oubliez pas le petit **`=`** apres le flag ! 

##### Exemple de recherche :
**`./tags -s  "Color et non(Red) et Education et pas(L3)"`**
---
cette exécution nous retourne les fichiers du répertoire courant satisfaisant les critères demandés.



Pour pouvoir créer un nouveau tag, il faut lui donner son tag parent **`CATEGORY`** donc deux alternatives sont à votre disposition : 
soit vous créez la `CATEGORY` avant de lui ajouter le `TAG` en question, ou bien, au moment de l'ajout d'un `TAG` vous spécifierez la catégorie directement dans le terminal !

Afin de supprimer un tag il est possible soit de donner le nom du tag `./tags -d "TAG" FILE_PATH`

 ou aussi vous pouvez le faire cia la commande : `./tags -d "TAG" -c "CATEGORY" `

### Pas de panique  !
Si les options et choix de la commande **`./tags`** sont compliqués et dur à retenir il serait toujours possible de demander de l'aide à notre ami **`./tags --help `** 
 ou encore  **`./tags -? `** 
 et pour comment l'utiliser : **`./tags --usage`**

### Option 2 : **`./tags`**
Dans cette méthode si vous lancez **`./tags`** sans lui donner d'option ! 
un petit menu s'affichera vous indiquant tous les choix à votre disposition 


# Comment on a fait !
Nous avons choisit de sauvegarder les tags dans les fichiers à l'aide de XATTR (Extended Attributes).
### Structures utilsées :
Dans notre implémentation, on a choisi de stocker les tags dans des catégories, par défaut la catégorie d'un tag c'est le tag lui meme.
la liste des tags est une chaine de caractere contenant des mots séparés par des '#'.
Pour gérer les tags, on récupere d'abord la liste des tags du fichier dans une pile de Token appelé 'Tags' qui a la structure suivante : 

```c
struct Token
{
	char  tag[30];
	struct  elem  *suivant;
}
```
```c
struct Tags
{
	Token *sommet;
	int NbTags;
}
```
#### Gestion des tags :

##### Ajout :
Pour taguer un fichier, l'utilisateur doit donner le tag, la catégorie ainsi que le chemin du fichier qu'il veut taguer.
Pour cela, on a implémenté les fonctions suivantes  : 


```c
void init_tags(Tags  *tags, char  buf[MAXLEN]);
```
Cette fonction initliaise la structure Tags.
```c
void addCategorie(char  *Path, char  *tagName);
```
Cette fonction ajoute une catégorie au fichier.
```c
void addTagInCategorie(char  *Path, char  *category, char  *tagName);
```
Cette fonction ajoute un tag à une catégorie.

##### Suppression :
Pour supprimer des catégories ou des tags d'un fichier, on les récupere d'abord dans une pile, on la parcoure par la suite pour trouver le tag ou la catégorie recherchée.
Pour cela, on a implémenté les fonctions suivantes  : 

```c
void supprimerCategorie(char  *Path, char  *category);
```
- Supprime une catégorie donnée en parametre.
```c
void removeTagCategory(char  *Path, char  *category, char  *tagName);
```
- Supprime un tag d'une catégorie passée en argument d'un fichier.

```c
void removeTag(char  *Path, char  *tagName);
```
- Supprime un tag d'un fichier.

##### Affichage :
Pour l'affichage, on a implémenté les fonctions suivantes qui permettent d'affichier tous les tags d'un fichier, nous préciserons ulterierement, comment on procede 
pour afficher les tags selon des criteres.
- fonctions utilisées : 

```c
void afficher(Tags  *tags);
```
```c
void listTag(char  *Path);
```


---

##### Gestion de la recherche des fichiers selon des tags : 
**` search_creteria :`** cette structure comme définit ci dessous contient des listes de mots à rechercher **`in`** et d'autres à ne pas  **`not_in`**! 
```c
struct search_criteria
{
	char  **in; 
	char  **not_in;
	int in_size;
	int not_in_size;
}
```
**`arguments :`** cette structure sert à parser les commandes si on utlise **`option1`** de tags avec des options & des flags en paramètres !
```c
struct  arguments
{
	char  *args[1]; /* FILE PATH */
	char  *add_tag; /* --add Or  -a */
	char  *rm_tag;  /* --delete Or -d */
	char  *add_category; /* --category Or -c */
	char  *rm_category; /* --delete_category Or -x */
	char  *search_files_criteria; /* --search Or -s */
	char  *search_tags_criteria; /* --list Or  -l */
}
```
---
#### Algos utilisés pour la recherche selon les tags :
```c
search_criteria_t  tokenize(char  **result,  char  *working,  const  char  *src,  const  char  *delim)
```
Cette fonction prend en paramètre le critère de recherche que l'utilisateur a tapé comme par exemple : 
**`./tags -s "Color et non(Yellow) et Diderot et pas(M2)"`**
dans ce cas cette fonction prend le **`working="Color et non(Yellow) et Diderot et pas(M2)"`** et nous produit une structure  `search_criteria_t` remplie comme ci dessous :
```c
struct search_criteria
{	
	char **in=;  // ["Color","Diderot"]
	char **not_in; // ["Yellow","M2"]
	int in_size;   // 2
	int not_in_size;  // 2
}
```
Pour pouvoir distinguer les deux champs principaux de cette recherche ( négation ou pas )  la fonction suivante nous rend un grand service !
```c
char  *str_splitBetweenParentheses(char  *a_str,  const  char  a_delim)
```
Puisque cette fonction permet de prendre tout ce qui est entre les indicateurs de présence d'une négation et puis le mettre dans la champs dédié dans la structure 

Apres la partie de **parsing** il est temps de rechercher !
notre idée principale içi c'est de faire un parcours récursive dans les répertoires qu'on rencontre et pour chaque fichier on teste si'il est tagé et si c'est le cas voir tout ses sous tags à l'aide de la fonction :
```c
Tags *Allsoustags(char  *Path, Tags *listcat);
```
Et puis il suffit de tester si notre fichier satisfait la **`criteria`** demandée
```c
int  testCriteria(char  *Path, search_criteria_t criteria);
```
Et donc pour pouvoir tout tester il suffit de refaire ceci récursivement et on teste si ça vérifie la condition un petit `printf` fera l'affaire d'informer avec les fichiers visées par la **`criteria`**
```c
void  listFilesRecursively(char  *basePath, search_criteria_t criteria);
```
---
# compatibilité avec le SGF :
### La commande ```mv```:
Lorsqu'on déplace un fichier avec 'mv', le fichier garde ses tags

### La commande ```cp```:
Pour copier un fichier avec la commande 'cp', si on veut garder les memes tags, on doit rajouter le flag ```--preserve=xattr``` à notre commande.
##### exemple : 
``` cp --preserve=xattr file file_cp ```

### La commande ```rm```:
La commande 'rm' supprime le fichier, donc il n'apparaitra plus lors de la recherche.

### Gestion des liens physiques et symboliques :
##### liens physiques : 
Si on crée un lien physiques à partir d'un fichier contenant des tags, le lien contiendra, lui aussi, les memes tags.
Si un fichier contient plusieurs liens physiques, on a fait en sorte qu'il n'apparait qu'une fois lors de la recherche, et ce via une comparaison du numéro d'inoeud de chaque fichier.

#### liens symboliques : 
Pareil que les liens physques. Si on veut taguer un lien symbolique sans pour autant taguer le fichier sur lequel il pointe, on doit remplacer la fonction ```setxattr``` dans notre code par ```lsetxattr```

### Liens hierarchique entre 2 tags : 
Pour spécifier le lien hierarchique entre deux tags, il suffit de choisir l'option 6 du menu, et de donner le nom des tags.
Pour ca on fait appel aux 2 fonctions suivantes : 

```c
void lienhierarchique(char *Path, char *tag1, char *tag2)

```
```c
Tags *lienEntreTags(char *Path, char *tag1, char *tag2)
```
