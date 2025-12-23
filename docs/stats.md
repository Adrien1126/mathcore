# **stats.md — Module Statistics (v0.1)**

*Documentation interne — Projet mathcore*

---

## **1. Objectif du module**

Le module **stats** fournit les statistiques descriptives fondamentales nécessaires dans :

* le traitement de données,
* la finance quantitative (returns, volatilities, standardization),
* l'analyse numérique,
* la normalisation et pré-traitement pour machine learning,
* les modules futurs (régressions, covariance matrices, PCA, Monte Carlo).

Les fonctions sont **pures** sauf celles qui modifient explicitement leurs arguments (`centered`, `normalize_zscore`).
Toutes les opérations sont effectuées sur `std::vector<double>`, en cohérence avec la v0.1 du projet.

---

## **2. API publique (`stats.hpp`)**

```cpp
double mean(const std::vector<double>& v);
double variance_population(const std::vector<double>& v);
double variance_sample(const std::vector<double>& v);
double stddev(const std::vector<double>& v);
double sum(const std::vector<double>& v);
double min(const std::vector<double>& v);
double max(const std::vector<double>& v);
double range(const std::vector<double>& v);
void centered(std::vector<double>& v);
void normalize_zscore(std::vector<double>& v);
```

---

## **3. Description détaillée des fonctions**

### **3.1 sum(v)**

Retourne :

[
\sum_{i=1}^{n} v_i
]

Préconditions :

* `v.size() > 0`.

---

### **3.2 mean(v)**

Retourne :

[
\mu = \frac{1}{n} \sum_{i=1}^{n} v_i
]

Préconditions :

* vecteur non vide → **throw std::invalid_argument** si `v.empty()`.

---

### **3.3 variance_population(v)**

Formule :

[
\sigma^2 = \frac{1}{n} \sum_{i=1}^{n} (v_i - \mu)^2
]

Notes :

* Version **population** (division par `n`).
* Précondition identique : `v.size() > 0`.
* Utilisée en finance pour des moyennes et volatilities population.

---

### **3.4 variance_sample(v)**

Formule :

[
s^2 = \frac{1}{n - 1} \sum_{i=1}^{n} (v_i - \mu)^2
]

Notes :

* Version **échantillon** (division par `n - 1`).
* Précondition : `v.size() >= 2`.

---

### **3.5 stddev(v)**

Retourne l’écart-type population par défaut :

[
\sigma = \sqrt{\sigma^2}
]

Conventions :

* Appelé comme raccourci naturel.
* Doit utiliser `variance_population`.

---

### **3.6 min(v)** et **max(v)**

Calculent les bornes du vecteur.

Préconditions :

* `v.size() > 0`.

À ne pas confondre avec la version `mathcore::arithmetic::min`, qui est scalaire.

---

### **3.7 range(v)**

[
\text{range} = \max(v) - \min(v)
]

Préconditions :

* vecteur non vide.

---

### **3.8 centered(v)**

Centre le vecteur :

[
v_i \leftarrow v_i - \mu
]

Caractéristiques :

* **Modifie v en place.**
* Moyenne finale du vecteur = 0 (à une tolérance machine près).
* Utilisé en pré-processing, PCA, régressions.

Préconditions :

* vecteur non vide.
* fonction mutative → ne renvoie rien.

---

### **3.9 normalize_zscore(v)**

Normalisation Z-score :

[
v_i \leftarrow \frac{v_i - \mu}{\sigma}
]

Où :

* `μ` = moyenne,
* `σ` = stddev population.

Utilité :

* machine learning, statistique, outlier detection,
* mettre les variables dans un espace comparable,
* utilisé dans des pipelines financiers (volatility scaling, standardization).

Préconditions :

* `v.size() >= 2`
  (σ = 0 pour un vecteur constant → **throw std::invalid_argument**).

Mutateur (modifie v).

---

## **4. Gestion des erreurs**

Toutes les fonctions doivent :

1. vérifier que `v.size() > 0` pour sum/mean/min/max/range/variance_population,
2. vérifier que `v.size() >= 2` pour variance_sample, stddev, normalize_zscore,
3. lancer **std::invalid_argument** en cas d’entrée invalide.

Comportements interdits :

* retourner `nan` en silence,
* division silencieuse par zéro,
* se reposer sur `std::accumulate` sans vérifier la taille.

---

## **5. Contraintes de conception**

* pas de dépendances externes,
* pas d’allocation mémoire :
  *sauf les copies internes nécessaires dans les versions non mutatives* (ici aucune),
* opérations en **double**, cohérence avec arithmetic,
* aucune exception non documentée,
* uniquement des boucles simples (v0.1),
* **pas encore d’optimisation SIMD** (prévue v0.3),
* prédictibilité totale (pas de random).

---

## **6. Exigences de tests unitaires**

### Tests généraux

* vecteurs simples : `[1,2,3,4]`
* vecteurs négatifs
* vecteurs avec valeurs flottantes
* vecteurs très grands / très petits

### Tests d’erreur

* vecteurs vides
* vecteur de taille 1 pour variance_sample, stddev, normalize_zscore
* vecteur constant pour normalize_zscore → σ = 0 → exception

### Tests spécifiques

* mean : vérifier sum(v)/n
* variance_population / sample : comparaison explicite
* centered :

  * mean(final vector) ≈ 0
* normalize_zscore :

  * mean(final vector) ≈ 0
  * stddev(final vector) ≈ 1

### Cas extrêmes

* valeurs proches du max double
* très grandes valeurs vs très petites (stabilité relative)

---

## **7. Exemples d’utilisation**

```cpp
#include "mathcore/stats.hpp"
using namespace mathcore::stats;

std::vector<double> v = {1.0, 2.0, 3.0, 4.0};

double m = mean(v);               // 2.5
double s = stddev(v);            // ~1.118
double r = range(v);             // 3.0

centered(v);                     // v devient {-1.5, -0.5, 0.5, 1.5}

normalize_zscore(v);             // normalisation standard
```

---

## **8. Perspectives (v0.2 → v1.0)**

Prochaines extensions :

### **v0.2**

* covariance,
* correlation,
* weighted statistics,
* aggregations multi-variables.

### **v0.3**

* implémentation numérique stable (formules de Welford),
* SIMD (AVX2/AVX512),
* accumulation Kahan.

### **v1.0**

* matrices de covariance et corrélation,
* préparation des modules PCA, regressions, Monte Carlo.

---

# **Conclusion**

Le module **stats** fournit les briques statistiques de base indispensables à tout moteur numérique, analytique ou financier.
Les distinctions entre population/sample, la pureté des fonctions, la rigueur des préconditions et l’inclusion d’outils de préparation des données (centered, z-score) assurent une cohérence complète avec le reste de la bibliothèque *mathcore*.

