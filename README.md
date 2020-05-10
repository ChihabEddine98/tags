# Projet Système L3 "tags"

## Gestion de Tags sous unix 
Le projet de L3 programmation systèmes **Tags** réalisé en trinome : 


## Membres D'équipe :

  
  |   Nom & Prénoms |N_Etudiant| ID_Gitlab | Groupe |
|----------------|-------------------------------|-----------------------------|-------|
|Benamara Abdelkader Chihab | `-- 21808027 --` | `benamara` |    Maths-Info     |
|Aknoun Mehdi | `-- 21970844 --` | `aknoun` |      Info4  |
|Djelid Aymen | `-- 21810771 --` | `djelid` |  Info4 |

---
# Pour la première fois ! 
Le projet est accompagné d'un `MakeFile` donc un petit `make` dans le répertoire du projet permettra de lancer le projet  mais plusieurs maniérés d'utilisation sont possibles et ce sont bien détaillés ci dessous : 
 
## Mode D'emploi  :
 Apres le **`make`**  un exécutable appelé  **`tags`**   est généré qui permet donc le test du projet !
### Option 1 : **` ./tags -options[Value] --flags FILE_PATH `**
Dans cette méthode si vous lancez **`./tags`** en lui donnant des option en argument ( d'autres termes pareil qu'une commande du shell ) et donc les différentes options sont :

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
cette exécution nous retourne les fichiers dont ils satisfont le critère donné à partir du répertoire courant ! 



Pour pouvoir créer un nouveau tag il faut lui donner son tag parent **`CATEGORY`** donc deux alternatives sont à votre disposition : 
soit vous créez la `CATEGORY` avant de lui ajouter le `TAG` en question ou bien au moment de l'ajout d'un `TAG` répondre qu dialogue sur le terminal par le nom de la catégorie que vous voulez !

Afin de supprimer un tag il est possible soit de donner le nom du tag `./tags -d "TAG" FILE_PATH`
 ou aussi vous pouvez : `./tags -d "TAG" -c "CATEGORY" `

### Pas de panique  !
Si les options et choix de la commande **`./tags`** sont compliqués et dur à retenir il serait toujours possible de demander de l'aide à notre ami **`./tags --help `** 
 ou encore  **`./tags -? `** 
 et pour comment l'utiliser : **`./tags --usage`**

### Option 2 : **`./tags`**
Dans cette méthode si vous lancez **`./tags`** sans lui donner d'option ! 
un petit menu s'affichera vous indiquant tout les choix à votre disposition 

# Comment on a fait !
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

# Algos implementés :
**DETAILS BY MEHDI & ME & AYMEN**
```c
void init_tags(Tags  *tags, char  buf[MAXLEN]);
```
```c
void add(Tags  *tags, char  *tagName);
```
```c
void deletTag(Tags  *tags, char  *tagName);
```
```c
void set_tags(char  *Path, char  data[MAXLEN], char  *tagName, int rep);
```
```c
void get_tags(Tags  *tags, char  *Path, char  *tagName);
```
```c
void ListOfTags(Tags  *tableau, char  buff[MAXLEN], int  size);
```
```c
int findInList(Tags  *tags, char  *tagName);
```
```c
void addCategorie(char  *Path, char  *tagName);
```
```c
void addTagInCategorie(char  *Path, char  *category, char  *tagName);
```
```c
void supprimerCategorie(char  *Path, char  *category);
```
```c
void removeTagCategory(char  *Path, char  *category, char  *tagName);
```
```c
void afficher(Tags  *tags);
```
```c
void listTag(char  *Path);
```
```c
void removeTag(char  *Path, char  *tagName);
```
```c
int contientTag(char  *Path, char  *tag);
```
```c
Tags  *Allsoustags(char  *Path, Tags  *listcat);
```
```c
int testCriteria(char  *Path, search_criteria_t criteria);
```
```c
void listFilesRecursively(char  *basePath, search_criteria_t criteria);
```
```c
void low(char  str[40]);
```
```c
Tags  *lienEntreTags(char  *Path,char  *tag1,char  *tag2);
```
```c
void lienhierarchique(char  *Path,char  *tag1,char  *tag2);
```

