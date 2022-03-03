#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// int main(int argc, char** argv){
//     Mat img, img_resized, img_hsv;
//     img = imread("index.jpeg");
//     resize(img, img_resized, Size(), 2, 2);
//     cvtColor(img_resized, img_hsv, COLOR_BGR2HSV);
//     Point titik = Point (1,1);
//     circle(img_resized,titik,50,Scalar(0,0,255), -1);
//     imshow("gambar", img_resized);
//     waitKey(0);
//     return 0;
// }

int main(int argc, char **argv)
{
    VideoCapture vid("ball.mp4");
    Mat frame, thresh, frame_resize, frame_hsv;
    int L_H = 0;
    int U_H = 68;
    int L_S = 9;
    int U_S = 246;
    int L_V = 241;
    int U_V = 255;
    namedWindow("threshold", WINDOW_AUTOSIZE);
    createTrackbar("L_H", "threshold", &L_H, 179);
    createTrackbar("U_H", "threshold", &U_H, 179);
    createTrackbar("L_S", "threshold", &L_S, 255);
    createTrackbar("U_S", "threshold", &U_S, 255);
    createTrackbar("L_V", "threshold", &L_V, 255);
    createTrackbar("U_V", "threshold", &U_V, 255);

    while (true)
    {
        vid.read(frame);
        resize(frame, frame_resize, Size(), 0.5, 0.5);
        cvtColor(frame_resize, frame_hsv, COLOR_BGR2HSV);

        inRange(frame_hsv, Scalar(L_H, L_S, L_V), Scalar(U_H, U_S, U_V), thresh);

        vector<vector<Point>> contours;
        findContours(thresh, contours, RETR_TREE, CHAIN_APPROX_NONE);

        for (int i = 0; i < contours.size(); i++)
        {
            vector<Point> contours_new;
            Point2f center;
            float radius;
            contours_new = contours[i];
            minEnclosingCircle(contours_new, center, radius);

            if (radius > 30 && radius < 78)
            {
                circle(frame_resize, center, radius, Scalar(255, 0, 0), 3);
                printf("x: %2f y: %2f rad: %f\n\n", center.x, center.y, radius);
            }
        }
        imshow("IniVideo", frame_resize);
        imshow("IniTresh", thresh);

        if ((char)27 == (char)waitKey(150))
            break;
    }
    return 0;
}