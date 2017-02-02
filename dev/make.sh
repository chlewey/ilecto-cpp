!/bin/bash

BASE=`pwd`
cd $BASE
for DIR in main *;do
	if [ -d "$DIR" ]; then
		echo '-->' $DIR
		cd -P $DIR
		make
	fi
	cd $BASE
done
