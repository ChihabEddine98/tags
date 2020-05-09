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
