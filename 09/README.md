# Semaine 09/16

- [x] Surcharge de l'operateur crochets
  - [x] Avec `__getitem__`, et `slice`
- [x] for loop: items, keys, values
- [x] zip(a,b), zip(*v)
- [x] sort, sorted
- [x] Vos questions ?

- [ ] __new__
- [ ] reduce

## Elements de langage

- `enumerate`
- `slice`
- `zip`
- `__getitem__(self)`
- `__setitem__(self, a, b)`
- `.sort()`
- `sorted(iterable)`
- `map(lambda x: x*10, iterable)`

## Vos questions

1. Différence d'utilisation entre un `assert` et un `raise AttributeError`
2. Pytest, comment ça fonctionne ?
3. `__getitem__ ` ça fonctionne comment ? Pour la surcharge crochet ?
4. Donner deux applications avec `itertools`
5. Que font les deux astrix dans `**kwargs`
6. C'est quoi une instance ?
7. Comment ça fonctionne les décorateurs ?
8. Un petit rappel sur `args` et `kwargs` ? C'est quoi la différence
9. C'est quoi une instance, et une classe ?
10. C'est quoi la différence entre un tuple et une liste ?
11. Quelques clarifications sur les exceptions
12. C'est quoi l'utilité d'utiliser des `_` ou `__` pour cacher des variables ?
13. Est-ce qu'on a le droit d'utiliser les membres privés ou protégés (`_`, ou `__`) ?
14. Est-ce que les attributs cachés dans python implique que l'on ne peut pas faire un programme *safe* en Python ?
15. Différences entre une fonction et un opérateur ?
16. Quelle serait l'utilité de la classe itérable dans le premier labo ?
17. C'est quoi le but de la fonction `__init__ ?
18. Est-ce possible d'éclaircir le `__new__` ?
19. C'est quoi le `@wrap`
20. L'héritage avec `str`
21. Utilisation des exceptions avec `with` ?
22. C'est quoi le but des getter et des setter ?
23. Et ce fichier `__init__`, faut-il une methode __init__?


### 1. Différence d'utilisation entre un `assert` et un `raise AttributeError`

