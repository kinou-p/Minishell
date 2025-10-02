# Minishell - École 42

## Description
Minishell est un projet de l'École 42 qui consiste à créer un shell Unix minimaliste mais fonctionnel, similaire à bash. Ce projet permet de comprendre en profondeur le fonctionnement des shells, la gestion des processus, et l'exécution de commandes sous Unix.

## Objectifs pédagogiques
- Maîtriser la **programmation système** Unix/Linux
- Comprendre l'**exécution de processus** (fork, exec, wait)
- Gérer les **pipes et redirections** d'I/O
- Implémenter un **parser** pour analyser les commandes
- Traiter les **signaux système** (SIGINT, SIGQUIT)
- Gérer les **variables d'environnement**

## Fonctionnalités implémentées

### Built-ins
- `echo` avec option `-n`
- `cd` avec chemins relatifs et absolus
- `pwd` - affichage du répertoire courant
- `export` - définition de variables d'environnement
- `unset` - suppression de variables
- `env` - affichage de l'environnement
- `exit` - fermeture du shell avec code de retour

### Fonctionnalités shell
- **Exécution de programmes** via PATH ou chemin absolu
- **Pipes** (`|`) pour chaîner les commandes
- **Redirections** :
  - `<` redirection d'entrée
  - `>` redirection de sortie
  - `>>` redirection de sortie en mode append
  - `<<` here document avec délimiteur
- **Variables d'environnement** (`$VAR`, `$?`, `$$`)
- **Gestion des quotes** simples et doubles
- **Historique** des commandes
- **Autocomplétion** basique

### Gestion des signaux
- `Ctrl+C` (SIGINT) - interruption
- `Ctrl+D` (EOF) - fermeture propre
- `Ctrl+\` (SIGQUIT) - ignoré en mode interactif

## Technologies utilisées
- **Langage** : C (norme 42)
- **Bibliothèques** : readline, termcap
- **Appels système** : fork, execve, wait, pipe, dup2
- **Gestion mémoire** : malloc, free (pas de leaks)

## Architecture du projet

### Structure des fichiers
```
Minishell/
├── Makefile              # Compilation
├── includes/             # Headers (.h)
│   ├── minishell.h      # Header principal
│   └── libft.h          # Bibliothèque libft
├── srcs/                # Code source
│   ├── main.c           # Point d'entrée
│   ├── parsing/         # Analyseur lexical/syntaxique
│   │   ├── lexer.c
│   │   ├── parser.c
│   │   └── expander.c
│   ├── execution/       # Exécution des commandes
│   │   ├── executor.c
│   │   ├── pipes.c
│   │   └── redirections.c
│   ├── builtins/        # Commandes intégrées
│   │   ├── echo.c
│   │   ├── cd.c
│   │   ├── pwd.c
│   │   ├── export.c
│   │   ├── unset.c
│   │   ├── env.c
│   │   └── exit.c
│   ├── signals/         # Gestion des signaux
│   │   └── signals.c
│   └── utils/           # Fonctions utilitaires
│       ├── env_utils.c
│       ├── error.c
│       └── cleanup.c
└── libft/               # Bibliothèque personnelle
```

### Flux d'exécution
1. **Lecture** de la ligne de commande (readline)
2. **Tokenisation** et analyse lexicale
3. **Parsing** et construction de l'AST
4. **Expansion** des variables et wildcards
5. **Exécution** avec gestion des processus
6. **Nettoyage** mémoire et gestion d'erreurs

## Installation et compilation

### Prérequis
- **GCC** compiler
- **Make**
- **Bibliothèque readline** (`sudo apt-get install libreadline-dev`)

### Compilation
```bash
git clone <repository-url>
cd Minishell
make
```

### Nettoyage
```bash
make clean     # Supprime les fichiers .o
make fclean    # Supprime tout + l'exécutable
make re        # Recompile entièrement
```

## Utilisation

### Lancement
```bash
./minishell
```

### Exemples de commandes
```bash
# Commandes simples
$ ls -la
$ pwd
$ echo "Hello World"

# Pipes
$ cat file.txt | grep "pattern" | wc -l
$ ls | head -5

