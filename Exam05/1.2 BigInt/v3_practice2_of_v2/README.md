# Comprendre `BigInt::addStrings()`

## 1. But de la fonction

La fonction `addStrings()` permet d'additionner deux nombres très grands représentés par des `std::string`.

On ne peut pas forcément faire :

```cpp
int result = 123456789123456789 + 987654321987654321;
```

car le nombre peut dépasser la capacité des types classiques (`int`, `long`, etc.).

On fait donc l'addition chiffre par chiffre, comme à l'école.

```cpp
std::string BigInt::addStrings(const std::string &s1,
                               const std::string &s2) const
{
    std::string result;
    size_t i = 0, l1 = s1.size(), l2 = s2.size(), len;

    len = l1 > l2 ? l1 : l2;

    unsigned int s1_r, s2_r, res, cto = 0;

    while (i < len)
    {
        s1_r = i < l1 ? (s1[i] - '0') : 0;
        s2_r = i < l2 ? (s2[i] - '0') : 0;

        res = s1_r + s2_r + cto;

        cto = res / 10;
        res = res % 10;

        result.push_back(res + '0');
        i++;
    }

    if (cto)
        result.push_back(cto + '0');

    return (result);
}
```

---

# 2. Point très important : les chiffres sont inversés

Dans cette implémentation de `BigInt`, le nombre semble être stocké avec les chiffres inversés.

Par exemple :

```text
Nombre réel :    1234
Valeur stockée : "4321"
```

Donc :

```text
_value[0] = '4'  -> unités
_value[1] = '3'  -> dizaines
_value[2] = '2'  -> centaines
_value[3] = '1'  -> milliers
```

Pourquoi ?

Parce que dans une addition normale, on commence par les unités :

```text
    1234
  + 5678
  ------
```

On commence par :

```text
4 + 8
```

Avec la représentation inversée :

```text
"4321"
  ^
  |
i = 0
```

On commence directement par les unités.

C'est donc très pratique pour faire l'addition.

---

# 3. Les variables

```cpp
std::string result;
```

Contient le résultat final.

```cpp
size_t i = 0;
```

`i` indique la position du chiffre que l'on traite.

```cpp
l1 = s1.size();
l2 = s2.size();
```

Ce sont les longueurs des deux strings.

```cpp
len = l1 > l2 ? l1 : l2;
```

On prend la longueur du plus grand nombre.

Cela permet de traiter tous les chiffres.

---

# 4. Le `?:` (ternaire)

Cette ligne :

```cpp
len = l1 > l2 ? l1 : l2;
```

signifie :

```cpp
if (l1 > l2)
    len = l1;
else
    len = l2;
```

Même principe ici :

```cpp
s1_r = i < l1 ? (s1[i] - '0') : 0;
```

Cela signifie :

```cpp
if (i < l1)
    s1_r = s1[i] - '0';
else
    s1_r = 0;
```

Donc si le premier nombre n'a plus de chiffre, on utilise `0`.

Exemple :

```text
s1 = "321"
s2 = "98765"
```

Quand `i = 3` :

```text
s1[3] n'existe pas
```

Donc :

```text
s1_r = 0
```

C'est exactement comme si on faisait :

```text
00321
98765
```

---

# 5. Transformer un caractère en chiffre

Dans une string :

```cpp
s1[i]
```

renvoie un `char`.

Par exemple :

```cpp
s1[i] = '7';
```

Mais nous voulons le nombre :

```text
7
```

On utilise :

```cpp
s1[i] - '0'
```

Exemples :

```text
'0' - '0' = 0
'1' - '0' = 1
'2' - '0' = 2
'3' - '0' = 3
...
'9' - '0' = 9
```

Donc :

```cpp
s1_r = s1[i] - '0';
```

transforme un caractère représentant un chiffre en valeur numérique.

---

# 6. Le `carry` / la retenue

Cette variable :

```cpp
unsigned int cto = 0;
```

représente la retenue.

Par exemple :

```text
  8
+ 7
---
 15
```

On garde le `5` dans la position actuelle et on reporte `1` à la position suivante.

Donc :

```text
résultat = 5
carry = 1
```

Dans le code :

```cpp
res = 8 + 7 + 0;
```

donne :

```text
res = 15
```

Puis :

```cpp
cto = res / 10;
```

donne :

```text
cto = 15 / 10
    = 1
```

Et :

```cpp
res = res % 10;
```

donne :

