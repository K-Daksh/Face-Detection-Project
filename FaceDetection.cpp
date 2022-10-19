#include<opencv2/core.hpp>
#include<opencv2/face.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/objdetect.hpp>
#include <time.h>
#include <iostream>
#include<string>
#include <fstream>
#include <sstream>

using namespace cv::face;
using namespace cv;

using namespace std;

static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    switch (src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(Error::StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if (!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}


void main(int argc, char** argv) {
    Mat img;
    VideoCapture real_time(0);
    String Path = "Resources/haarcascade_frontalface_default.xml";
    string fn_csv = string(argv[1]);
    CascadeClassifier faceClass;
    faceClass.load(Path);
    vector<Mat> images;
    vector<int> labels;

    try {
        read_csv(fn_csv, images, labels);
    }
    catch (const cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }

    if (faceClass.empty()) {
        cout << "XML File not loaded." << endl;
    }

    if (images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(Error::StsError, error_message);
    }
    int height = images[0].rows;
    Mat testSample = images[images.size() - 1];
    int testLabel = labels[labels.size() - 1];
    images.pop_back();
    labels.pop_back();
    Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
    model->train(images, labels);
    vector<Rect> faces;

    while (true) {
        faceClass.detectMultiScale(img, faces, 1.1, 10, CASCADE_SCALE_IMAGE, Size(55, 55));
        real_time.read(img);
        for (int i = 0; i < faces.size(); i++) {
            Mat faceROI = img(faces[i]);
            rectangle(img, faces[i], Scalar(0, 255, 0), 2);
            rectangle(img, Point(10, 10), Point(50, 50), Scalar(0, 0, 0), FILLED);
            putText(img, to_string(faces.size()), Point(22, 40), FONT_ITALIC, 1, Scalar(255, 0, 255), 2);
        }

        imshow("Web Output", img);
        //waitKey(1);
        if (waitKey(10) == 27) {
            break;
        }

    }
}
