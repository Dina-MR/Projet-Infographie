#include "ImageTraitment.h"

using namespace std;
using namespace cv;

int KERNEL_MIN = 1;
int KERNEL_MAX = 21;

// Affichage en chaine de caractères du mode de floutage
const String ModeToString(Mode mode) throw()
{
	switch (mode)
	{
		case Normal: return "Normal";
		case Gaussien: return "Gaussien";
		case Median: return "Median";
		case Bilateral: return "Bilateral";
		default: throw invalid_argument("Mode inconnu");
	}
}

// Floutage d'une image
Mat blurImage(Mat image, int kernel, Mode mode)
{
	Mat blurredImage = image.clone();
	try {
		switch (mode)
		{
			case Gaussien:
				GaussianBlur(image, blurredImage, Size(kernel, kernel), 0, 0);
				break;
			case Median:
				medianBlur(image, blurredImage, kernel);
				break;
			case Bilateral:
				bilateralFilter(image, blurredImage, kernel, 1, 1);
				break;
			default:
				blur(image, blurredImage, Size(kernel, kernel), Point(-1, -1));
		}
		return blurredImage;

	}
	catch (const exception & e) {
		cout << e.what();
	}
}

// Floutage de plusieurs images, sous un même mode et un même kernel
vector<Mat> blurredImagesByModeAndKernel(vector<Mat> images, int kernel, Mode mode)
{
	cout << "Floutage des images en cours ... \n";
	cout << "Valeur du kernel : " << kernel << ".\n";

	vector<Mat> blurredImages = vector<Mat>();
	for (Mat image : images)
	{
		blurredImages.push_back(blurImage(image, kernel, mode));
	}
	return blurredImages;
}

// Floutage d'un ensemble d'images, sous un même mode et différents kernels
vector<vector<Mat>> blurredImagesPerKernel(vector<Mat> images, Mode mode)
{
	cout << "Floutage des images selon différents niveaux de kernel en cours ... \n";
	cout << "Mode choisi : " << ModeToString(mode) << ".\n";

	vector<vector<Mat>> blurredImagesList = vector<vector<Mat>>();
	for (int i = KERNEL_MIN; i <= KERNEL_MAX; i = i + 2)
	{
		blurredImagesList.push_back(blurredImagesByModeAndKernel(images, i, mode));
	}

	cout << "Floutage terminé ! \n";
	return blurredImagesList;
}