# Redirections
$ echo "test" > output.txt
$ cat < input.txt
$ ls >> log.txt

# Here document
$ cat << EOF
> line 1
> line 2
> EOF

# Variables d'environnement
$ export MY_VAR="value"
$ echo $MY_VAR
$ echo $?    # Code de retour dernière commande
$ echo $$    # PID du shell

# Built-ins
$ cd /home/user
$ pwd
$ env | grep PATH
$ unset MY_VAR
$ exit 0
```

### Gestion des quotes
```bash
$ echo "Hello $USER"        # Expansion dans les doubles quotes
$ echo 'Hello $USER'        # Pas d'expansion dans les simples quotes
$ echo "He said 'hello'"    # Imbrication de quotes
```

## Gestion d'erreurs

### Types d'erreurs gérées
- **Commandes introuvables** (command not found)
- **Permissions insuffisantes** (permission denied)
- **Fichiers inexistants** (no such file or directory)
- **Erreurs de syntaxe** (syntax error)
- **Erreurs de pipe** (broken pipe)
- **Allocation mémoire** (malloc failure)

### Codes de retour
- `0` - Succès
- `1` - Erreur générale
- `2` - Erreur de syntaxe
- `126` - Permission refusée
- `127` - Commande introuvable
- `130` - Interruption par signal

## Parsing et analyse

### Étapes du parsing
1. **Tokenisation** : Division en tokens (mots, opérateurs)
2. **Classification** : Identification du type de chaque token
3. **Validation syntaxique** : Vérification de la grammaire
4. **Construction AST** : Arbre syntaxique abstrait
5. **Expansion** : Variables, quotes, wildcards

### Grammaire simplifiée
```
command_line : pipeline
pipeline     : command ('|' command)*
command      : simple_command redirection*
simple_command : word word*
redirection  : '<' word | '>' word | '>>' word | '<<' word
```

## Gestion mémoire

### Stratégies appliquées
- **Allocation tracking** : Suivi de toutes les allocations
- **Cleanup systématique** : Libération en cas d'erreur
- **Valgrind clean** : Aucun leak détecté
- **Error handling** : Gestion robuste des échecs malloc

## Tests et validation

### Tests automatisés
```bash
# Tests de base
make test

# Tests avec valgrind
make test_memory

# Tests de régression
make test_all
```

### Cas de test couverts
- Commandes simples et complexes
- Pipes multiples
- Redirections combinées
- Gestion d'erreurs
- Variables d'environnement
- Signaux et interruptions

## Optimisations

### Performance
- **Parser optimisé** pour les cas courants
- **Gestion mémoire** efficace
- **Exécution directe** des built-ins
- **Cache PATH** pour les exécutables

### Compatibilité
- **POSIX compliance** pour les fonctionnalités de base
- **Bash-like behavior** pour l'expérience utilisateur
- **Cross-platform** (Linux, macOS)

## Compétences développées
- **Programmation système** avancée Unix/Linux
- **Gestion des processus** et communication inter-processus
- **Parsing** et analyse syntaxique
- **Architecture logicielle** modulaire
- **Debugging** multi-processus
- **Gestion mémoire** rigoureuse sans leaks
- **Tests** et validation de systèmes complexes

## Contraintes et normes 42
- **Norme de codage** 42 strictement respectée
- **Pas de variables globales** (sauf une pour les signaux)
- **Gestion d'erreurs** exhaustive
- **Pas de memory leaks** (validé Valgrind)
- **Fonctions autorisées** uniquement celles de la liste 42

## Challenges techniques

### Difficultés rencontrées
- **Parsing complexe** avec gestion des quotes et échappements
- **Gestion des signaux** dans un contexte multi-processus
- **Race conditions** entre processus père et fils
- **Memory management** dans un contexte d'erreurs multiples
- **Compatibilité bash** pour les edge cases

### Solutions apportées
- **Architecture modulaire** facilitant la maintenance
- **Error handling** centralisé et robuste
- **Tests exhaustifs** couvrant les cas limites
- **Documentation** du code pour la compréhension

## Auteur
Alexandre Pommier (apommier) - École 42

## Licence
Projet académique - École 42
