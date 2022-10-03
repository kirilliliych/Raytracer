all:
	@g++ image.cpp sphere.cpp drawable.cpp pixel3d.cpp lightsource.cpp vector3d.cpp color.cpp objsys.cpp objsysarr.cpp utilities.cpp displaywindow.cpp main.cpp -o raytracing -lsfml-system -lsfml-window -lsfml-graphics 
	./raytracing
