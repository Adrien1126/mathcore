# **mathcore — Module arithmetic (v0.1, API complète)**

## 1. Objectif du module

Le module `arithmetic` centralise les opérations scalaires fondamentales mises à disposition du reste de la bibliothèque.
La majorité des fonctions sont `constexpr`, ce qui permet une **évaluation à la compilation** lorsque les arguments sont constants, et garantit :

* pureté fonctionnelle,
* absence d’allocation,
* coût nul ou optimal après optimisation par le compilateur,
* utilisation dans des contextes `constexpr` (tables statiques, constantes numériques, méta-calculs).

Ce module sert de socle aux autres modules (algebra, linalg, stats, finance).

---

## 2. API publique

Header : `include/mathcore/arithmetic.hpp`

L’espace de noms est :

```cpp
namespace mathcore::arithmetic { ... }
```

### 2.1 Fonctions arithmétiques de base (`constexpr`)

| Fonction         | Description       |
| ---------------- | ----------------- |
| `add(a, b)`      | Retourne `a + b`. |
| `subtract(a, b)` | Retourne `a - b`. |
| `multiply(a, b)` | Retourne `a * b`. |
| `square(a)`      | Retourne `a²`.    |
| `cube(a)`        | Retourne `a³`.    |

Toutes ces fonctions sont **pures**, sans effets de bord, et IEEE-754 dépendantes.

---

### 2.2 Fonctions arithmétiques avec vérification (`divide`, `inverse`)

#### `divide(a, b)`

Renvoie `a / b`.

Précondition : `b != 0`.
En cas de violation : **lève `std::invalid_argument`**.

Raison : empêcher la propagation silencieuse de `inf` ou `nan`, nuisible en finance ou en analyse numérique.

#### `inverse(a)`

Renvoie `1 / a`.

Précondition : `a != 0`.
En cas de violation : **lève `std::invalid_argument`**.

Remarque : cette fonction sert de primitive pour des modules plus avancés (normalisation, optimisation, calcul matriciel).

---

### 2.3 Fonctions utilitaires (`constexpr`)

Ces fonctions fournissent des primitives essentielles pour de futurs modules :

| Fonction                  | Définition                          | Utilité                                                   |
| ------------------------- | ----------------------------------- | --------------------------------------------------------- |
| `min(a, b)`               | retourne le minimum                 | alternative légère à `std::min` (constexpr, sans include) |
| `max(a, b)`               | retourne le maximum                 | idem                                                      |
| `abs(a)`                  | valeur absolue                      | utilisée partout (stats, distance, optimisation)          |
| `sign(a)`                 | -1 si a<0, 0 si a=0, 1 si a>0       | utile en analyse numérique, gradients, modèles financiers |
| `clamp(value, low, high)` | borne dans l’intervalle [low, high] | essentiel pour éviter les dérives numériques              |

Ces fonctions étant `constexpr`, elles s’évaluent en temps de compilation si les arguments sont constants.

---

## 3. Comportement mathématique & numérique

### 3.1 Conventions IEEE-754

* Le module ne modifie pas les modes d’arrondi,
* il ne corrige pas les underflow/overflow,
* il ne gère pas explicitement les cas `nan` ou `inf` (sauf division/inversion).

### 3.2 Purity contract

Toutes les fonctions `constexpr` sont :

* sans état,
* déterministes,
* libres d’effets de bord,
* indépendantes de l’environnement.

### 3.3 Robustesse

Les seules fonctions pouvant lancer une exception sont :

* `divide()`
* `inverse()`

Ce choix maintient un comportement **safe-by-default**, indispensable dans les moteurs mathématiques ou quantitatifs.

---

## 4. Contraintes de conception

* aucune dépendance externe,
* include minimaliste : seul `<stdexcept>` peut être requis dans `arithmetic.cpp`,
* aucune allocation dynamique,
* toutes les fonctions simples sont `constexpr` pour un maximum d’optimisation,
* signatures claires et légères,
* namespace dédié `mathcore::arithmetic`.

---

## 5. Tests unitaires recommandés

Les tests doivent couvrir :

### 5.1 Tests de base

* addition, soustraction, multiplication sur :

  * positifs, négatifs, zéro,
  * valeurs extrêmes (`DBL_MAX`, `DBL_MIN` si besoin).

### 5.2 Fonctions utilitaires

* `min` / `max` — symétrie, cohérence.
* `abs` — inclure le cas `0`.
* `sign` — trois cas {-, 0, +}.
* `clamp` — trois cas : inférieur, intérieur, supérieur.
* `square` / `cube` — vérifier sur petits entiers.

### 5.3 Tests d’erreurs

```cpp
EXPECT_THROW(divide(1.0, 0.0), std::invalid_argument);
EXPECT_THROW(inverse(0.0), std::invalid_argument);
```

### 5.4 Tests constexpr

Compiler un fichier contenant :

```cpp
constexpr double x = mathcore::arithmetic::square(5.0);
static_assert(x == 25.0);
```

Cela valide la pureté de l’API.

---

## 6. Exemples d’utilisation

```cpp
#include "mathcore/arithmetic.hpp"
using namespace mathcore::arithmetic;

double a = add(2.0, 3.0);         // 5
double b = clamp(1.5, 0.0, 1.0);  // 1
double c = cube(-2.0);            // -8

double inv = inverse(4.0);        // 0.25
double ratio = divide(10.0, 2.0); // 5
```

---

## 7. Perspectives (v0.2 → v1.0)

* ajout de fonctions trigonométriques `constexpr`,
* ajout de versions SIMD (AVX/AVX2),
* extension vers des opérations vectorielles/matricielles,
* intégration avec le module `linalg`.

---

# **Conclusion**

Le module `arithmetic` constitue la brique la plus fondamentale de *mathcore*.
Son design combine :

* simplicité,
* pureté,
* sécurité,
* performance,
* compatibilité constexpr,

ce qui en fait une base idéale pour faire évoluer la bibliothèque vers des usages plus avancés (stats, optimisation, finance quantitative, calcul parallèle).