```text
res = 15 % 10
    = 5
```

Donc :

```text
15
|
+-- carry = 1
|
+-- chiffre = 5
```

---

# 7. Pourquoi `/ 10` ?

Cette ligne :

```cpp
cto = res / 10;
```

permet de récupérer la retenue.

Exemples :

```text
 9 / 10 = 0
10 / 10 = 1
11 / 10 = 1
12 / 10 = 1
19 / 10 = 1
20 / 10 = 2
```

Pour une addition de deux chiffres avec une retenue, le carry est généralement `0` ou `1`.

---

# 8. Pourquoi `% 10` ?

Cette ligne :

```cpp
res = res % 10;
```

permet de garder uniquement le dernier chiffre.

Exemples :

```text
 9 % 10 = 9
10 % 10 = 0
11 % 10 = 1
12 % 10 = 2
15 % 10 = 5
19 % 10 = 9
```

Donc :

```text
res / 10 -> carry
res % 10 -> chiffre à écrire
```

---

# 9. Transformer un chiffre en caractère

Après :

```cpp
res = res % 10;
```

`res` est un nombre :

```text
0 ... 9
```

Mais `result` est une `std::string`.

Il faut donc transformer le chiffre en caractère :

```cpp
res + '0'
```

Exemple :

```text
7 + '0' = '7'
```

Puis :

```cpp
result.push_back(res + '0');
```

ajoute ce caractère à la fin de la string.

---

# 10. Exemple simple : `123 + 456`

Comme les nombres sont stockés à l'envers :

```text
123 -> "321"
456 -> "654"
```

Au départ :

```text
cto = 0
result = ""
```

## Tour 1

```text
i = 0

s1_r = 3
s2_r = 6
cto  = 0
```

Addition :

```text
3 + 6 + 0 = 9
```

Carry :

```text
9 / 10 = 0
```

Chiffre :

```text
9 % 10 = 9
```

On ajoute :

```text
result = "9"
```

---

## Tour 2

```text
i = 1

s1_r = 2
s2_r = 5
cto  = 0
```

Addition :

```text
2 + 5 + 0 = 7
```

Résultat :

```text
result = "97"
```

---

## Tour 3

```text
i = 2

s1_r = 1
s2_r = 4
cto  = 0
```

Addition :

```text
1 + 4 + 0 = 5
```

Résultat :

```text
result = "975"
```

Mais attention :

```text
"975"
```

est inversé.

Il représente :

```text
579
```

Donc :

```text
123 + 456 = 579
```

---

# 11. Exemple avec des retenues : `789 + 123`

Stockage :

```text
789 -> "987"
123 -> "321"
```

Au départ :

```text
cto = 0
result = ""
```

## Tour 1

```text
9 + 3 + 0 = 12
```

On sépare :

```text
12 / 10 = 1   -> carry
12 % 10 = 2   -> chiffre
```

Donc :

```text
result = "2"
cto = 1
```

---

## Tour 2

Attention : on utilise maintenant le carry `1`.

```text
8 + 2 + 1 = 11
```

Donc :

```text
11 / 10 = 1
11 % 10 = 1
```

Résultat :

```text
result = "21"
cto = 1
```

---

## Tour 3

```text
7 + 1 + 1 = 9
```

Donc :

```text
9 / 10 = 0
9 % 10 = 9
```

Résultat :

```text
result = "219"
cto = 0
```

Comme la string est inversée :

```text
"219" -> 912
```

Donc :

```text
789 + 123 = 912
```

---

# 12. Exemple avec des nombres de longueurs différentes

Prenons :

```text
12 + 345
```

Stockage :

```text
12  -> "21"
345 -> "543"
```

Les longueurs sont :

```text
l1 = 2
l2 = 3
```

Donc :

```cpp
len = l1 > l2 ? l1 : l2;
```

donne :

```text
len = 3
```

## Tour 1

```text
2 + 5 = 7
```

Résultat :

```text
"7"
```

## Tour 2

```text
1 + 4 = 5
```

Résultat :

```text
"75"
```

## Tour 3

`i = 2`.

Pour `s1` :

```text
s1 = "21"
```

Il n'existe pas de :

```text
s1[2]
```

Donc :

```cpp
s1_r = 0;
```

Pour `s2` :

```text
s2[2] = '3'
```

Donc :

```text
s2_r = 3
```

Addition :

```text
0 + 3 = 3
```

Résultat :

```text
"753"
```

En le remettant dans le bon sens :

