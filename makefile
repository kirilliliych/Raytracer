all:
	@g++ image.cpp sphere.cpp vector3d.cpp color.cpp utilities.cpp displaywindow.cpp camera.cpp ray.cpp main.cpp -o raytracing -lsfml-system -lsfml-window -lsfml-graphics 
	./raytracing
