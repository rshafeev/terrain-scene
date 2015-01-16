###Description###
3D scene was generated using opengl libraries and shaders. In the scene there are a terrain, a pyramid and lake.

#See demonstration video:#
 [![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/PcpdO9eGPrI/0.jpg)](https://www.youtube.com/watch?v=PcpdO9eGPrI)

### Control keys ###
* keyboard arrows - moving around terrain (if you do not change height).
* Home/End - increase/decrease height.
* F1 - exit full screen mode
* F2 - return to full-screen mode 
* Esc - exit

###Possible problems###
* If you get the next error: "fatal error LNK1281: .... SAFESEH." we recommend that you do the following: Open project properties/Linker/Additional/(set NO:SAFESEH.)
* If we run project and get "can not find glew32.dll", copy glew32.dll and glut32.dll libraries to folder "Release[or Debug]"