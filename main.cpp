#include "opencv2/opencv.hpp"
#include<unistd.h>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;
    Mat prev, current, diff;
    int nz;
    cap >> prev;
    sleep(15);
    cap >> prev;
    cvtColor(prev, prev, CV_BGR2GRAY);
    for(;;) {
        cap >> current;
        cvtColor(current, current, CV_BGR2GRAY);
        string t = to_string(time(0));
        absdiff(prev, current, diff);
        blur(diff, diff, Size(5, 5));
        threshold(diff, diff, 10, 255, THRESH_BINARY_INV);
        nz = countNonZero(diff);
        if(nz < 297000) {
            cap >> current;
            imwrite(t + ".jpg", current);
            VideoWriter vw(t + ".wmv", CV_FOURCC('M','J','P','G'), 5, Size(640, 480));
            for(int i=0;i<50;i++) {
                vw.write(current);
                usleep(200000);
                cap >> current;
            }
            cvtColor(current, current, CV_BGR2GRAY);
        }
        sleep(3);
        prev = current;
    }
    return 0;
}
