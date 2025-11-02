# t3.sh

# single argument (tag)

set +x
nb=$#

if [ $nb == 0 ]
then
	echo "error, at least one tag required"
	exit 1
fi

echo "nb arg=$# arg=$1"

echo ".open /home/sk/.mozilla/firefox/z7do02ft.default-release/places.sqlite" >temp_command
echo "select id from moz_bookmarks where title='$1';" >>temp_command

sqlite3 <temp_command >out2.txt

index=$(cat out2.txt)
echo "index=$index"

echo ".open /home/sk/.mozilla/firefox/z7do02ft.default-release/places.sqlite" >temp_command
echo "select fk from moz_bookmarks where parent='$index';" >>temp_command
sqlite3 <temp_command >out3.txt


echo ".open /home/sk/.mozilla/firefox/z7do02ft.default-release/places.sqlite" >temp_command
for a in $(cat out3.txt);
do
	echo $a
	echo "select url from moz_places where id='$a';" >>temp_command
done
sqlite3 <temp_command >out4.txt




