//
// Created by hu on 2019/5/20.
//
#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>

using namespace cv;
using namespace std;

void detCircleCas(Mat frame);

string circle_name = "../trained_xml/robot/LBP.xml";//使用的分类器名字

CascadeClassifier circle_cas;//检测机器人使用的分类器

string windows_name = "real-time show";

RNG rng(12345);

int main(int argc, char **argv) {
    srand((int) time(NULL));
    VideoCapture capture;
    Mat frame;
    capture.open("2.avi");

    circle_cas.load(circle_name);

    while (capture.read(frame)) {

        if (frame.empty()) {
            printf("Load frame error!");
            break;
        }
        detCircleCas(frame);
        char c = (char) waitKey(10);
        if (c == 27) {
            break;
        }
    }
}



//使用级联分类器识别机器人
void detCircleCas(Mat frame) {
    std::vector<Rect> circles;
    Mat frame_grey;
    cvtColor(frame, frame_grey, COLOR_BGR2GRAY);//转成灰度图像
    //检测机器人
    circle_cas.detectMultiScale(frame_grey, circles, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    //对每个检测到的机器人
    for (size_t i = 0; i < circles.size(); i++) {
        //中心点
        Point center(circles[i].x + circles[i].width / 2, circles[i].y + circles[i].height / 2);
        //画圈
        circle(frame, center, circles[i].width / 2, Scalar(0, 255, 0), 3, LINE_AA);
        if (((circles[i].x + 30) < frame.cols) && (circles[i].y + 30) < frame.rows) {
            Mat cut(frame_grey, circles[i]);
            medianBlur(cut, cut, 5);
        }


    }
    imshow(windows_name, frame);
}


