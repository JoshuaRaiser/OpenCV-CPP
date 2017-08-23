## OpenCV

Windows - Visual Studio

http://docs.opencv.org/2.4/doc/tutorials/introduction/windows_install/windows_install.html

- opencv-v3.2.0-vc14

Release x64

 Project > Properties > C/C++ > General > Additional Include Directories:
◦$(OPENCV_DIR)\..\..\include

 Project > Properties > Linker > General > Additional Library Directories:
◦$(OPENCV_DIR)\lib

 Project > Properties > Linker > Input > Additional Dependencies:
◦opencv_world320.lib

 Project > Properties > C/C++ > Preprocessor > Preprocessor Definitions:
◦_CRT_SECURE_NO_WARNINGS

- Erro identificado na execução

![](erro-opencv_world320.dll.PNG)

-> mova "opencv\build\x64\vc14\bin\opencv_world320.dll" para "opencv-v3.2.0-vc14-app\x64\Release"

