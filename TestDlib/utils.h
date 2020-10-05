#ifndef UTILS_H
#define UTILS_H

#include <dlib/opencv.h>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <ctime>


void draw_polyline(cv::Mat &img, const dlib::full_object_detection& d, const int start, const int end, bool isClosed = false)
{
    std::vector <cv::Point> points;
    for (int i = start; i <= end; ++i)
    {
        points.push_back(cv::Point(d.part(i).x(), d.part(i).y()));
    }
    cv::polylines(img, points, isClosed, cv::Scalar(255,0,0), 2, 16);
}


void render_face (cv::Mat &img, const dlib::full_object_detection& d)
{
    DLIB_CASSERT
    (
     d.num_parts() == 68,
     "\n\t Invalid inputs were given to this function. "
     << "\n\t d.num_parts():  " << d.num_parts()
     );

    draw_polyline(img, d, 0, 16);           // Jaw line
    draw_polyline(img, d, 17, 21);          // Left eyebrow
    draw_polyline(img, d, 22, 26);          // Right eyebrow
    draw_polyline(img, d, 27, 30);          // Nose bridge
    draw_polyline(img, d, 30, 35, true);    // Lower nose
    draw_polyline(img, d, 36, 41, true);    // Left eye
    draw_polyline(img, d, 42, 47, true);    // Right Eye
    draw_polyline(img, d, 48, 59, true);    // Outer lip
    draw_polyline(img, d, 60, 67, true);    // Inner lip

}


std::vector<std::string> getdir (std::string dir) {
    std::vector<std::string> files;
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return files;
    }

    while ((dirp = readdir(dp)) != NULL) {
    std::string name  = dirp->d_name;
    if (name[0] != '.') {
            files.push_back(std::string(dirp->d_name));
    }
    }
    closedir(dp);
    return files;
}

struct TimeMeasurer {
    std::string info_;
    clock_t begin_;
    TimeMeasurer(std::string info):info_(info) {
        begin_ = clock();
    }
    ~TimeMeasurer() {
         clock_t end = clock();
         double elapsed_secs = double(end - begin_) / CLOCKS_PER_SEC;
         std::cout << info_ << elapsed_secs <<std::endl;
    }
};

#endif // UTILS_H
