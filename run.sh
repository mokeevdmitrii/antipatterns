#!/bin/bash
#git clone https://github.com/mokeevdmitrii/antipatterns.git
# проверка существования каталога
if [ -e RPG_Game ]
then
	cd RPG_Game
	cd antipatterns
	cd antipatterns
	cd build
	a="$PWD/antipatterns"
	exec $a
	exit 0
	
else
	mkdir RPG_Game
	cd RPG_Game
	git clone https://github.com/mokeevdmitrii/antipatterns.git
	cd antipatterns
	git checkout curr
	cd antipatterns
	mkdir build
	cd build
	cmake ..
	make
	a="$PWD/antipatterns"
	exec $a
	exit 0
fi
