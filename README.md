# CTTUBE

CTTUBE takes `.tb` files and compiles them into boolean expressions

A `.tb` file is simply a logical `truth table`, such as this [logical implication](https://en.wikiversity.org/wiki/Logical_implication):

```
A B | X
-------
0 0 | 1
0 1 | 1
1 0 | 0
1 1 | 1 
```

Which evaluates to the following `boolean expression`:

```
((~A)&(~B))|((~A)&(B))|((A)&(B))
```

Here is [more on the relationship between these grammars](https://en.wikipedia.org/wiki/Canonical_normal_form)

> To test this compiler and see the results for various components (`multiplexer, half_adder`, etc.), run `./run_tests.sh`