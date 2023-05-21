# GnuMake : rans notes on some advanced features

* author: S. Kramm
* started: 2023-05-21
* status: WIP
* goal: document some advanced features for GnuMake

These are some random notes about make, not intended (yet) to be a real tutorial.
It assumes the reader has basic knowledge of what make is and how to use it.

ref:
* https://www.gnu.org/software/make/manual/make.html
* https://www.gnu.org/software/make/manual/html_node/index.html

## Some special targets that can be useful:

ref: https://www.gnu.org/software/make/manual/html_node/Special-Targets.html

### 1 - `.PHONY`
Initially, this was intended to handle the case if some target names could collide with real file names. But it can also be used to designate targets whose recipes will allways be executed, whatever their dependencies.

### 2 - `.PRECIOUS and .SECONDARY`
The targets referenced by these will not be erased when one of the recipes fail.
The diffence between those is that `PREVIOUS` can take a pattern rule (say, `%.c`) while `SECONDARY` requires a full target name.

### 3 - `.ONESHELL`
this will tell Make to use the same shell for all the steps of the recipe.
The defaul behavior is to open a new shell for every line.

For example, consider the following makefile (assumes there is a `dummyfile` in current folder):

```
all:
	mkdir -p dummyfolder
	cd dummyfolder
	cp ../dummyfile .
```
On the first line, it creates a subfolder. On second line it moves into it. And on third line, it attemps to copy the file from the above folder to the current one.

This will fail, because each line is run in a new shell, that has the makefile's folder as current one.
So a correct writing should be:

```
all:
	mkdir -p dummyfolder
	cd dummyfolder; cp ../dummyfile .
```

But by defining `.ONESHELL` on the top of the file, you can use the first version.



ref: https://stackoverflow.com/questions/27090032/