```text
"753" -> 357
```

Donc :

```text
12 + 345 = 357
```

---

# 13. Exemple important : `999 + 1`

C'est le cas qui permet de comprendre le dernier `if`.

Stockage :

```text
999 -> "999"
1   -> "1"
```

## Tour 1

```text
9 + 1 + 0 = 10
```

Donc :

```text
chiffre = 0
carry = 1
```

Résultat :

```text
"0"
```

---

## Tour 2

`1` n'a plus de chiffre.

Donc :

```text
0 + 9 + 1 = 10
```

Résultat :

```text
"00"
```

Carry :

```text
1
```

---

## Tour 3

Encore :

```text
0 + 9 + 1 = 10
```

Résultat :

```text
"000"
```

Carry :

```text
1
```

La boucle est terminée.

Mais il reste :

```text
cto = 1
```

Donc :

```cpp
if (cto)
    result.push_back(cto + '0');
```

ajoute le `1`.

On obtient :

```text
"0001"
```

Comme c'est inversé :

```text
"0001" -> 1000
```

Donc :

```text
999 + 1 = 1000
```

---

# 14. Exemple : `999 + 999`

Stockage :

```text
999 -> "999"
999 -> "999"
```

## Tour 1

```text
9 + 9 + 0 = 18

carry = 1
chiffre = 8

result = "8"
```

## Tour 2

```text
9 + 9 + 1 = 19

carry = 1
chiffre = 9

result = "89"
```

## Tour 3

```text
9 + 9 + 1 = 19

carry = 1
chiffre = 9

result = "899"
```

Après la boucle :

```text
cto = 1
```

Donc on ajoute :

```text
result = "8991"
```

Inversion :

```text
"8991" -> 1998
```

Donc :

```text
999 + 999 = 1998
```

---

# 15. Résumé du fonctionnement

La fonction fait exactement ceci :

```text
1. Prendre le chiffre de s1
2. Prendre le chiffre de s2
3. Ajouter l'ancien carry
4. Calculer le résultat
5. Récupérer le nouveau carry avec / 10
6. Récupérer le chiffre avec % 10
7. Ajouter le chiffre au résultat
8. Passer au chiffre suivant
9. À la fin, ajouter le dernier carry s'il existe
```

On peut résumer le coeur avec :

```text
             ancien carry
                  |
                  v
        chiffre1 + chiffre2
                  |
                  v
                res
               /   \
              /     \
             v       v
          / 10      % 10
            |         |
            v         v
        nouveau     chiffre
         carry      résultat
```

---

# 16. Les quatre opérations importantes

## `s1[i] - '0'`

Convertit :

```text
char -> nombre
```

Exemple :

```text
'7' -> 7
```

---

## `res / 10`

Récupère la retenue :

```text
15 / 10 = 1
```

---

## `res % 10`

Récupère le chiffre :

```text
15 % 10 = 5
```

---

## `res + '0'`

Convertit :

```text
nombre -> char
```

Exemple :

```text
5 -> '5'
```

---

# 17. Pourquoi cette méthode fonctionne pour BigInt ?

Parce qu'on ne fait jamais l'opération sur le nombre entier.

On travaille uniquement avec des chiffres :

```text
0 à 9
```

Par exemple, même si on a :

```text
123456789123456789123456789
```

on peut traiter :

```text
9 + ...
8 + ...
7 + ...
...
```

un chiffre à la fois.

La taille du nombre n'est donc pas limitée par `int` ou `long`.

C'est le principe essentiel d'un `BigInt` basé sur une `std::string`.

---

# 18. À retenir pour l'examen 42

Si on te demande d'expliquer `addStrings()`, tu peux retenir :

```text
Les nombres sont stockés à l'envers afin de commencer
l'addition par les unités.

À chaque position :

    res = chiffre1 + chiffre2 + carry

Puis :

    carry = res / 10
    chiffre = res % 10

Le chiffre est converti en char avec :

    chiffre + '0'

et ajouté avec :

    result.push_back(...)

Si un carry reste après la dernière position,
on l'ajoute au résultat.
```

La logique est donc exactement celle d'une addition manuelle :

```text
        carry
          |
          v
        8 7
      + 6 5
      -----
```

On commence par les unités, on garde le chiffre des unités et on reporte la retenue vers la gauche.

La seule différence est que le `BigInt` stocke les chiffres **à l'envers** pour rendre cette opération simple avec `i = 0`.
