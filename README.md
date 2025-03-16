# zondata
Zondata is a library for data structures written in C, from hash maps to linked lists..

## Build
Before running the main build and test commands, you need to initialize the project by creating the required directories. This can be done by executing the following command:

```
make init
```

### Object files

Object files are created in `./obj/`. The following command creates them:

```
make
```

### Build and run tests

Object files are created in `./obj/`, and test binaries are created in `./test/bin/`. The following command creates both, then runs the binaries, and then makes clean:

```
make test
```

### Delete generated files

Deletes generated files in `./obj/` and `./test/bin/`.

```
make clean
```
