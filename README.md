# zondata
C data structures. From hash maps to linked lists.

## Build
### Object files

Object files are created in `./obj/`. The following command creates them:

```
make
```

### Build and run tests

Object files are created in `./obj/`, and test binaries are created in `./test/bin/`. The following command creates both, then run the binaries, and then makes clean:

```
make test
```

### Delete generated files

Deletes generated files in `./obj/` and `./test/bin/`.

```
make clean
```
