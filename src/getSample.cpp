//
// Created by hu on 2019/5/20.
//

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

void detectcircleHOF(Mat frame);

void savePicture(Mat frame, string path, string name);

string windows_name = "real-time show";

RNG rng(12345);

int main(int argc, char **argv) {
    srand((int) time(NULL));

    VideoCapture capture;
    Mat frame;
    capture.open("2.avi"); // Read recorded video

    while (capture.read(frame)) {
        if (frame.empty()) {
            printf("Load frame error!");
            break;
        }
        detectcircleHOF(frame);
        char c = (char) waitKey(10);
        if (c == 27) {
            break;
        }
    }
}


//保存图片
void savePicture(Mat frame, string path, string name) {
    /*
     * Save samples to specified path with specified name
     */
    int count;
    string num;

    ifstream readFile;
    readFile.open(path + "/"+name+"-config.txt");
    readFile >> count;
    num = to_string(count++);
    readFile.close();

    string finalPath;
    finalPath = path + "/" + name + num + ".bmp";
    imwrite(finalPath, frame);

    ofstream writeFile;
    writeFile.open(path + "/"+name+"-config.txt", ios::trunc);
    writeFile << count;
    writeFile.close();
}

/*
 * Because of the shape of the robots
 * we can firstly detect circle and get a raw data
 * then delete the noisy picture by hand
 */
void detectcircleHOF(Mat frame) {
    srand((int) time(NULL));
    Mat frame_grey;
    cvtColor(frame, frame_grey, COLOR_BGR2GRAY);
    medianBlur(frame_grey, frame_grey, 5);
    vector<Vec3f> circles;
    HoughCircles(frame_grey, circles, HOUGH_GRADIENT, 1,
                 frame_grey.rows / 16, // change this value to detect circles with different distances to each other
                 100, 30, 1, 30 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    int minx = 0;
    for (size_t i = 0; i < circles.size(); i++) {


        Vec3i c = circles[i];
        circle(frame, Point(c[0], c[1]), c[2], Scalar(0, 0, 255), 3, LINE_AA);
        circle(frame, Point(c[0], c[1]), 2, Scalar(0, 255, 0), 3, LINE_AA);
        //获取正样本

        if (((c[0] + c[2]) < frame.cols) && ((c[1] + c[2]) < frame.rows))
        {
            Mat cut(frame_grey, Rect((c[0] - c[2]) >= 0 ? (c[0] - c[2]) : 0, (c[1] - c[2]) >= 0 ? (c[1] - c[2]) : 0, 2 * c[2], 2 * c[2]));
            savePicture(cut,"./circle/pos","pos")

        }

        if (c[0] <= circles[minx][0]) {
            minx = i;
        }
    }

    if (circles.size()) {
        Vec3i c = circles[minx];
        if ((c[0] - c[2]) > 50 && (c[1] - c[2]) > 50) {
            Mat cut(frame_grey, Rect(0, 0, c[0] - c[2], c[1] - c[2]));

            savePicture(cut, "./circle/neg", "neg");

        }
    }
    imshow(windows_name, frame);
}