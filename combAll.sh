for file in C:/Users/imigat0/Desktop/py/gentbl/html/*.html
do
	echo "doing " $file
	cat $file >> all.html
done