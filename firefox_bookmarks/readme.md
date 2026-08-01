# Firefox Bookmarks and their tags

(WIP !)

This page holds various information on how Firefox handles the tags associated with bookmarks, and (I hope) how to use them efficiently.

## Rationale

As you know probably, you can associate a saved bookmark with a couple of "tags".
Say, if you want to bookmark today some article in the New York Times about the current trouble with IA, you would add the tags:
`NYT`, `2025`, `IA`, `article`.

Fine. And you go on, day after day. And you end up with hundreds (or thousands) of bookmarks, all with tags.

The problem is now: I want to search all bookmarks that has both `NYT` and `IA` as tags.

At present (unless some way I am not aware of), you cannot do this with the current Firefox release (2025/10).

So this page will gather some information from various sources about how Firefox handles internally bookmarks and their tags, and one day, a solution will arise !!


## Bookmarks organization

All the bookmarks are stored using sqlite.

I found an old file (2008), showing the tables relationship:  
https://wiki.mozilla.org/images/d/d5/Places.sqlite.schema3.pdf  
(inluded [here](Places.sqlite.schema3.pdf)).

The file is called `places.sqlite` and is located (on a Linux machine) in this folder:  
`~/.mozilla/firefox/XXXXX.default-release`,
with `XXXXX` being your current profile, that you can see in `~/.mozilla/firefox/profiles.ini`.

