# **mathcore — Overview (v0.1)**

## 1. Objectif général du projet

**mathcore** est une bibliothèque C++ modulaire regroupant un ensemble de fonctionnalités mathématiques fondamentales destinées à servir de base à des projets plus avancés en :

* finance quantitative (pricing, modèles stochastiques, calibration),
* data science,
* simulations numériques,
* développement d’outils internes (risk engines, analytics…).

L’objectif de la v0.1 est de construire un **socle minimal, propre, testable et extensible**, en appliquant strictement les bonnes pratiques modernes de C++ (séparation interface/implémentation, RAII, modularité, documentation, CMake, tests unitaires).

Cette première version couvre trois modules essentiels :

1. **arithmetic** — opérations scalaires élémentaires, sûres et isolées.
2. **algebra** — résolution d’équations linéaires et quadratiques.
3. **stats** — statistiques descriptives de base (moyenne, variance, écart type).

---

## 2. Architecture générale du projet

Arborescence standard :

```
mathcore/
├── include/mathcore/
│     ├── arithmetic.hpp
│     ├── algebra.hpp
│     └── stats.hpp
│
├── src/
│     ├── arithmetic.cpp
│     ├── algebra.cpp
│     └── stats.cpp
│
├── tests/                     (GoogleTest)
│     ├── test_main.cpp
│     ├── test_arithmetic.cpp
│     ├── test_algebra.cpp
│     └── test_stats.cpp
│
├── docs/
│     ├── overview.md          ← (ce document)
│     ├── arithmetic.md
│     ├── algebra.md
│     └── stats.md
│
└── CMakeLists.txt
```

### Principes d’architecture

* **include/** contient uniquement les *interfaces publiques* (headers).
* **src/** contient les implémentations (fichiers .cpp).
* **tests/** regroupe des tests exhaustifs basés sur GoogleTest.
* **docs/** regroupe la documentation fonctionnelle et technique.
* **CMakeLists.txt** construit :

  * une bibliothèque `mathcore`,
  * un exécutable optionnel pour les démonstrations/tests manuels,
  * une suite de tests unitaires.

---

## 3. Philosophie du design (v0.1)

### 3.1 Minimalisme fonctionnel

Chaque module expose uniquement l’essentiel et se concentre sur :

* simplicité,
* robustesse des contrôles,
* comportements mathématiques clairement définis,
* prévisibilité (déterminisme, exceptions explicites).

Tu construis ici la **colonne vertébrale** de librairies futures plus complexes.

### 3.2 Séparation stricte interface / implémentation

Pour tous les modules :

* `.hpp` : déclarations, documentation des contrats, préconditions.
* `.cpp` : implémentations, gestion des erreurs, détails internes.

Cela prépare :

* la compilation incrémentale optimale,
* la stabilité du code à long terme,
* une architecture modulaire évolutive.

### 3.3 Gestion rigoureuse des erreurs

Les fonctions doivent :

* vérifier systématiquement les préconditions,
* lancer des exceptions standard (`std::invalid_argument`, `std::domain_error`),
* jamais masquer un comportement non défini.

### 3.4 Testabilité

Chaque comportement défini par l’API doit être testé :

* cas normaux,
* cas limites,
* exceptions,
* robustesse numérique.

Les tests constituent la **documentation vivante** du projet.

---

## 4. Description des modules v0.1

### 4.1 Module `arithmetic`

Fonctionnalités :

* addition
* soustraction
* multiplication
* division (avec gestion stricte des divisions par zéro)

Usage : bloc fondamental pour développer des modules plus complexes (linalg, stats, models…).

Documentation : `docs/arithmetic.md`.

---

### 4.2 Module `algebra`

Fonctionnalités :

* résolution d’équations linéaires : `ax + b = 0`
* résolution d’équations quadratiques : `ax² + bx + c = 0`

Spécifications clés :

* traitement des trois régimes du discriminant,
* gestion des cas dégénérés (`a = 0`),
* invariants mathématiques testés (somme et produit des racines).

Documentation : `docs/algebra.md`.

---

### 4.3 Module `stats`

Fonctionnalités :

* `mean` (moyenne)
* `variance_population` (variance population)
* `std_dev_population` (écart-type population)

Propriétés :

* exception si vecteur vide,
* conventions explicites (population vs sample),
* précision numérique contrôlée,
* API pure (aucune mutation en place).

Documentation : `docs/stats.md`.

---

## 5. Normes C++ appliquées

* C++20, flags stricts :
  `-Wall -Wextra -Wpedantic -Werror`.
* Pas de dépendances inutiles dans les headers.
* Inclusion minimaliste.
* pas de globales, pas de singletons.
* tous les fichiers `.hpp` protégés par `#pragma once`.
* design orienté vers la testabilité et l’extensibilité.

---

## 6. Étapes futures (v0.2 → v1.0)

La v0.1 sert de base. Les prochaines évolutions prévues :

### v0.2

* introduction d’un module **linalg** (vecteurs, matrices, produits scalaires),
* stabilisation de l’API,
* extension de `stats` (covariance, corrélation),
* introduction d’un module `utils`.

### v0.3

* optimisation (inlining, constexpr, SIMD optionnel),
* ajout de tests de performance,
* début d’intégration HPC.

### v1.0

* documentation complète,
* benchmarks,
* packaging,
* intégration possible dans un projet finance (QRIS, pricers).

---

## 7. Public cible

* étudiants/jeunes diplômés en C++ et quantitative finance,
* développeurs souhaitant un socle propre pour modèles mathématiques,
* utilisateurs voulant un moteur robuste, testable, minimaliste mais extensible.

---

# **8. Conclusion**

`mathcore` est un projet formateur et structurant : tu y construis les fondations exactes que l’on retrouve dans des bibliothèques professionnelles utilisées en finance, en HPC, en simulation numérique.

La qualité de l’architecture et des tests préparera parfaitement :

* les modules futurs (linalg, probabilités, optimisation),
* les pricers C++,
* les moteurs de risk analytics,
* les projets montrables aux recruteurs.