La fonction `assert` empruntée à d'autres langage est très pratique pour vérifier qu'une [assertion](https://fr.wikipedia.org/wiki/Assertion) est correcte. Par exemple si une fonction qui résoud un polynôme du deuxième degré est supposée toujours avoir une solution réelle, vous pouvez vous assurer que le cas delta négatif ne se produit jamais. S'il se produit, c'est que votre fonction est mal utilisée, et une exception du type `AssertionError` est alors levée.

```python
def solve(a, b, c):
    delta = b**2 - 4*a*c
    assert delta >= 0, "Delta must be positive"
    return (-b + math.sqrt(delta))/(2*a), (-b - math.sqrt(delta))/(2*a)
```

Dit autrement, lorsqu'on utilise `assert` on se dit "Je m'assure que mon delta soit supérieur ou égal à zéro". Si la fonction est appelée avec `solve(1,2,3)` vous obtiendrez:

```python
Cell In[1], line 3, in solve(a, b, c)
      1 def solve(a, b, c):
      2     delta = b**2 - 4*a*c
----> 3     assert delta >= 0, "Delta must be positive"
      4     return (-b + math.sqrt(delta))/(2*a), (-b - math.sqrt(delta))/(2*a)

AssertionError: Delta must be positive
```

L'utilisation de `raise AttributeError('message')` lève aussi une exception mais du type `AttributeError`, le assert génère plutôt une exception `AssertionError`. La question est de savoir la différence entre `assert condition, message` et `if not condition: raise AssertionError()`. La réponse est que l'assert est généralement plus lisible.

Néanmoins, l'assert est une instruction qui peut être désactivée en utilisant l'option `-O` ou `python -O`. Dans ce cas, les assertions ne sont pas évaluées. Il est donc recommandé d'utiliser `raise` pour les cas où vous voulez être sûr que l'exception est levée.

On utilise préférablement le `assert` en développement pour vérifier que les préconditions sont respectées. En production, on utilise plutôt le `raise` pour s'assurer que les exceptions sont bien levées.

### 2. Pytest, comment ça fonctionne ?

Pytest est un *framework* de [tests unitaires](https://fr.wikipedia.org/wiki/Test_unitaire) qui va automatiquement chercher dans un module Python les fichiers qui commencent par le mot `test` et les fonctions qui commencent par `test`. Pytest va automatiquement appeler toutes ces fonctions et vérifier qu'elles ne génèrent pas d'exceptions. Cela vous permet de tester facilement un module, simplement en exécutant `pytest` ou `python3 -mpytest`.

Il existe un long historique de framework de tests dans Python, on connaît par exemple:

- `unittest` qui est le module de test standard de Python
- `doctest` qui permet de tester des exemples dans la documentation
- `nose` qui est un framework de test plus avancé que `unittest`
- `pytest` qui est le framework de test le plus utilisé en Python, et le plus récent.

L'écriture de tests avec `pytest` est très simple. Il suffit de créer un fichier `test_monmodule.py` et d'écrire des fonctions qui commencent par `test`. Par exemple:

```python
import pytest

def test_addition():
    assert 1+1 == 2

def test_exception_division():
    with pytest.raises(ZeroDivisionError):
        fonction_qui_divise_par_zero()
```

### 3. `__getitem__ ` ça fonctionne comment ? Pour la surcharge crochet ?

Le *datamodel* de Python décrit un ensemble de méthodes magiques qui commencent et finissent par un double *underscore*. La plupart des opérateurs `*`, `+` correspondent à des méthodes magiques `__add__`, `__mul__`... L'opérateur crochet `a[2]` est aussi un opérateur et dispose par conséquent de ses propres méthodes magiques `__getitem__` et `__setitem__`.

En Python vous pouvez passer n'importe quoi dans l'opérateur crochets: `a[2]`, `a["test"]`, `a[1,2,3,4]`, `a[2:3:4]`. Ici un entier, une chaîne de caractère, un tuple de 4 éléments et un `slice`. Le `slice` est un élément particulier uniquement utilisé dans la surcharge de l'opérateur crochet. Un slice peut être créé avec `slice(1,100,3)`. Une instance de `slice` dispose de trois attributs en lecture : `start`, `end` et `step`. Ici `start` vaut 1, `end` vaut 100 et `step` vaut trois. Écrire `a[2:3:4]` est équivalent à `a[slice(2,3,4)]`.

Généralement la surcharge de l'opérateur `[]` passe par plusieurs tests de type:

```python
classe MaClasse:
    def __getitem__(self, value):
        if isinstance(value, int):
            """ Cas de figure si entier """
            return 42
        if isinstance(value, slice):
            """ Cas de figure si slice """
            return 23
        # Sinon lève une exception
        raise TypeError("Invalid type for")
```

### 4. Donner deux applications avec `itertools`

Le module `itertools` est un module très puissant faisant partie de la distribution standard qui permet de manipuler des itérables de manière très efficace. Par exemple, `itertools.chain` permet de concaténer plusieurs itérables en un seul, `itertools.cycle` permet de répéter un itérable indéfiniment, `itertools.permutations` permet de générer toutes les permutations d'un itérable, `itertools.combinations` permet de générer toutes les combinaisons d'un itérable.

**Cas de cartes à jouer**: On veut générer toutes les combinaisons possibles de 5 cartes parmi un jeu de 52 cartes. On peut utiliser `itertools.combinations` pour générer toutes les combinaisons possibles de 5 cartes parmi 52.

```python
import itertools

cartes = range(52)
combinaisons = itertools.combinations(cartes, 5)
```

**Cas d'un cadenas à 3 chiffres**: On veut générer toutes les combinaisons possibles d'un cadenas à 3 chiffres. On peut utiliser `itertools.product` pour générer toutes les combinaisons possibles de 3 chiffres parmi 10.

```python
import itertools

chiffres = range(10)
combinaisons = itertools.product(chiffres, repeat=3)
```

**Cas d'une permutation de 4 éléments**: On veut générer toutes les permutations possibles de 4 éléments. On peut utiliser `itertools.permutations` pour générer toutes les permutations possibles de 4 éléments.

```python
import itertools

elements = range(4)
permutations = itertools.permutations(elements)
```

### 5. Que font les deux astrix dans `**kwargs`

Les deux astérisques `**` dans `**kwargs` permettent de déballer un dictionnaire en une liste de paramètres nommés. Par exemple, si vous avez une fonction `f` qui prend trois paramètres `a`, `b` et `c`, vous pouvez appeler `f` avec un dictionnaire `d` qui contient les valeurs de `a`, `b` et `c`:

```python
def f(a, b, c):
    return a+b+c

d = {'a': 1, 'b': 2, 'c': 3}
f(**d)
```

Ceci équivaut d'appeler `f` avec `f(a=1, b=2, c=3)`.

A l'inverse, si vous avez une fonction `g` qui prend un nombre quelconque de paramètres nommés, vous pouvez les récupérer dans un dictionnaire `kwargs`:

```python
def g(**kwargs):
    return kwargs
```

Un seul astérisque `*` permet de déballer une liste en une liste de paramètres. Par exemple, si vous avez une liste `l` qui contient trois éléments, vous pouvez appeler `f` avec `l`:

```python
def f(a, b, c):
    return a+b+c

l = [1, 2, 3]
f(*l)
```

Donc :

- `*args` permet de déballer une liste en une liste de paramètres
- `**kwargs` permet de déballer un dictionnaire en une liste de paramètres nommés

Les noms `args` (ARGumentS) et `kwargs` (KeyWord ARGumentS) sont des conventions, vous pouvez les appeler comme vous voulez.

### 6. C'est quoi une instance ?

En programmation orientée objet, une instance est un objet qui a été créé à partir d'une classe. Par exemple, si vous avez une classe `Personne`, vous pouvez créer une instance de cette classe en appelant `Personne()`. Cette instance est un objet qui a été créé à partir de la classe `Personne`.

```python
class Personne:
    def __init__(self, nom, prenom):
        self.nom = nom
        self.prenom = prenom

    def say_hello(self):
        print(f"Hello, my name is {self.prenom} {self.nom}")

    @property
    def email(self):
        return f"{self.prenom.lower()}.{self.nom.lower()}@heig-vd.ch"

bob = Personne("Dylan", "Bob")
alice = Personne("Cooper", "Alice")
print(alice.say_hello()) # Hello, my name is Alice Cooper
print(bob.email) # bob.dylan@heig-vd.ch
```

### 7. Comment ça fonctionne les décorateurs ?

Un décorateur est une fonction qui prend une autre fonction en argument et retourne une nouvelle fonction. Les décorateurs sont utilisés pour ajouter des fonctionnalités à une fonction sans modifier son code. Par exemple, si vous avez une fonction `f` qui prend en paramètre des valeurs en degrés Farhenheit et retourne une distance en Inch mais que vous voulez l'utiliser dans le système métrique, vous pourriez écrire un décorateur `@farhenheit_to_celsius` qui convertit les valeurs en degrés Celsius avant d'appeler la fonction `f`.

```python
def farhenheit_to_celsius(f):
    def wrapper(farhenheit):
        celsius = (farhenheit - 32) * 5/9
        return f(celsius)
    return wrapper

@farhenheit_to_celsius
def f(celsius):
    return celsius * 2.54
```

De manière plus générale, un décorateur vous permet d'exécuter du code avant et après l'appel d'une fonction. Par exemple, vous pourriez écrire un décorateur `@timeit` qui mesure le temps d'exécution d'une fonction:

```python
import time

def timeit(f):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = f(*args, **kwargs) # Appel de la fonction
        end = time.time()
        print(f"Execution time: {end-start} seconds")
        return result
    return wrapper

def fib(n):
    if n <= 1:
        return n
    return fib(n-1) + fib(n-2)

@timeit
def fibonaci(n):
    return fib(n)
```

On aurait par exemple:

```python
>>> print(fibonaci(30))
Execution time: 0.151625394821167 seconds
832040
```

Bien souvent les décorateurs sont définis dans un module à part, et importés dans le module principal. Par exemple, le module `functools` de la distribution standard contient un décorateur `@lru_cache` qui permet de mettre en cache les résultats d'une fonction et améliorer ses performances:

```python
from functools import lru_cache

@lru_cache
def fib(n):
    if n <= 1:
        return n
    return fib(n-1) + fib(n-2)
```

On peut montrer que l'exécution de cette fonction pour des valeurs de `n` élevées est beaucoup plus rapide que sans le cache.

On utilise également les décorateurs pour les getter et les setters ainsi que dans le module click.

### 8. Un petit rappel sur `args` et `kwargs` ? C'est quoi la différence

`*args` et `**kwargs` sont des conventions pour passer un nombre variable de paramètres à une fonction. `*args` permet de passer un nombre variable de paramètres positionnels, `**kwargs` permet de passer un nombre variable de paramètres nommés.

Par exemple, si vous avez une fonction `f` qui prend un nombre variable de paramètres positionnels, vous pouvez les récupérer dans une liste `args`:

```python
def f(*args):
    return args

print(f(1, 2, 3)) # (1, 2, 3), vous récupérez un tuple
```

Si vous avez une fonction `g` qui prend un nombre variable de paramètres nommés, vous pouvez les récupérer dans un dictionnaire `kwargs`:

```python
def g(**kwargs):
    return kwargs

print(g(a=1, b=2, c=3)) # {'a': 1, 'b': 2, 'c': 3}, vous récupérez un dictionnaire
```

Vous pouvez aussi combiner les deux:

```python
def h(*args, **kwargs):
    return args, kwargs

print(h(1, 2, 3, a=1, b=2, c=3)) # ((1, 2, 3), {'a': 1, 'b': 2, 'c': 3})

```

### 9.  C'est quoi une instance, et une classe ?

En programmation orientée objet, une classe est un modèle qui définit un ensemble d'attributs (paramètres) et de méthodes (actions) communes à un ensemble d'objets. Par exemple, si vous avez une classe `str` qui définit une chaîne de caractères, vous pouvez créer une instance de cette classe en appelant `str()` et appeler des actions sur cette instance comme `upper()`, `lower()`, `replace()`, `split()`.

```python
s = str("Hello, World!")
print(s.upper()) # HELLO, WORLD!
print(s.lower()) # hello, world!
print(s.replace("Hello", "Goodbye")) # Goodbye, World!
print(s.split(",")) # ['Hello', ' World!']
```

### 10.  C'est quoi la différence entre un tuple et une liste ?

Un tuple et une liste sont deux types de données en Python qui permettent de stocker une collection d'éléments. La principale différence entre un tuple et une liste est que les tuples sont **immuables** et les listes sont **mutables**. Cela signifie que vous ne pouvez pas modifier un tuple une fois qu'il a été créé, alors que vous pouvez modifier une liste.

Le point essentiel est qu'un type immuable est hashable, c'est-à-dire qu'il peut être utilisé comme clé dans un dictionnaire. Par exemple, vous pouvez utiliser un tuple comme clé dans un dictionnaire, mais pas une liste.

```python
d = {(1, 2, 3): "Hello, World!"} # Valide car (1, 2, 3) est un tuple
e = {[1, 2, 3]: "Hello, World!"} # Invalide car [1, 2, 3] est une liste
```

Bienq que vous puissiez créer un tuple contenant une référence vers une liste, ce tuple, ne sera par conséquent pas hashable:

```python
>>> hash(([],))
---------------------------------------------------------------------------
TypeError                                 Traceback (most recent call last)
hash(([],))

TypeError: unhashable type: 'list'
```

### 11.  Quelques clarifications sur les exceptions

Les exceptions sont des objets qui sont levés lorsqu'une erreur se produit dans un programme. Les exceptions peuvent être attrapées et gérées par le programme, ou laissées se propager jusqu'à ce qu'elles soient attrapées par le programme principal. Les exceptions sont des objets qui héritent de la classe `BaseException`.

Lorsque vous faite un `raise` vous pouvez lever n'importe quel objet qui hérite de `BaseException`. Par exemple, vous pouvez lever une exception `ValueError` si une valeur est incorrecte, une exception `TypeError` si un type est incorrect, une exception `KeyError` si une clé n'existe pas dans un dictionnaire. L'exception `AttributeError` est levée si un attribut n'existe pas dans un objet tandis que `IndexError` est levée si un index est hors des limites.

Les éléments standards de Python utilisent des exceptions pour signaler des erreurs. Par exemple, si vous essayez d'accéder à un élément d'une liste qui n'existe pas, une exception `IndexError` est levée:

```python
>>> u = [1, 2, 3]
>>> u[4]
---------------------------------------------------------------------------
IndexError                                Traceback (most recent call last)
```

Vous pouvez attraper une exception avec un bloc `try` et `except`:

```python
try:
    u[4]
except IndexError:
    print("Index out of range")
```

### 12.  C'est quoi l'utilité d'utiliser des `_` ou `__` pour cacher des variables ?

En Python, les noms qui commencent par un seul underscore `_` sont considérés comme des variables privées. Cela signifie que ces variables ne sont pas censées être utilisées en dehors de la classe ou du module dans lequel elles sont définies. Par exemple, si vous avez une classe `Personne` qui a un attribut `_nom`, vous ne devriez pas accéder directement à cet attribut en dehors de la classe.

Le double underscore `__` est utilisé pour cacher des variables de manière plus stricte. Les noms qui commencent par un double underscore sont mangled, c'est-à-dire qu'ils sont renommés pour éviter les collisions de noms. Par exemple, si vous avez une classe `Personne` qui a un attribut `__nom`, cet attribut sera renommé en `_Personne__nom` pour éviter les collisions de noms.

En Python il n'existe pas de sécurité parfaite, et il est toujours possible d'accéder à des variables privées en utilisant des astuces. Par exemple, vous pouvez accéder à un attribut privé en utilisant `obj._Personne__nom` si vous connaissez le nom de la classe. C'est pourquoi il est recommandé de ne pas utiliser des attributs privés pour cacher des informations sensibles.

La philosophie de Python est que ses utilisateurs sont des adultes responsables, et que la plupart du temps, ils savent ce qu'ils font. C'est pourquoi Python ne force pas la protection des variables privées, mais laisse la responsabilité aux programmeurs.

### 13.  Est-ce qu'on a le droit d'utiliser les membres privés ou protégés (`_`, ou `__`) ?

En Python, les membres privés ou protégés sont des conventions qui permettent de signaler que certaines variables ou méthodes ne sont pas censées être utilisées en dehors de la classe ou du module dans lequel elles sont définies.

En pratique il n'y a pas de protection réelle des membres privés ou protégés en Python. Aussi, lorsque vous utilisez une bibliothèque tierce, et bien que vous puissiez accéder à des membres privés ou protégés, il est recommandé de ne pas le faire, car vous n'avez aucune garantie que ces membres ne changeront pas dans une version ultérieure de la bibliothèque.

### 14.  Est-ce que les attributs cachés dans python implique que l'on ne peut pas faire un programme *safe* en Python ?

Effectivement, il n'y a pas de moyen de réellement cacher quelque chose en Python car le langage est reflectif, c'est-à-dire qu'il permet d'inspecter et de modifier les objets à l'exécution.

### 15.  Différences entre une fonction et un opérateur ?

En Python, une fonction est un objet qui prend des arguments et retourne une valeur. Par exemple, la fonction `f` prend un argument `x` et retourne `x**2`:

```python
def f(x):
    return x**2
```

Un opérateur est un symbole qui effectue une opération sur des valeurs. Par exemple, l'opérateur `+` effectue une addition sur deux valeurs:

Dans des langages comme C, les opérateurs hardcodé dans la syntaxe du langage et il n'y a pas moyen de les redéfinir. En Python, les opérateurs sont des méthodes magiques qui peuvent être redéfinies dans les classes. Par exemple, si vous avez une classe `Vecteur` qui définit une addition de vecteurs, vous pouvez redéfinir l'opérateur `+` pour effectuer cette opération:

```python
class Vecteur:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Vecteur(self.x + other.x, self.y + other.y)
```

À chaque opérateur correspond une méthode magique:

| Opérateur | Méthode magique |
| --------- | --------------- |
| `+`       | `__add__`       |
| `-`       | `__sub__`       |
| `*`       | `__mul__`       |
| `/`       | `__truediv__`   |
| `//`      | `__floordiv__`  |
| `%`       | `__mod__`       |
| `**`      | `__pow__`       |
| `<<`      | `__lshift__`    |
| `>>`      | `__rshift__`    |
| `&`       | `__and__`       |
| `|`       | `__or__`        |
| `^`       | `__xor__`       |
| `~`       | `__invert__`    |
| `<`       | `__lt__`        |
| `<=`      | `__le__`        |
| `==`      | `__eq__`        |
| `!=`      | `__ne__`        |
| `>`       | `__gt__`        |
| `>=`      | `__ge__`        |

Etc.

### 16.  Quelle serait l'utilité de la classe itérable dans le premier labo ?

Dans le laboratoire du pendu, on vous demande de créer une classe `Words` qui est un itérable. C'est à dire que cette classe doit implémenter la méthode `__iter__` qui retourne un itérateur. Un itérateur est un objet qui implémente la méthode `__next__` qui retourne l'élément suivant de l'itérable.

Une instance de `Words` peut donc générer des mots selon une configuration définie à la création de son instance:

```python
class Words:
    """ A simple word generator """
    def __init__(self, filename, size=None):
        self.filename = filename
        with open(self.filename, encoding='utf-8') as f:
            self.words = f.readlines()
        self.words = [word.split(',')[0] for word in self.words]
        if size:
            self.words = list(filter(lambda x: len(x) == size, self.words))

    def __next__(self):
        return random.choice(self.words)

    def __iter__(self):
        return self
```

On peut donc utiliser cette classe pour générer des mots aléatoires de taille 5:

```python
words = Words("dictionnaire.txt", 5)
for _ in range(10):
    print(next(words))
```

Ou alors, demander le mot suivant:

```python
mot = next(words)
```

### 17.  C'est quoi le but de la fonction `__init__ ?

Init n'est pas une fonction mais la méthode magique `__init__` qui est appelée lorsqu'une instance d'une classe est créée. Cette méthode est utilisée pour initialiser les attributs de l'instance. Par exemple, si vous avez une classe qui décrit un animal, vous pouvez initialiser les attributs de l'animal dans la méthode `__init__`:

```python
class Animal:
    def __init__(self, nom, espece):
        self.nom = nom
        self.espece = espece

    ...
```

### 18.  Est-ce possible d'éclaircir le `__new__` ?

La méthode magique `__new__` est appelée lorsqu'une nouvelle instance d'une classe est créée. Cette méthode est utilisée pour créer l'instance de la classe. La méthode `__new__` est particulière car elle ne reçois pas `self` qui est l'instance de la classe mais `cls` qui est la classe elle-même. La méthode `__new__` est généralement utilisée pour personnaliser la création d'une instance d'une classe. En général son utilisation reste maginale.

### 19.  C'est quoi le `@wrap`

La fonction wraps du module functools en Python est très utile pour écrire des décorateurs de fonctions proprement. Lorsque vous écrivez un décorateur, il peut être important de "préserver" certaines métadonnées de la fonction originale, comme son nom et sa documentation. Utiliser wraps aide à garder ces informations intactes.

Voici un exemple simple de l'utilisation de functools.wraps:

Imaginons que vous voulez créer un décorateur qui imprime un message avant et après l'exécution de la fonction décorée. Sans wraps, les métadonnées de la fonction originale ne seraient pas préservées.

```python
from functools import wraps

def my_decorator(f):
    @wraps(f)
    def wrapped(*args, **kwargs):
        print("Avant l'appel de la fonction.")
        result = f(*args, **kwargs)
        print("Après l'appel de la fonction.")
        return result
    return wrapped

@my_decorator
def say_hello(name):
    """Saluer une personne"""
    print(f"Hello, {name}!")

say_hello("Alice")
print(say_hello.__name__)  # Affiche 'say_hello'
print(say_hello.__doc__)   # Affiche 'Saluer une personne'
```

Dans cet exemple :

1. Le décorateur my_decorator utilise wraps pour envelopper la fonction wrapped.
2. `wraps` prend la fonction f comme argument et s'applique au décorateur interne wrapped. Cela copie les métadonnées (comme `__name__`, `__doc__`, etc.) de `f` à wrapped.
3. Lorsque vous décorez say_hello avec my_decorator, et que vous appelez `say_hello`, vous voyez les messages avant et après l'appel, tout en conservant le nom et la documentation de say_hello.
4. Sans `wraps`, `say_hello.__name__` aurait retourné "wrapped" et say_hello.`__doc__` aurait été `None`.

L'utilisation de `wraps` est une bonne pratique pour s'assurer que les décorateurs n'obscurcissent pas la fonctionnalité des fonctions qu'ils décorent.

### 20.  L'héritage avec `str`

En Python, vous pouvez hériter de la classe `str` pour créer une sous-classe qui a des fonctionnalités supplémentaires. On appelle cela de l'héritage. Par exemple, vous pouvez créer une classe `Majuscule` qui hérite de `str` et qui convertit automatiquement les chaînes de caractères en majuscules:

```python
class Majuscule(str):
    def __new__(cls, value):
        return super(Majuscule, cls).__new__(cls, value.upper())
```

En Python la classe `str` est particulière car elle est immuable. Cela signifie que vous ne pouvez pas modifier une chaîne de caractères une fois qu'elle a été créée. C'est pour cette raison qu'en général on utilise la méthode `__new__` pour créer une nouvelle instance de la classe.

### 21.  Utilisation des exceptions avec `with` ?

En Python, la déclaration `with` est utilisée pour gérer des ressources qui doivent être nettoyées après utilisation. Par exemple, si vous ouvrez un fichier

```python
with open("fichier.txt", "r") as f:
    for line in f:
        print(line)
```

La déclaration `with` garantit que le fichier est fermé après utilisation, même si une exception est levée pendant l'exécution du bloc `with`. En fait, la déclaration `with` est équivalente à un bloc `try` et `finally`:

```python
f = open("fichier.txt", "r")
try:
    for line in f:
        print(line)
finally:
    f.close()
```

Lorsqu'on utilise le framework de test `pytest`, on peut utiliser `with` pour vérifier qu'une exception est levée:

```python
def test_exception():
    with pytest.raises(ValueError):
        raise ValueError("This is an exception")
```

On peut créer des context managers personnalisés en définissant une classe qui implémente les méthodes `__enter__` et `__exit__`:

```python
class ContextManager:
    def __enter__(self):
        print("Entrée dans le contexte")
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        print("Sortie du contexte")
        return True

with ContextManager() as cm:
    print("Dans le contexte")
```

Cet exemple affichera:

```
Entrée dans le contexte
Dans le contexte
Sortie du contexte
```

Python garanti que la méthode `__exit__` est appelée même si une exception est levée dans le bloc `with`.

### 22. C'est quoi le but des getter et des setter ?

Les getter et les setter sont des méthodes qui permettent de contrôler l'accès aux attributs d'une classe. Les getter sont des méthodes qui permettent de récupérer la valeur d'un attribut, les setter sont des méthodes qui permettent de modifier la valeur d'un attribut.

Historiquement avec l'apparition des langages orientés objet, on a commencé à utiliser des getter et des setter pour contrôler l'accès aux attributs d'une classe. Par exemple, si vous avez une classe `Personne` qui a un attribut `age`, vous pouvez utiliser un getter pour récupérer l'âge de la personne et un setter pour modifier l'âge de la personne. On peut évidemment n'avoir qu'un setter ou qu'une seule getter pour éviter d'avoir le doit de modifier un attribut, ou d'obtenir sa valeur.

Alternativement un getter peut permettre de calculer une valeur à partir d'autres attributs de la classe. Par exemple, si vous avez une classe `Rectangle` qui a des attributs `longueur` et `largeur`, vous pouvez utiliser un getter pour calculer la surface du rectangle:

```python
class Rectangle:
    def __init__(self, longueur, largeur):
        self.longueur = longueur
        self.largeur = largeur

    @property
    def surface(self):
        return self.longueur * self.largeur
```

L'avantage du getter par rapport à la méthode `surface` est que vous pouvez accéder à la surface comme un attribut:

```python
r = Rectangle(10, 5)
print(r.surface) # 50
```

En Python les getter et setter sont réalisés avec des décorateurs. Le décorateur `@property` est utilisé pour définir un getter, le décorateur `@attribut.setter` est utilisé pour définir un setter, où `attribut` est le nom de l'attribut que vous voulez modifier.

```python
class Personne:
    def __init__(self, nom, prenom):
        self.nom = nom
        self.prenom = prenom

    @property
    def nom_complet(self):
        return f"{self.prenom} {self.nom}"

    @nom_complet.setter
    def nom_complet(self, value):
        self.prenom, self.nom = value.split(" ")
```

### 23. Et ce fichier `__init__`, faut-il une methode __init__?

Le fichier `__init__.py` est un fichier spécial qui est utilisé pour initialiser un package Python. Ce fichier peut être vide, ou contenir du code d'initialisation. Lorsqu'un package est importé, le fichier `__init__.py` est exécuté.

C'est à dire que lorsque vous utilisez la directive `import monpackage`, le fichier `__init__.py` est exécuté. Cela permet de définir des variables, des fonctions, des classes, etc. qui seront disponibles dans le package.

A l'inverse le fichier `__main__.py` est un fichier qui est exécuté lorsque vous appelez un package Python avec la commande `python -m monpackage`. Cela permet de définir un point d'entrée pour votre package.