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


## Notes







