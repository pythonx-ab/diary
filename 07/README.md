# Semaine 07/16

- [ ] TE le 25 avril 2024
  - [ ] Tout
- [ ] CI/CD
  - [ ] Continuous Integration / Continuous Deployment
  - [ ] GitHub Actions (.github/workflows/ci.yml)
  - [ ] Tests automatiques selon des critères (quand on push)
  - [ ] Tester la couverture du code (codecov)
- [ ] Framework de test
  - [ ] Test unitaire (tester des fonctions et des classes)
  - [ ] Test d'integration ou tests fonctionnels  
- [ ] Modules

- Boilerplate
- Sucre Sytaxique

## Setter/Getter

```python

class Toto:
    def __init__(self):
        self._foo = 42

    @property # Getter
    def foo(self):
        return self._foo - 10

    @foo.setter
    def foo(self, value):
        self._foo = value + 10

t = Toto
#t.foo = 0
t.foo = 32
print(t.foo)


class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    @property    
    def length(self):
        return math.sqrt(x**2 + y**2)

## Module Python

```



## Test unitaire

```python
def add(a, b):
    if a > 42:
        raise ValueError("Max value is 42")
    return a + b


def test_add():
    assert(add(2,3) == 5)
    assert(add(3,2) == 5)
    assert(add(0,3) == 3)
    for a,b in products(list(range(10)), 2):
        assert(add(a, b) == a + b)
    with pytest.raises(ValueError):
        add(42, 0)





with open("foo.bar", "r") as fp:
    fp.readall()


FILE *fp = fopen("foo.bar", 'r')
...
fclose(fp)

