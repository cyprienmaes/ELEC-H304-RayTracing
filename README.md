# ELEC-H304-RayTracing
Le projet fonctionne sur Windows.
Attention malgre tout ! Si le projet doit etre recompilé, il faut installer codeblocks avec mingw : http://www.codeblocks.org/downloads/26.
Ensuite il faut installer SDL de la meme maniere que dans ce tutoriel : https://openclassrooms.com/courses/apprenez-a-programmer-en-c/installation-de-la-sdl
Et pour finir, il faut installer SDL_ttf de la manière suivante :
-Aller sur le site d'installation et télécharger SDL_ttf pour SDL1.2 (Ne pas se tromper) : https://www.libsdl.org/projects/SDL_ttf/release-1.2.html
-Telecharger le fichier win32.zip et VC.zip
-Aller dans votre dossier CodeBlocks\MinGW\mingw32 et rajouter un dossier \include\SDL
-Ouvrer le win32.zip et Rajouter le .h dans le dossier susmentionne
-Aller dans votre dosser CodeBlocks\MinGW\mingw32\lib
-Ouvrer le VC.zip et Rajouter SDL_ttf dans le dossier susmentionne
Les fichiers DLL sont deja mis dans le projet.


