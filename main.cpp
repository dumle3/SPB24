#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>    //��� exit(int);

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    system("CHCP 1251");

    char mainWindow[] = "Main";
    char trackbarWindow[] = "Trackbar";
    int thr = 150, thrmax = 255,
        bl = 21, blmax = 22;
    VideoCapture cap;
    Mat frame, blurred, grayscale, binthreshold;

    /*�������� ����*/
    namedWindow(mainWindow, 0);
    namedWindow(trackbarWindow, 0);

    createTrackbar("Gray threshold: ", trackbarWindow, &thr, thrmax);
    createTrackbar("Preparation-blur intensity: ", trackbarWindow, &bl, blmax);

    /*������ ������*/
    cap.open(0);
    if (!cap.isOpened()) {
        std::cout << "������ �� ����� ���� �������" << std::endl;
        exit(1);
    }

    while (1) {
        cap >> frame;
        cvtColor(frame, grayscale, COLOR_BGR2GRAY);
        threshold(grayscale, binthreshold, thr, 255, THRESH_BINARY);
        medianBlur(binthreshold, blurred, bl);
        
        /*����� ��������*/
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(blurred, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

        /*��������� ��������*/
        Mat copy = frame.clone();
        drawContours(copy, contours, -1, Scalar(255, 0, 0), 2);
        
        /*����� �����������*/
        imshow(mainWindow, copy);
        if (waitKey(10) == 27)
            break;
    }
    return 0;
}