(mine is currently ~100MB, so as you see, I have a **lot** of bookmarks.

Related sources:
  - https://stackoverflow.com/a/740183/193789

Pasted here (just in case):

---

_The central place for all URLS in the database is moz_places. The table moz_bookmarks refers to it by the foreign key column fk._

_If you tag a bookmark, there are multiple entries in moz_bookmarks, all having the same reference fk: The first is the bookmark itself (having the title in the title column) For each tag, there's an additional entry in moz_bookmarks having the same foreign key fk and refering to the tag in the parent coumn (which points to the moz_bookmarks row for the tag)._

_If you have a bookmark 'http://stackoverflow.com' titled 'Stackoverflow' with tags 'programming' and 'info', you will get:_
```
moz_places
----------
id    url   (some more)
3636  http://stackoverflow.com

moz_bookmarks
-------------
id    type    fk     parent    title          (other columns omitted...)
332   1       3636   5         Stackoverflow  (parent=5 -> unfiled folder)
333   2       (NULL) 4         programming    (programming tag, parent=4 -> tags folder)
334   1       3636   333       (NULL)         (link to 'programming' tag)
335   2       (NULL) 4         info           (info tag, parent=4 see above)
336   1       3636   335       (NULL)         (link to 'info' tag)
```

---


This [question](https://superuser.com/questions/771110/) from SO addresses this issue but unfortunately, none of the provided solutions seem to work anymore.


## Tools

Sqlite provides a CLI app: `sqlite3`.  
Can be installed with:
`$ sudo apt install sqlite`

A GUI app is available here: https://sqlitebrowser.org/

Can be installed with:
`$ sudo apt install sqlitebrowser`

Manual: https://sqlite.org/cli.html

## Vibe coding
https://chatgpt.com/share/6a6db33c-7c7c-83eb-a829-fe91e5009778


Sunday 11:54 AM
peux-tu m'orienter vers une extension Firefox qui permettent de faire une requete multiple sur les tags des signets. Quelque chose qui permettent de taper deux mots-clés (par exemple "IA" et "Python") et qui renvoie la liste des signets qui ont été tagué avec ces deux mot-clés.

Si ton objectif est de retrouver les signets qui possèdent simultanément plusieurs tags (intersection des tags), j'ai deux remarques importantes :

    Firefox sait déjà faire une recherche par intersection de tags, mais uniquement depuis la barre d'adresse, pas depuis la bibliothèque des signets. Il suffit de précéder la recherche d'un +. Par exemple :

+ IA Python

renvoie les signets possédant les deux tags IA et Python, et non ceux qui ont l'un ou l'autre. Cette fonctionnalité est peu connue mais existe depuis longtemps.

En revanche, la bibliothèque (Ctrl+Shift+O) ne permet toujours pas de sélectionner plusieurs tags simultanément, ce qui fait l'objet de demandes récurrentes auprès de Mozilla.
Si tu cherches une extension

Je n'en ai malheureusement pas trouvé une qui ajoute directement cette fonctionnalité aux tags natifs de Firefox.

Les plus proches sont :

    Bookmark Tag Manager

        ajoute son propre système de tags ;

        permet de filtrer et rechercher selon plusieurs critères ;

        interface moderne ;

        mais n'utilise pas les tags natifs de Firefox.

    Bookmark tags

        permet des recherches multicritères ;

        mais les "tags" sont en réalité des hashtags (#python, #IA) intégrés au titre du signet, pas les tags Firefox.

Si tu utilises déjà les tags natifs de Firefox

À ma connaissance, il n'existe pas d'extension mature qui enrichisse directement la recherche sur ces tags. Les API WebExtensions donnent accès aux signets, mais les tags natifs sont très peu exposés, ce qui explique probablement cette absence.
Une autre possibilité

Si tu manipules plusieurs milliers de signets et que tu souhaites faire des requêtes du type :

IA AND Python
NOT MachineLearning
(tag:Rust OR tag:C++)

je pourrais te proposer un petit outil (Python ou C++) qui lit directement la base places.sqlite de Firefox et fournit une interface de recherche beaucoup plus puissante que celle du navigateur. C'est généralement la solution la plus flexible pour un gros volume de signets.

curieux, quand je tape + IA Python dans la barre d'adresse, j'ai un message d'erreur comme quoi cette requet est incorrecte (Firefox version 151). Sais-tu pourquoi?

Oui, et c'est une bonne remarque. En fait, je pense que je t'ai induit en erreur en mélangeant deux mécanismes de recherche de Firefox.

Le préfixe + n'est pas (ou n'est plus) un opérateur de recherche booléenne des tags dans la barre d'adresse. Sur Firefox 151, il est normal que tu obtiennes un message indiquant que la requête est incorrecte.

Plusieurs explications sont possibles :

    cette syntaxe a existé dans des versions anciennes ou expérimentales de Firefox et a disparu ;

    ou je l'ai confondue avec la syntaxe de recherche interne de la base SQLite (places.sqlite) ou avec les recherches de la bibliothèque.

Après vérification de mes connaissances, je ne connais pas de syntaxe officielle permettant de faire une intersection de tags dans la barre d'adresse de Firefox 151. La recherche se comporte essentiellement comme une recherche plein texte sur les titres, URL et tags, mais sans opérateurs booléens sur les tags.

Malheureusement, cela confirme ce que beaucoup d'utilisateurs reprochent au gestionnaire de signets de Firefox : il est impossible, avec l'interface native, de rechercher les signets possédant simultanément plusieurs tags. Mozilla n'a toujours pas ajouté cette fonctionnalité.

Si tu souhaites, je peux chercher sur le Web s'il existe une extension récente compatible avec Firefox 151 ou une syntaxe cachée/documentée qui aurait été ajoutée récemment. Les extensions évoluant régulièrement, une recherche en ligne serait le meilleur moyen de te donner une réponse fiable.

Oui, et je pense même que c'est la variante la plus intéressante pour explorer une grosse collection de signets. L'idée est simplement de filtrer les tags lors du group_concat().

Voici la requête :

SELECT
    p.url,
    group_concat(t.title, ';')
FROM moz_places p
JOIN moz_bookmarks b
    ON p.id = b.fk
JOIN moz_bookmarks t
    ON b.parent = t.id
WHERE p.id IN
(
    SELECT b2.fk
    FROM moz_bookmarks b2
    WHERE b2.parent IN
    (
        SELECT id
        FROM moz_bookmarks
        WHERE title IN ('IA','Python')
    )
    GROUP BY b2.fk
    HAVING COUNT(DISTINCT b2.parent)=2
)
AND t.title NOT IN ('IA','Python')
GROUP BY p.id
ORDER BY p.url;

Le résultat devient :

https://url1.com;Anthropic;2026
https://url2.com;LLM
https://url3.com;2025

Adaptation au script Bash

Le script devient simplement :

#!/bin/bash

DB="$HOME/.mozilla/firefox/z7do02ft.default-release/places.sqlite"

if [ $# -eq 0 ]; then
    echo "Usage: $0 tag1 [tag2 ...]"
    exit 1
fi

tags=$(printf "'%s'," "$@")
tags=${tags%,}

sqlite3 -separator ";" "$DB" "
SELECT
    p.url,
    COALESCE(group_concat(t.title, ';'), '')
FROM moz_places p
JOIN moz_bookmarks b
    ON p.id = b.fk
LEFT JOIN moz_bookmarks t
    ON b.parent = t.id
   AND t.title NOT IN ($tags)
WHERE p.id IN
(
    SELECT b2.fk
    FROM moz_bookmarks b2
    WHERE b2.parent IN
    (
        SELECT id
        FROM moz_bookmarks
        WHERE title IN ($tags)
    )
    GROUP BY b2.fk
    HAVING COUNT(DISTINCT b2.parent) = $#
)
GROUP BY p.id
ORDER BY p.url;
"

J'ai utilisé un LEFT JOIN avec le filtre dans la clause ON plutôt qu'un WHERE. C'est important : ainsi, si un signet ne possède que les tags recherchés, il apparaîtra quand même dans le résultat, avec une seconde colonne vide.

Par exemple, si tu recherches :

./bookmarks.sh IA Python

tu pourrais obtenir :

https://openai.com;Anthropic;LLM;2026
https://docs.python.org;
https://huggingface.co;Transformers;PyTorch

La deuxième URL est bien conservée, même si elle ne possède aucun tag supplémentaire.
Une amélioration que je trouve encore plus pratique

Si tu comptes utiliser ce script comme un véritable outil d'exploration de tes signets, je remplacerais group_concat() par :

group_concat(t.title, ';')
ORDER BY t.title

ou, si ta version de SQLite ne permet pas ORDER BY directement dans group_concat(), je passerais par une sous-requête. Les tags seraient alors affichés dans un ordre alphabétique stable :

https://url1.com;2026;Anthropic;Python
https://url2.com;Java
https://url3.com;2025;Python

Au bout de quelques centaines de signets, cette simple mise en ordre rend les résultats beaucoup plus agréables à parcourir.

Je ne comprends pas, dans les résultats de ce script, certaines URL apparaissent avec le tag toolbar, alors que ce tag n'existe pas, je l'ai vérifié via l'interface graphique de Firefox. Sais-tu pourquoi?

Oui, et je pense savoir exactement pourquoi. C'est lié à la façon dont Firefox stocke ses signets.

Dans moz_bookmarks, tout est représenté comme un "bookmark item" :

    les véritables tags (ceux visibles dans l'interface),

    les dossiers,

    la barre personnelle ("Bookmarks Toolbar"),

    le menu des signets,

    "Autres marque-pages",

    etc.

Or, dans notre requête, nous avons fait implicitement l'hypothèse que tout parent d'un signet est un tag, ce qui est faux.

En particulier, le dossier interne Bookmarks Toolbar a pour nom interne toolbar. Si un signet est placé dans la barre personnelle, il possède une entrée dans moz_bookmarks dont le parent est ce dossier, et notre JOIN le récupère comme s'il s'agissait d'un tag.

Pour t'en convaincre, exécute :

SELECT id, guid, title
FROM moz_bookmarks
WHERE title='toolbar';

ou même :

SELECT id, guid, title, type
FROM moz_bookmarks
WHERE guid='toolbar_____';

Tu devrais trouver le dossier système correspondant à la barre personnelle.
Pourquoi cela arrive-t-il ?

En réalité, un signet possédant trois tags possède plusieurs entrées dans moz_bookmarks :

moz_places
----------
id=42
url=https://example.com

moz_bookmarks
-------------
fk=42 parent=<Bookmarks Toolbar>
fk=42 parent=<tag IA>
fk=42 parent=<tag Python>
fk=42 parent=<tag 2026>

Notre requête récupère toutes les lignes ayant le même fk, sans distinguer si le parent est un dossier "normal" ou un véritable dossier de tags.
Comment distinguer un vrai tag ?

Firefox range tous les tags sous un dossier spécial nommé Tags.

Autrement dit, un tag est un dossier dont le parent est le dossier "Tags".

On peut le retrouver par exemple avec :

SELECT id
FROM moz_bookmarks
WHERE guid='tags_______';

(ou en cherchant le titre Tags, selon la langue et la version de Firefox).

Ensuite, il suffit d'ajouter une contrainte du genre :

JOIN moz_bookmarks t
  ON b.parent = t.id
WHERE t.parent = <id_du_dossier_Tags>

Ainsi, seuls les véritables tags seront pris en compte dans le group_concat(), et toolbar, menu, unfiled, etc. disparaîtront.

Je peux également te proposer une requête 100 % robuste, qui n'utilise aucun nom de dossier (toolbar, Tags, etc.) et se base uniquement sur les GUID internes de Firefox (tags_______, toolbar_____, ...). Elle sera indépendante de la langue de Firefox (français, anglais, etc.) et plus résistante aux changements d'intitulés. C'est la solution que je recommanderais si tu comptes conserver ce script sur le long terme.

Oui, propose moi cette version, indépendante de la langue.

Oui, et je pense qu'il vaut mieux repartir de la structure réelle de places.sqlite, car il y a un point important que nous avons simplifié.
La hiérarchie réelle

Firefox possède un dossier racine dont le GUID est toujours :

root________

Sous celui-ci se trouvent notamment :
GUID	Rôle
menu________	Menu des signets
toolbar_____	Barre personnelle
unfiled_____	Autres marque-pages
mobile______	Signets mobiles
tags_______	Racine des tags

Les vrais tags sont les enfants du dossier tags_______.

Par exemple :

root________
 ├── toolbar_____
 ├── menu________
 ├── unfiled_____
 └── tags_______
      ├── IA
      ├── Python
      ├── 2026
      └── Anthropic

Chaque tag est lui-même un dossier contenant des "copies" des signets.
Une requête robuste

La première étape consiste à ne considérer comme tags que les enfants de tags_______.

Pour cela, on peut utiliser une CTE (WITH) qui construit la liste des tags :

WITH tag_folder AS (
    SELECT id
    FROM moz_bookmarks
    WHERE guid='tags_______'
),

tags AS (
    SELECT id,title
    FROM moz_bookmarks
    WHERE parent=(SELECT id FROM tag_folder)
)

Ensuite, toute la requête ne manipule plus que cette table virtuelle tags.

Par exemple :

WITH

tag_folder AS (
    SELECT id
    FROM moz_bookmarks
    WHERE guid='tags_______'
),

tags AS (
    SELECT id,title
    FROM moz_bookmarks
    WHERE parent=(SELECT id FROM tag_folder)
)

SELECT
    p.url,
    group_concat(tags.title,';')
FROM moz_places p
JOIN moz_bookmarks b
    ON b.fk=p.id
JOIN tags
    ON tags.id=b.parent
...

Ainsi :

    toolbar_____ est ignoré ;

    menu________ est ignoré ;

    unfiled_____ est ignoré ;

    seuls les véritables tags restent.

Encore mieux : supprimer complètement les sous-requêtes

En fait, si j'étais amené à utiliser souvent cette base SQLite, je construirais une vue représentant la relation « URL ↔ tags ».

Par exemple :

CREATE VIEW bookmark_tags AS

SELECT
    p.id      AS place_id,
    p.url,
    t.title   AS tag

FROM moz_places p

JOIN moz_bookmarks b
    ON b.fk=p.id

JOIN moz_bookmarks t
    ON t.id=b.parent

WHERE t.parent=(
    SELECT id
    FROM moz_bookmarks
    WHERE guid='tags_______'
);

À partir de là, la base devient beaucoup plus agréable à interroger.

Les URL ayant les tags IA et Python s'obtiennent simplement par :

SELECT url
FROM bookmark_tags
WHERE tag IN ('IA','Python')
GROUP BY url
HAVING COUNT(DISTINCT tag)=2;

Et les autres tags associés :

SELECT
    url,
    group_concat(tag,';')
FROM bookmark_tags
GROUP BY url;

Ce que je te conseillerais

Vu les questions que tu poses, j'ai l'impression que tu cherches à faire de places.sqlite une véritable base documentaire de tes signets, avec des recherches avancées.

Dans ce cas, je te proposerais de créer une vue SQL (ou deux) qui masque complètement la structure assez alambiquée de moz_bookmarks. Ensuite, toutes les requêtes (intersection de tags, exclusion de tags, statistiques, export CSV, etc.) deviennent très courtes et lisibles. On peut même ajouter des recherches du type :

    IA AND Python

    IA AND NOT OpenAI

    Python OR Rust

    tag:2026 AND tag:Anthropic AND NOT tag:Vidéo

sans jamais avoir à se préoccuper des GUID, des dossiers système ou des duplications internes de moz_bookmarks. Je pense que ce serait une base beaucoup plus agréable pour développer les outils de recherche que tu envisages.



## Notes







