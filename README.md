# **Plan d’action — Projet mathcore**

---

## **Phase 1 — Mise en place du squelette du projet**

1. Créer la structure des dossiers :

   ```
   mathcore/
   ├── include/mathcore/
   ├── src/
   ├── tests/
   ├── CMakeLists.txt
   └── README.md
   ```

2. Configurer un **CMakeLists minimal** :

   * création d’une bibliothèque `mathcore`,
   * ajout des include directories,
   * flags stricts,
   * option BUILD_TESTS.

3. Préparer le fichier `test_main.cpp`.

---

## **Phase 2 — Implémentation du noyau mathématique (v0.1)**

Objectif : couvrir les besoins de base des futurs modules financiers.

### **Modules à développer :**

* `arithmetic` : opérations élémentaires.
* `algebra` : équation linéaire + quadratique.
* `stats` : moyenne, variance, écart-type.
* `linalg` : produit scalaire, norme, small vector.

### **Tâches**

1. Rédiger les **headers** (interfaces).
2. Implémenter les .cpp avec RAII minimal.
3. Ajouter tests unitaires basiques.

---

## **Phase 3 — Extension numérique (v0.2)**

Objectif : préparer les outils pour Monte Carlo et pricing simple.

### Modules à ajouter :

* `calculus` : dérivation numérique, intégration simple.
* `root_finding` : bisection, Newton.

### Tâches :

1. Ajouter les headers correspondants.
2. Implémenter la logique numérique.
3. Tester les méthodes (fixtures + paramétrés).

---

## **Phase 4 — Outils statistiques avancés (v0.3)**

Objectif : préparer un moteur d’analyse statistique utilisé en finance.

### Ajouts :

* covariance, corrélation,
* vecteurs centrés,
* normalisation z-score,
* estimateurs robustes.

### Tâches :

1. Décomposer statistique descriptive et inférentielle.
2. Ajouter tests avec jeux de données synthétiques.

---

## **Phase 5 — Algèbre linéaire structurée (v0.4)**

Objectif : disposer d’un module vector/matrix stable et réutilisable.

### Ajouts :

* classe `Vector` RAII,
* classe `Matrix` RAII (dense, row-major),
* multiplication M*v,
* transposition,
* norme de Frobenius.

### Tâches :

1. Implémentation RAII complète (règle des 5).
2. Gestion des exceptions (allocation).
3. Tests unitaires robustes (dimensions, erreurs).

---

## **Phase 6 — Intégration et optimisation (v0.5)**

Objectif : stabiliser mathcore avant d’en faire une dépendance.

### Tâches :

* Nettoyage API,
* ajout `constexpr` quand possible,
* benchmarks simples,
* documentation interne (`docs/architecture.md`).

---

## **Phase 7 — Version stable mathcore v1.0**

Livrable prêt pour l’intégration dans :

* Financial Payoff Engine,
* Monte Carlo Engine,
* modules de calibration,
* solveurs PDE.

### Tâches :

1. Publier le repo GitHub avec version taggée.
2. Créer un `CHANGELOG.md`.
3. Ajouter une pipeline de tests minimale.
4. Préparer un exemple d’utilisation simple.

---

# **Résumé du plan en 10 étapes**

1. Créer la structure de projet.
2. Configurer CMake.
3. Implémenter arithmetic + algebra.
4. Implémenter stats basiques.
5. Implémenter linalg minimal.
6. Ajouter tests pour chaque module.
7. Implémenter calculus + root finding.
8. Ajouter stats avancées + covariance/corrélation.
9. Implémenter RAII Vector + Matrix.
10. Consolidation, documentation, release v1.0.
