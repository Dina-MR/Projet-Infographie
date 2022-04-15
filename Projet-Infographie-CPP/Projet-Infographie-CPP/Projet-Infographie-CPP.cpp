// Projet-Infographie-CPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "FaceDetection.h"
#include "ImageTraitment.h"

using namespace cv;
using namespace std;

int main()
{
	String image_test = "../../dataset/images/mb1.png";
	Mat blurTest;

	vector<Mat> images = vector<Mat>();
	images.push_back(imread(image_test));
	detectOneFaceMultiPic(images);
	// test du flou
	blurTest = blurImage(images[0]);
	imshow("Test flou", blurTest);
	waitKey();
	// test des différents niveaux de kernel
	vector<vector<Mat>> imagesList = vector<vector<Mat>>();
	imagesList = blurredImagesPerKernel(images, Bilateral);
	for (vector<Mat> imgVec : imagesList)
	{
		for (Mat img : imgVec)
		{
			imshow("Test de flou avec variation de paramètres", img);
			waitKey();
		}
	}
	// test des modes de flou
	/*vector<vector<Mat>> modeNormal = vector<vector<Mat>>();
	vector<vector<Mat>> modeGaussien = vector<vector<Mat>>();
	vector<vector<Mat>> modeMedian = vector<vector<Mat>>();
	vector<vector<Mat>> modeBilateral = vector<vector<Mat>>();*/

	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
