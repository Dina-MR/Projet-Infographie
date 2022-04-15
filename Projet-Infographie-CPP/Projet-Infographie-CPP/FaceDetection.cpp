#include "FaceDetection.h"

using namespace std;
using namespace cv;

String CASCADE_PATH = "../../XML/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;

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
    Mat edited_frame = frame.clone();

    // Traitements sur l'image
    cvtColor(edited_frame, frame_gray, COLOR_BGR2GRAY);
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
    ellipse(edited_frame, center, Size(rx, ry), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

    cout << "Détection faciale terminée ! Affichage des résultats...\n";

    // Affichage
    imshow("Projet infographie", edited_frame);
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
