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
Le projet est accompagné d'un `MakeFile` donc une petit `make` dans le répertoire du projet permettra de lancer le projet  mais plusieurs maniérés d'utilisation sont possibles et ce sont bien détaillés ci dessous : 
 
## Mode D'emploi  :
 Apres le **`make`**  un exécutable appelé  **`tags`**   est généré qui permet donc le test du projet !
### Option 1 : **` ./tags -options[Value] --flags FILE_PATH `**
Dans cette méthode si vous lancez **`./tags`** en lui donnant des option en argument ( d'autres termes pareil qu'une commande du shell ) et donc les différentes options sont :

  |   Option     |Flags|Arguments| Description|
|-------------------|----------------|-----------------------------|-------|
| **`--add`**  | **`-a`** | `TAG :  nom du tag à ajouter`    | ajoute le tag **TAG** à le fichier qui se trouve en **FILE_PATH**|
| **`--delete`**  | **`-d`** | `TAG :  nom du tag à supprimer`    | supprime le tag **TAG** du fichier qui se trouve en **FILE_PATH**|
| **`--category`**  | **`-c`** | `CATEGORY:  nom de categorie à ajouter`    | ajoute la catégorie **CATEGORY** à le fichier qui se trouve en **FILE_PATH**|
| **`--delete_category`**  | **`-x`** | `CATEGORY:  nom de categorie à supprimer`    | supprime la catégorie **CATEGORY** du fichier qui se trouve en **FILE_PATH**|
| **`--search_files`**  | **`-s`** | `CRITERIA:  critere de recherche`    | recherche tous les fichiers qui satisfont le critere   **CRITERIA** à partir d'un chemin donné ou du **`./`** si celui là n'est pas spécifié|
| **`--search_tags`**  | **`-l`** | `FILE:  nom du fichier demandé `    | affiche la liste de tout les tags lié au fichie **FILE** à le fichier qui se trouve en **FILE_PATH**|

### Option 2 : **`./tags`**
Dans cette méthode si vous lancez **`./tags`** sans lui donner d'option ! 
un petit menu s'affichera vous indiquant tout les choix à votre disposition 