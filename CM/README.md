# Framework de compilation Latex pour des slides Beamer
 Sebastien Kramm - 2020
 LITIS

## How does this work:

* run `make`

(or `make` -j4 to make things faster)

`make clean` will... well, clean!
	

Folder description:

* `src`: your source files
* `out`: folder where the output pdf files will be generated
* `build`: folder where all the LaTeX magi happens. This is also where you will have to look in case of trouble
* `template`: here, all common header files
  * `common_header.tex`: this is where you put your personal information (name, institute, ...)
  * `head_beamer.tex`: specific stuff for regular beamer version
  * `head_handout1.tex`: specific stuff for handout version, no animations
  * `head_handout4.tex`: specific stuff for handout 4 pages on 1 version (printable)
