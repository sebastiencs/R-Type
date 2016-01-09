R-Type
=====

The purpose of this project is to create a one to four players game, based on a client / server architecture.

![Alt text](R-Type.png?raw=true "R-Type")

Build:  

Windows  
	mkdir build; cd build;  
	cmake -G "Visual Studio 14 2015" -DSFML_ROOT=$DIR_INSTAL_SFML ..  
	Open solution in Visual Studio  

Unix  
	mkdir build; cd build  
	cmake ..  
	make -j 8  
