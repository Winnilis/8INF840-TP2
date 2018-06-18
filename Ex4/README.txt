Quelques petites instructions pour bien faire fonctionner le programme

Normalement, tout devrait bien être configurer et marcher
S'il y a des problèmes avec Magick++ (ImageMagick)
suivre ce tutoriel : https://fortunomedia.com/magick-plus-plus-config-vs2010/
Résumé du tutoriel : 
	- changer le build du projet de "debug" à "release"
	- ajouter les "includes"
	- ajouter les "lib"
	- ajouter les "dépendances" :
		CORE_RL_magick_.lib
		CORE_RL_Magick++_.lib
		CORE_RL_wand_.lib

Les includes et lib se trouve dans : 8INF840-TP2\Ex4\ImageMagick-7.0.8-Q16

En lancant le main, on vous demande le PATH des images à charger et le PATH de où sauvegarder votre image.
Vous pouvez utiliser n'importe quel PATH / image.
Cependant, une série d'image de test est disponible ici : 8INF840-TP2\Ex4\Images
Pour accèder à l'image : 8INF840-TP2\Ex4\Images\soleil.png
tapez dans la console : Images\\soleil.png ou le PATH complet.

IMPORTANT: quand vous entrez un PATH, mettez des \\
ex : D:\\Repositories\\8INF840-TP2\\Ex4\\Images\\soleil.png
Il est possible qu'il y est des problèmes s'il y a des espaces dans le PATH (non testé, cela peut donc marcher comme crasher)