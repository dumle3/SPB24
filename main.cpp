#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>                      //для exit(int);

using namespace cv;

int main(int argc, char **argv)
{
    system("CHCP 1251");

    char mainWindow[] = "Main";
    char trackbarWindow[] = "Trackbar";
    char thresholdWindow[] = "Threshold";

    int BlurSize = 21,
        min = 0, max = 1000, Max = 1000,
        h = 0, dh = 0, smin = 0, vmin = 0,
        hmax = 255, smax = 255, vmax = 255;

    VideoCapture cap;
    Mat frame, HSV, threshold, blurred;

    /*Создание окон*/
    namedWindow(mainWindow, 0);
    namedWindow(trackbarWindow, 0);
    namedWindow(thresholdWindow, 0);

    /*Создание ползунков для определения границ искомых на картинке значений*/
    createTrackbar("H: ", trackbarWindow, &h, hmax);
    createTrackbar("dH: ", trackbarWindow, &dh, hmax);
    createTrackbar("S min: ", trackbarWindow, &smin, smax);
    createTrackbar("S max: ", trackbarWindow, &smax, smax);
    createTrackbar("V min: ", trackbarWindow, &vmin, vmax);
    createTrackbar("V max: ", trackbarWindow, &vmax, vmax);
    createTrackbar("Size min: ", trackbarWindow, &min, max);
    createTrackbar("Size max: ", trackbarWindow, &max, max);



    cap.open(0);
    if (!cap.isOpened()) {
        std::cout << "Камера не может быть открыта" << std::endl;
        exit(1);
    }

    //moveWindow("First OpenCV Application", 0, 45);
    while (1) {
        cap >> frame;
        cvtColor(frame, HSV, COLOR_BGR2HSV);
        medianBlur(HSV, blurred, BlurSize);
        inRange(blurred, Scalar(h-dh, smin, vmin), Scalar(h+dh, smax, vmax), threshold);

        for (int y=0; y<threshold.rows; y++)
            for (int x = 0; x < threshold.cols; x++) {
                int value = threshold.at<uchar>(y, x);
                if (value == 255) {
                    Rect rect;
                    int count = floodFill(threshold, Point(x, y), Scalar(200), &rect);
                    if (rect.width >= min && rect.width <= max && rect.height >= min && rect.height <= max)
                        rectangle(frame, rect, Scalar(255, 0, 255, 4));
                }
            }

        imshow(mainWindow, frame);
        imshow(thresholdWindow, threshold);
        if (waitKey(10) == 27)
            break;
    }
    return 0;
}