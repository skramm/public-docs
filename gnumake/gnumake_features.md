# GnuMake : rans notes on some advanced features

* author: S. Kramm
* started: 2023-05-21
* status: WIP
* goal: document some advanced features for GnuMake

# Preamble:
These are some random notes about make, not intended (yet) to be a real tutorial.
It assumes the reader has basic knowledge of what make is and how to use it.

Being a longterm GnuMake user, I got to know it pretty well, but I always discover new tricks, so here are some of these (no specific order of importance!)

References:
* https://www.gnu.org/software/make/manual/make.html
* https://www.gnu.org/software/make/manual/html_node/index.html

## A - Some special targets that can be useful:

ref: https://www.gnu.org/software/make/manual/html_node/Special-Targets.html

### 1 - `.PHONY`
Initially, this was intended to handle the case when some target names could collide with real file names.
But it can also be used to designate targets whose recipes will allways be executed, whatever their dependencies.

### 2 - `.PRECIOUS and .SECONDARY`
The targets referenced by these will not be erased when one of the recipes fail.
The diffence between those is that `PREVIOUS` can take a pattern rule (say, `%.c`) while `SECONDARY` requires a full target name.

ref: https://stackoverflow.com/questions/27090032/

### 3 - `.SUFFIXES`

GnuMake has a lot of builtin rules.
For example
You can automatically disable all these built-in rules by writing an empty rule:
```
.SUFFIXES:
```

### 4 - `.ONESHELL`
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


### 5 - `.DEFAULT_GOAL`
This will define the default target, that will be run when make is run without any argument.
For example:

```
.DEFAULT_GOAL=help
```


Without this, make will run the first target found in makefile.

## B - Some useful variables

### B1 - SHELL

This defines the shell to use for recipe execution. The default shell for GnuMake is
`/bin/sh`. This can be demonstrated by the following target:
```
all:
    echo "SHELL=$(SHELL)"
```
that should print `SHELL=/bin/sh`.

If you need some features relying on another shell (say, `bash`), then you need to add
`SHELL=bash` on top of your Makefile, else some of your recipes might fail unexpectedly.

Note that some source recommend adding the full path. But as its location is not always the same ( can be `/usr/bin/bash` or `/bin/bash`), you might encounter some failures.
And as `bash` sould definitely be in the machine's path, the pathless definition above should be okay.

Note: the  "make command substitution syntax" (double `$` sign) does not seem to work with variable assignements, so this:
```
SHELL=$$(which bash)
```
does not work.




