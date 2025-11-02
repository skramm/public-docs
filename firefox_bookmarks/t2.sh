set +x
nb=$#

if [ $nb == 0 ]
then
	echo "error, at least one tag required"
	exit 1
fi

echo "nb arg=$# arg=$1"

echo ".open /home/sk/.mozilla/firefox/z7do02ft.default-release/places.sqlite" >temp_command
echo -n "select fk from moz_bookmarks where title='ARG1'" >>temp_command
for ((i=1;i<$nb;i++))
do
	echo "i=$i"
	j=$((i+1))
	echo -n " AND title='ARG$j'" >>temp_command
done
echo ";" >>temp_command

if [ -f temp_command2 ]; then
	rm temp_command2
fi


for ((i=0;i<$nb;i++))
do
	echo "i=$i, arg1=$1"
	j=$((i+1))
	sed -i s/ARG$j/$1/ temp_command
	shift
done
sqlite3 <temp_command  >out2.txt

