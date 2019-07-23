# MachineLearningProject
~~~~
                           changement de sujet le 31/03/2019

nous travaillons à présent sur une Application permettant de différencier les drapeaux de pays différents (France et USA)
~~~~

# Pour lancer le projet (suivre ces étapes)

## Requirements

- Linux (created and tested on Linux)
- Python3
- Node.js (tested with v12.5.0) & npm (tested with v6.9.0)
- g++ (if you need to re-compile C++ sources)
- opencv-python (pip3 install opencv-python)

## Change paths in file CLibrary.py in CLibrary folder :

	- PROJECT_PATH variable at line 11 
	put your own path pointing to CLibrary folder :
	Example : PROJECT_PATH = "/home/user/MachineLearningProject/CLibrary/"
	
	- List of path at line 398
	Put your own pathto point to TrainRBF/USA and TrainRBF/FR
	XTrain, YTrain = create_train_mat(["/home/user/MachineLearningProject/TrainRBF/FR", "/home/user/MachineLearningProject/TrainRBF/USA"], 5)

## Go into WebAPI folder :
	- type "npm install" to install the dependencies of the server
	- then type "node index.js"
	- Server is now launched and ready, go to http://localhost:3000/app to use the app !

/!\ A noter : parfois le première requète pose problème, il faut alors 
cliquer sur "Clear and upload a new image" et re-upload l'image tout
fonctionnera comme il faut par la suite !

Ilès BENKOUSSA

Arnauld BIAM

Victor MEYER
