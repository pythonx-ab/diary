# Semaine 02/16

## Types

### Scalaires

- Entiers (`42`)
- Réels (`3.1415`)
- Complexes (`2 + 3j`)
- Chaîne de caractères ('abc')

### Conteneurs 

#### Séquentiels

- Liste (`[1,2,3,4]`) Modifiable
- Tuple (`(1,2,3,4)`) Immuable

#### Associatifs

- Set (`{1,2,3,4}`)
- Dictionnaire (`{'bob': 42, 'alice': 23}`)

## Classes

Une **class** est la définition d'un type de données qui contient des **données** (que l'on nomme **attribut**), et des actions (que l'on nomme **méthodes**).

Voici une classe pour définir un nouveau point:

```python
class Point:
    def __init__(self, x, y):
        self.a = x
        self.b = y
    def length(self):
        return math.sqrt(self.a * self.a + self.b * self.b)
    def __repr__(self):
        return f"Point({self.a}, {self.b})"
    def __add__(self, other):
        return Point(self.a + other.a, self.b + other.b)
```

## Objets

Un objet c'est la **réalisation** ou **l'instanciation** d'une classe. Alors qu'une classe n'est que la définition d'un type, l'objet contient des données. On peut dire qu'une classe c'est le plan de fabrication d'une maison et que l'objet est la maison. 

Lorsque vous faites : `i = 42` vous créez un nouvel objet `i` issu de la classe `int`.

