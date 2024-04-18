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

La fonction `assert` empruntée à d'autres langage est très pratique pour vérifier qu'une assertion est correcte. Par exemple si une fonction qui résoud un polynôme du deuxième degré est supposée toujours avoir une solution réelle, vous pouvez vous assurer que cela fonctionne: 

```python
def solve(a, b, c):
    delta = b**2 - 4*a*c
    assert(delta >= 0)
    return (-b + math.sqrt(delta))/(2*a), (-b - math.sqrt(delta))/(2*a)
```

Dit autrement, lorsqu'on utilise assert on se dit "Je m'assure que mon delta soit supérieur ou égal à zéro"

L'utilisation de raise `AttributeError` lève une autre exception, le assert génère plutôt une exception `AssertionError`. La question est de savoir la différence entre `assert(condition)` et `if not condition: raise AssertionError()`. La réponse est que l'assert est généralement plus lisible. 

### 2. Pytest, comment ça fonctionne ? 

Pytest est un *framework* de tests unitaires qui va automatiquement chercher dans un module Python les fichiers qui commencent par le mot `test` et les fonctions qui commencent par `test`. Pytest va automatiquement appeler toutes ces fonctions et vérifier qu'elles ne génèrent pas d'exceptions. Cela vous permet de tester facilement un module, simplement en exécutant `pytest` ou `python3 -mpytest`.

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