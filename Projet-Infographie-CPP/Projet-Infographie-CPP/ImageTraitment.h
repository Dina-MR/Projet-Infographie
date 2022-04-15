#pragma once
#ifndef IMAGE_TRAITMENT	
#define IMAGE_TRAITMENT		

#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
using namespace cv;

// Valeurs extrêmes du kernel
extern int KERNEL_MIN;
extern int KERNEL_MAX;

// Types de floutage
enum Mode {Normal, Gaussien, Median, Bilateral};

// Fonctions

// Affichage en chaine de caractères du mode de floutage
const String ModeToString(Mode mode);

// Floutage d'une image
Mat blurImage(Mat image, int kernel = 1, Mode mode = Normal);

// Floutage de plusieurs images, sous un même mode et un même kernel
vector<Mat> blurredImagesByModeAndKernel(vector<Mat> images, int kernel = 1, Mode mode = Normal);

// Floutage d'un ensemble d'images, sous un même mode et différents kernels
vector<vector<Mat>> blurredImagesPerKernel(vector<Mat> images, Mode mode = Normal);

#endif
