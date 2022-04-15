// Projet-Infographie-CPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "FaceDetection.h"
#include "ImageTraitment.h"
#include "FaceRecognition.h"

using namespace cv;
using namespace std;

int main()
{
	String image_test = "../../dataset/images/mb4.jpg";

	vector<Mat> images = vector<Mat>();
	images.push_back(imread(image_test));
	
	//1. leacture du base 
	string data_file = string("../../dataset/csv/mb.csv");

	//2. training
	Ptr<FaceRecognizer> model = EigenFaceRecognizer::create();

	model = training(data_file);

	//3.test
	Mat test = imread("../../dataset/images/18_2.jpg", IMREAD_GRAYSCALE);

	testImageSample(model, test);
	imshow("image avec flou", test);
	waitKey(0);
	
	return 0;
}