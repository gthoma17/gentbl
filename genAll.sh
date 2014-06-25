for file in C:/Users/imigat0/Desktop/py/gentbl/cmdlists/*.cmdlist
do
	echo "doing " $file
	python C:/Users/imigat0/Desktop/py/gentbl/generator.py $file
done