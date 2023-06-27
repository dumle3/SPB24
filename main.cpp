#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>                      //для exit(int);

using namespace cv;

int main(int argc, char **argv)
{
    system("CHCP 1251");

    char mainWindow[] = "Main";
    char trackbarWindow[] = "Trackbar";
    int thrmin = 0, thrmax = 255;
    VideoCapture cap;
    Mat frame, grayscale, binthreshold;

    /*Создание окон*/
    namedWindow(mainWindow, 0);
    namedWindow(trackbarWindow, 0);

    createTrackbar("Gray threshold: ", trackbarWindow, &thrmin, thrmax);

    /*Запуск камеры*/
    cap.open(0);
    if (!cap.isOpened()) {
        std::cout << "Камера не может быть открыта" << std::endl;
        exit(1);
    }

    while (1) {
        cap >> frame;
        cvtColor(frame, grayscale, COLOR_BGR2GRAY);
        threshold(grayscale, binthreshold, thrmin, 255, THRESH_BINARY);
        //findContours(grayscale,)
        imshow(mainWindow, binthreshold);
        if (waitKey(10) == 27)
            break;
    }
    return 0;
}