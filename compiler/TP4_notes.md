Pour la partie génération de code (section 4 du sujet TP4.pdf), vous aurez besoin de concaténer des listes d'instructions. La fonction `list_append(uint64_t* l1, uint64_t* l2)` déclarée dans `ast.h` et définie dans `ast.c` remplit ce rôle.

Les arguments de cette fonction doivent tous les deux être des listes, pas des éléments de listes.

Ainsi on pourra concaténer les listes `[1, 2, 3]` et `[4,5]` :

```
list_append(cons(1, cons(2, cons(3, nil()))), cons(4, cons(5, nil())))
```

Ou bien, pour rajouter un simple élément en fin de liste:

```
list_append(ma_liste, cons(element_a_ajouter_en_fin_de_liste, nil()))
```  
 
