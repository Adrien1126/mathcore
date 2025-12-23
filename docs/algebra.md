# **algebra.md — Module Algebra (v0.1)**

*Documentation interne — Projet mathcore*

---

## **1. Objectif du module**

Le module **algebra** regroupe les opérations algébriques élémentaires nécessaires à la construction de futurs modules numériques (linalg, stats, optimisation, finance).
Il fournit uniquement des fonctions **simples, pures et déterministes**, couvrant :

* la résolution d’équations linéaires `ax + b = 0` ;
* la résolution d’équations quadratiques `ax² + bx + c = 0` ;
* le calcul du discriminant.

Ce module constitue la base mathématique minimale pour la suite du projet.

---

## **2. API publique (`algebra.hpp`)**

L’interface publique expose trois fonctionnalités :

```cpp
double solveLinear(double a, double b);

constexpr double discriminant(double a, double b, double c);

std::pair<double, double> solveQuadratic(double a, double b, double c);
```

### **2.1. `solveLinear(a, b)`**

Résout l’équation :

[
ax + b = 0
]

* Si `a ≠ 0`, la solution est :

[
x = -\frac{b}{a}
]

* Si `a == 0` :

  * si `b == 0` : équation indéterminée (infinité de solutions) → **throw**
  * sinon : équation impossible → **throw**

L’API doit rester simple et sûre : les cas dégénérés sont rejetés explicitement.

---

### **2.2. `discriminant(a, b, c)`**

Fonction `constexpr` permettant une évaluation à la compilation.

[
\Delta = b^2 - 4ac
]

Typiquement utilisée pour :

* déterminer la nature des racines,
* éviter de recalculer le discriminant plusieurs fois.

---

### **2.3. `solveQuadratic(a, b, c)`**

Résout :

[
ax^2 + bx + c = 0
]

Trois cas :

1. **a = 0**
   Alors l’équation devient linéaire → délégation vers `solveLinear`.

2. **Discriminant > 0**
   Deux racines distinctes :

   [
   x_{1,2} = \frac{-b \pm \sqrt{\Delta}}{2a}
   ]

3. **Discriminant = 0**
   Racine double :

   [
   x_1 = x_2 = -\frac{b}{2a}
   ]

4. **Discriminant < 0**
   Pas de solution réelle → **throw**.

Le choix v0.1 est volontairement restreint : **pas de racines complexes**, cela appartient à un module ultérieur (complex numbers).

---

## **3. Contraintes professionnelles**

* Toutes les fonctions doivent être **pures** (aucun état interne).
* `solveLinear` et `solveQuadratic` doivent **valider leurs entrées**.
* Le module doit rester **auto-contenu**.
* `discriminant` doit rester `constexpr`.
* Les exceptions doivent être explicites et cohérentes (`std::invalid_argument`).

---

## **4. Structure du module**

```
mathcore/
├── include/mathcore/
│     ├── arithmetic.hpp
│     ├── algebra.hpp
│     └── stats.hpp (à venir)
├── src/
│     ├── arithmetic.cpp
│     ├── algebra.cpp
│     └── stats.cpp (à venir)
└── tests/
      ├── test_arithmetic.cpp
      ├── test_algebra.cpp
      └── test_stats.cpp (à venir)
```

---

## **5. Comportements attendus**

### **5.1 solveLinear**

| Entrée       | Sortie                         |
| ------------ | ------------------------------ |
| a ≠ 0        | −b/a                           |
| a = 0, b = 0 | exception : infinite solutions |
| a = 0, b ≠ 0 | exception : no solution        |

---

### **5.2 solveQuadratic**

| Δ (discriminant) | Sortie                    |
| ---------------- | ------------------------- |
| Δ > 0            | deux racines distinctes   |
| Δ = 0            | racine double             |
| Δ < 0            | exception : no real roots |
| a = 0            | redirection solveLinear   |

---

## **6. Exigences de test**

Tests recommandés pour v0.1 :

### **solveLinear**

* cas nominal : a ≠ 0
* cas a = 0, b ≠ 0
* cas a = 0, b = 0

### **solveQuadratic**

* discriminant > 0 : racines réelles distinctes
* discriminant = 0 : racine double
* discriminant < 0 : exception
* test de cohérence :
  (x_1 + x_2 = -b/a),
  (x_1 * x_2 = c/a)

### **discriminant**

* pure fonctionnelle : comparer des valeurs calculées

---

## **7. Roadmap future**

Version ultérieure (v0.2 ou v0.3) :

* prise en charge des racines complexes (avec `std::complex<double>`) ;
* stabilité numérique accrue (formule robuste pour éviter la perte de précision) ;
* généralisation aux polynômes de degré supérieur via des solveurs dédiés.
