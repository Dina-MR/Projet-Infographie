#include "ImageTraitment.h"

using namespace std;
using namespace cv;

vector<Mat> blurredImages(vector<Mat> images)
{
	vector<Mat> blurredImages = vector<Mat>();
	for (Mat image : images)
	{
		Mat blurredImage = image.clone();
		blur(image, blurredImage, image.size);
		blurredImages.push_back();
	}
}