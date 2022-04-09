#include "FaceDetection.h"

using namespace std;
using namespace cv;

String CASCADE_PATH = "../../XML/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;

//string window_name = "Face detection";
//RNG rng(12345);

/*int main(int argc, const char** argv)
{
    //read an image
    Mat img = imread("/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/multiple.jpg");
    //read the video
    String video_single = "/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/video_one.mp4";
    String video_multiple = "/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/video_multiple.mp4";


    //-- 1. Load the cascades
    if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading 1st cascade\n"); return -1; };
    if (!face_and_eyes_cascade.load(face_and_eyes_cascade_name)) { printf("--(!)Error loading 2nd cascade\n"); return -1; };

    //-- 2. Apply the classifier to the image

    // Question 1
    //detectAndDisplay(img, face_cascade);

    // Question 2
    //detectAndDisplayMulti(img, face_cascade);

    // Question 3A
    VideoCapture caption1(video_single);
    if (!caption1.isOpened())
    {
        cout << "Unable to open the one face video \n";
        exit(-1);
    }
    //detectAndDisplayVideo(caption1, 1, face_cascade);

    // Question 3B
    VideoCapture caption2(video_multiple);
    if (!caption1.isOpened())
    {
        cout << "Unable to open the one face video \n";
        exit(-1);
    }
    //detectAndDisplayVideo(caption2, 0, face_cascade);

    // Question 4
    detectAndDisplayVideo(caption1, 2, face_and_eyes_cascade);

    waitKey(0);


    return 0;
}*/

// Chargement de la cascade
int loadCascade()
{
    cout << "Chargement du fichier cascade en cours ...\n";

    if (!face_cascade.load(CASCADE_PATH))
    {
        printf(" -- /!\ Erreur : la cascade n'a pas pu être chargée ! -- \n");
        return -1;
    };

    cout << "Chargement du fichier cascade terminé ! \n";
    return 0;
}

// Détection d'un visage dans une image
void detectOneFace(Mat frame)
{
    cout << "Détection faciale en cours...\n";

    // Variables
    std::vector<Rect> faces;
    Mat frame_gray;

    // Traitements sur l'image
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Détection
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Mesures
    int cx = faces[0].x + faces[0].width * 0.5;
    int cy = faces[0].y + faces[0].height * 0.5;
    int rx = faces[0].width * 0.5;
    int ry = faces[0].height * 0.5;
    
    // Création du cercle de détection faciale
    Point center(cx, cy);
    ellipse(frame, center, Size(rx, ry), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

    cout << "Détection faciale terminée ! Affichage des résultats...\n";

    // Affichage
    imshow("Projet infographie", frame);
}

// Détection de visage sur plusieurs images
int detectOneFaceMultiPic(vector<Mat> images)
{
    loadCascade();
    for (Mat image : images)
    {
        if (image.empty())
        {
            cout << "-- Erreur : l'image n'a pas pu etre chargée --\n";
            return -1;
        }
        detectOneFace(image);
        waitKey(0);
    }
}

/*
// Détection de plusieurs visages dans une image
void detectAndDisplayMulti(Mat frame, CascadeClassifier cascade)
{
    std::vector<Rect> faces;

    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    for (int i = 0; i < faces.size(); i++)
    {
        int cx = faces[i].x + faces[i].width * 0.5;
        int cy = faces[i].y + faces[i].height * 0.5;

        int rx = faces[i].width * 0.5;
        int ry = faces[i].height * 0.5;

        Point center(cx, cy);

        ellipse(frame, center, Size(rx, ry), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
    }

    //-- Show what you got
    imshow(window_name, frame);
}

// Détection de plusieurs visages dans une vidéo
void detectAndDisplayVideo(VideoCapture caption, int indicator, CascadeClassifier cascade)
{
    Mat frame;

    while (true)
    {
        caption >> frame;
        if (frame.empty()) break;
        // 0 : multiple faces, 1 : one face
        switch (indicator)
        {
        case 0:
            detectAndDisplayMulti(frame, cascade);
            break;

        case 2:
            detectAndDisplayEyes(frame);
            break;

        default:
            detectAndDisplay(frame, cascade);
            break;
        }
        //imshow("Vidéo", frame);
        if (waitKey(1) == 27) break;
    }
}

// Détection des yeux
void detectAndDisplayEyes(Mat frame)
{
    std::vector<Rect> eyes;
    std::vector<Rect> faces;

    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    int cx = faces[0].x + faces[0].width * 0.5;
    int cy = faces[0].y + faces[0].height * 0.5;

    int rx = faces[0].width * 0.5;
    int ry = faces[0].height * 0.5;

    Point center(cx, cy);

    ellipse(frame, center, Size(rx, ry), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);


    //-- Detect eyes
    face_and_eyes_cascade.detectMultiScale(frame_gray, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    for (int i = 0; i < eyes.size(); i++)
    {
        int cx = eyes[i].x + eyes[i].width * 0.5;
        int cy = eyes[i].y + eyes[i].height * 0.5;

        int rx = eyes[i].width * 0.5;
        int ry = eyes[i].height * 0.5;

        Point center(cx, cy);

        ellipse(frame, center, Size(rx, ry), 0, 0, 360, Scalar(0, 195, 255), 4, 8, 0);
    }

    //-- Show what you got
    imshow(window_name, frame);
}*/
