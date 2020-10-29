En este directorio, usted deberá implementar el programa `wgrep.c`  y compilarlo como `wgrep` (e.g., `gcc -o wgrep wgrep.c -Wall -Werror`)

Despues de hacer esto, usted  puede correr los test de este directorio al ejecutar el script `test-wgrep.sh`. Si todo sale bien, usted verá:

```sh
prompt> ./test-wgrep.sh
test 1: passed
test 2: passed
test 3: passed
test 4: passed
test 5: passed
test 6: passed
test 7: passed
prompt>
```

**Nota del autor**:

The `test-wgrep.sh` script is just a wrapper for the `run-tests.sh` script in
the `tester` directory of this repository. This program has a few options; see
the relevant
[README](https://github.com/remzi-arpacidusseau/ostep-projects/blob/master/tester/README.md)
for details.
