
#include <chrono>
#include <cstdio>
#include <thread>

#include "ntcore.h"

#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

void setup_camera(VideoCapture *camera)
{
    bool ret;
    ret = camera->set(CV_CAP_PROP_FRAME_WIDTH,  320); printf("CV_CAP_PROP_FRAME_WIDTH   = %d\n", ret);
    ret = camera->set(CV_CAP_PROP_FRAME_HEIGHT, 240); printf("CV_CAP_PROP_FRAME_HEIGHT  = %d\n", ret);
    
}
void print_camera_prop(VideoCapture *camera)
{
    double ret;
    // ret = camera->get(CV_CAP_PROP_POS_MSEC      ); printf("CV_CAP_PROP_POS_MSEC      = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_POS_FRAMES    ); printf("CV_CAP_PROP_POS_FRAMES    = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_POS_AVI_RATIO ); printf("CV_CAP_PROP_POS_AVI_RATIO = %f\n", ret);
    ret = camera->get(CV_CAP_PROP_FRAME_WIDTH   ); printf("CV_CAP_PROP_FRAME_WIDTH   = %f\n", ret);
    ret = camera->get(CV_CAP_PROP_FRAME_HEIGHT  ); printf("CV_CAP_PROP_FRAME_HEIGHT  = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_FPS           ); printf("CV_CAP_PROP_FPS           = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_FOURCC        ); printf("CV_CAP_PROP_FOURCC        = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_FRAME_COUNT   ); printf("CV_CAP_PROP_FRAME_COUNT   = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_FORMAT        ); printf("CV_CAP_PROP_FORMAT        = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_MODE          ); printf("CV_CAP_PROP_MODE          = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_BRIGHTNESS    ); printf("CV_CAP_PROP_BRIGHTNESS    = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_CONTRAST      ); printf("CV_CAP_PROP_CONTRAST      = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_SATURATION    ); printf("CV_CAP_PROP_SATURATION    = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_HUE           ); printf("CV_CAP_PROP_HUE           = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_GAIN          ); printf("CV_CAP_PROP_GAIN          = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_EXPOSURE      ); printf("CV_CAP_PROP_EXPOSURE      = %f\n", ret);
    // ret = camera->get(CV_CAP_PROP_CONVERT_RGB   ); printf("CV_CAP_PROP_CONVERT_RGB   = %f\n", ret);
}

int main( int argc, char* argv[])
{

    // nt::SetLogger(
    //               [](unsigned int level, const char* file, unsigned int line,
    //                  const char* msg) {
    //                   std::fputs(msg, stderr);
    //                   std::fputc('\n', stderr);
    //               },
    //               0);
    if (argc != 4) {
        printf("my-grip <network table ip> <port> <camera dev (0,1...)>\n");
        exit(1);
    }
    char * ip = argv[1];
    int port = (int)strtol(argv[2], NULL, 10);
    int camera_dev = (int)strtol(argv[3], NULL, 10);
    printf("network table server ip = %s  port = %d camera dev = %d\n", ip, port, camera_dev);


    VideoCapture camera(camera_dev);
    if (!camera.isOpened()) {
        printf("can not open camera %d\n", camera_dev);
        exit(-1);
    }
    print_camera_prop(&camera);
    // setup_camera(&camera);
    // print_camera_prop(&camera);
    unsigned long int cnt = 0;

    Mat frame;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    int levels = 3;

    nt::StartClient(ip, port);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // auto foo = nt::GetEntryValue("/foo");
    // if (foo && foo->IsDouble()) printf("Got foo: %g\n", foo->GetDouble());
    // nt::SetEntryValue("/bar", nt::Value::MakeBoolean(false));
    // nt::SetEntryFlags("/bar", NT_PERSISTENT);
    // nt::SetEntryValue("/bar2", nt::Value::MakeBoolean(true));
    // nt::SetEntryValue("/bar2", nt::Value::MakeBoolean(false));
    // nt::SetEntryValue("/bar2", nt::Value::MakeBoolean(true));

    for(;;)
        {
            cnt++;
            vector<vector<Point> > contours0;
            camera >> frame;
            Mat img;
            cv::cvtColor(frame, img, CV_RGB2GRAY);
            // printf("row=%d col = %d %d\n", frame.rows, frame.cols, frame.empty());
            Mat bw = img > 250;

            imshow("bw", bw);
            contours.resize(0);
            // findContours(bw, contours0, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
            findContours(bw, contours0, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS);
            int contour_cnt = 0;
            if (cnt % 30 == 0) {
                printf("cnt= %ld\n", cnt);
            }
            std::vector<double> value_area;
            std::vector<double> value_centerX;
            std::vector<double> value_centerY;

            for( size_t k = 0; k < contours0.size(); k++ ) {
                double area  = contourArea(contours0[k]);
                if (area > 500) {
                    Rect bb = boundingRect(contours0[k]);
                    double centerX = bb.x + bb.width / 2;
                    double centerY = bb.y + bb.height / 2;
                    contours.resize(contour_cnt + 1); 
                    value_area.resize(contour_cnt + 1);
                    value_centerX.resize(contour_cnt + 1);
                    value_centerY.resize(contour_cnt + 1);
                    printf("area[%d] = %f center-X = %f  center-Y = %f\n", k, area, centerX, centerY);
                    value_area[contour_cnt] = area;
                    value_centerX[contour_cnt] = centerX;
                    value_centerY[contour_cnt] = centerY;
                    // approxPolyDP(Mat(contours0[k]), contours[contour_cnt], 3, true);
                    contour_cnt++;
                };
            }
            nt::SetEntryValue("/grip/area", nt::Value::MakeDoubleArray(value_area));
            nt::SetEntryValue("/grip/centerX", nt::Value::MakeDoubleArray(value_centerX));
            nt::SetEntryValue("/grip/centerY", nt::Value::MakeDoubleArray(value_centerY));
            // printf("\tcontours.size() = %d\n", contours.size());
            int _levels = levels - 3;
            Mat source = frame.clone();
            drawContours(source, contours, -1, Scalar(255,0,0),
                         3, CV_AA, hierarchy, std::abs(_levels) );

            imshow("camera", source);
            
            if( cvWaitKey(10) >= 0 )
                break;
        }
    return 0;
    std::this_thread::sleep_for(std::chrono::seconds(10));
}
