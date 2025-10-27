# Firefox Bookmarks and their tags

This page holds various information on how Firefox handles the tags associated with bookmarks, and (I hope) how to use them efficiently.

## Rationale

As you know probably, you can associate a saved bookmark with a couple of "tags".
Say, if you want to bookmark today some article in the New York Times about the current trouble with IA, you would add the tags:
`NYT`, `2025`, `IA`, `article`.

Fine. And you go on, day after day. And you end up with hundreds (or thousands) of bookmarks, all with tags.

The problem is now: I want to search for some bookmark that has both NYT and IA as tags.

At present (unless some way I am not aware of), you cannot do this with the current Firefox release (2025/10).

So this page will gather some information from varipous sources about how Firefox handles internally bookmarks and their tags, and one day, a solution will arise !!


## Bookmarks organization

All the bookmarks are stored using sqlite.

I found an old file (2008), showing the tables relationship:  
https://wiki.mozilla.org/images/d/d5/Places.sqlite.schema3.pdf  
(inluded [here](Places.sqlite.schema3.pdf)).

The file is called `places.sqlite` and is located (on a Linux machine) in this folder:

`~/.mozilla/firefox/z7do02ft.default-release`

(mine is currently ~100MB, so as you sse, I have a **lot** of bookmarks.

Related sources:
  - https://stackoverflow.com/questions/464516/firefox-bookmarks-sqlite-structure
  

