# CM Framework

* What is this: it is a Framework to build Beamer slides in different format from a single Latex source file
* author: Sebastien Kramm - 2020
* licence: WTFPL
* what's that name: *CM* means *Cours Magistral* in french

## How does this work:


 1. Edit your LaTeX source files in the `src` folder
 2. run `make`<br>
(or `make -j4` to make things faster)
 3. Check out your output pdf files in the `out` folder
 
`make clean` will... well, clean!


## Folder description:

* `src`: your source files
* `out`: folder where the output pdf files will be generated
* `build`: folder where all the LaTeX magi happens. This is also where you will have to look in case of trouble
* `template`: here, all common header files
  * `common_header.tex`: this is where you put your personal information (name, institute, ...)
  * `head_beamer.tex`: specific stuff for regular beamer version
  * `head_handout1.tex`: specific stuff for handout version, no animations
  * `head_handout4.tex`: specific stuff for handout 4 pages on 1 version (printable)
