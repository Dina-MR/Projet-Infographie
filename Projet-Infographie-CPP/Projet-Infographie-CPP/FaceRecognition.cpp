#include "FaceRecognition.h"
#include "FaceDetection.h"
#include "ImageTraitment.h"

// Fonction de lecture du fichier csv. Source : "https://docs.opencv.org/2.4/modules/contrib/doc/facerec/facerec_tutorial.html"
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        //CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if (!path.empty() && !classlabel.empty()) {
            images.push_back(blurImage(imread(path, 0), KERNEL_MAX - 10));
            //images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

Ptr<FaceRecognizer> training(string data_file) {
    //1. leacture du base 
    vector<Mat> images;
    vector<int> labels;

    try {
        read_csv(data_file, images, labels);
    }
    catch (cv::Exception& e) {
        cerr << "Error opening file \"" << data_file << "\". Reason: " << e.msg << endl;
        exit(1);
    }


    //2. train
    Ptr<FaceRecognizer> model = EigenFaceRecognizer::create();
    try {
        model->train(images, labels);
    }
    catch (const Exception& exc) {
        cout << "**************************************   ERREUE  *********************************  TRAIN ****************************************************************";
        cerr << exc.what();
    }

    return model;
}

void testImageSample(Ptr<FaceRecognizer> model, Mat test) {
    try {
        //int predictedLabel = model->predict(test);
        int predicted_label = -1;
        double predicted_confidence = 50.5;
        model->predict(test, predicted_label, predicted_confidence);
        string result_message = format("######################Predicted class = %d ", predicted_label);
        cout << result_message << endl;

    }
    catch (const Exception& exc) {
        cout << "**************************************   ERREUE   **** PREDICt";
        cerr << exc.what();
    }
}


void testImagesVector(Ptr<FaceRecognizer> model, vector<Mat> imgs) {
    for (Mat img : imgs) {
        testImageSample(model, img);
    }

}

void testImageVideo(Ptr<FaceRecognizer> model, VideoCapture cap) {
    if (!cap.isOpened()) {
        std::cout << "Unable to open the camera\n";
        std::exit(-1);
    }
    Mat img;
    while (true) {
        cap >> img;
        testImageSample(model, img);
    }
}
