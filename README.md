# CTTUBE

CTTUBE takes `.tb` files and compiles them into boolean expressions

A `.tb` file is simply a logical `truth table`, such as this:

```
A B C D | X
-----------
0 0 0 0 | 1
0 0 1 0 | 0
0 1 0 1 | 1
0 1 1 0 | 0
1 0 0 1 | 1
1 0 1 0 | 0
1 1 0 0 | 1
1 1 1 0 | 0
1 1 1 1 | 1 
```

Which evaluates to the following `boolean expression`:

```
((~A)&(~B)&(~C)&(~D))|((~A)&(B)&(~C)&(D))|((A)&(~B)&(~C)&(D))|((A)&(B)&(~C)&(~D))|((A)&(B)&(C)&(D)) 
```

Here is [more on this logical relationship](https://en.wikipedia.org/wiki/Canonical_normal_form)

> To run this program, edit the `.tb` file to your desired truth table, and then run `./compile.sh`
