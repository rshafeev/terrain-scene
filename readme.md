###Description###

### Control keys ###
* keyboard arrows - moving in terrain (if you do not change height).
* Home/End - increase/decrease height.
* F1 - exit full screen mode
* F2 - return to full-screen mode 

###Possible problems###
* If you get the next error: "fatal error LNK1281: Не удается создать образ SAFESEH." we recommend that you do the following: Open project properties/Linker/Additional/(set NO:SAFESEH.)
* If we run project and get "can not find glew32.dll", copy glew32.dll and glut32.dll libraries to folder "Release[or Debug]"