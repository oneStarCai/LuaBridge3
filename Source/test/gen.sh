file=test
if [ -e $file ];
then
	echo "rm old file $file"
	rm test
fi

echo "generate new file ..."
g++ -o $file test.cpp -llua
