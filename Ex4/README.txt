Quelques petites instructions pour bien faire fonctionner le programme

Normalement, tout devrait bien �tre configurer et marcher
S'il y a des probl�mes avec Magick++ (ImageMagick)
suivre ce tutoriel : https://fortunomedia.com/magick-plus-plus-config-vs2010/
R�sum� du tutoriel : 
	- changer le build du projet de "debug" � "release"
	- ajouter les "includes"
	- ajouter les "lib"
	- ajouter les "d�pendances" :
		CORE_RL_magick_.lib
		CORE_RL_Magick++_.lib
		CORE_RL_wand_.lib

Les includes et lib se trouve dans : 8INF840-TP2\Ex4\ImageMagick-7.0.8-Q16

En lancant le main, on vous demande le PATH des images � charger et le PATH de o� sauvegarder votre image.
Vous pouvez utiliser n'importe quel PATH / image.
Cependant, une s�rie d'image de test est disponible ici : 8INF840-TP2\Ex4\Images
Pour acc�der � l'image : 8INF840-TP2\Ex4\Images\soleil.png
tapez dans la console : Images\\soleil.png ou le PATH complet.

IMPORTANT: quand vous entrez un PATH, mettez des \\
ex : D:\\Repositories\\8INF840-TP2\\Ex4\\Images\\soleil.png
Il est possible qu'il y est des probl�mes s'il y a des espaces dans le PATH (non test�, cela peut donc marcher comme crasher)