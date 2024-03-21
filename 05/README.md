# Semaine 05/16

- [x] Arguments des fonctions
  - [x] Valeurs par défaut (`foo(a, b=42)`)
  - [x] Keyword arguments (`foo(key='value')`)
  - [x] `args` retourne dans une liste les arguments restants (`foo(a,b, *args)`)
  - [x] `kwargs` retourne un dictionnaire des keyword-arguments (`foo(*args, **kwargs)`)
- [x] Exceptions
  - [x] `try`
  - [x] `except`
- [x] Héritage de classes
  - [x] Un héritage c'est "est-un". 
- [ ] Environnement virtuels
- [ ] `__init__.py`
- [ ] `__new__(cls, *args, **kwargs)`
- [ ] `yield`

## Arguments des fonctions

```python
def op(left, right, op='add', scale=1, offset=0, **kwargs):
    print(kwargs)
    left *= scale
    right *= scale
    left += offset
    right += offset
    if kwargs.get('inverse', False):
        (left, right) = right, left
    if op == 'add': 
        return left + right
    if op == 'sub':
        return left - right
    if op == 'mul': 
        return left * right
    if op == 'div':
        return left / right
    raise AttributeError('invalid operation')
```

## Héritage

Si vous héritez de votre grand-mère, vous n'êtes pas votre grand-mère. En informatique l'héritage est le lien "Est-un". 

Si vous êtes un Canard Mandarin, vous "êtes-un" canard mais plus joli qu'un canard.

Ici la classe `Toto` "est-une" chaîne de caractère `str`. Elle hérite donc de toutes les fonctionnalités de la chaîne de caractère.

```python
class Toto(str):
    def count_a(self):
        count = 0
        for c in self:
            if c == 'a':
                count += 1
        return count
t = Toto("les biscuits amères")
t.count_a()
```

## Auto reload

Dans IPython par défaut lorsque vous importer un module, il ne sera pas possible de réimporter les changements sans quitter et relancer IPython. 

Néanmoins vous pouvez utiliser l'extension `autoreload` depuis IPython: 

```python
%load_ext autoreload
%autoreload 2
```