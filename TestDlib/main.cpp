#define DLIB_JPEG_SUPPORT
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/image_io.h>
#include <tuple>
#include <dlib/svm.h>
#include <dlib/gui_widgets.h>
#include <dlib/array2d.h>
#include <dlib/image_transforms.h>
#include "utils.h"
#include <assert.h>

std::string get_next_img_name(){
    static int i = 0;
    std::string s = "img/" + std::to_string(++i) + ".jpg";
    return s;
}

void create_faces_db(){
    cv::VideoCapture cap;
    if(!cap.open(0))
        std::cout << "error" << std::endl;
    for(;;)
    {
        cv::Mat frame;
        cap >> frame;
        if( frame.empty() ) break;

        cv::imshow("this is you, smile! :)", frame);
        int waitKey = cv::waitKey(1);
        if( waitKey == 27 ) break;
        if ((waitKey & 255) == 's' ) {
            cv::imwrite(get_next_img_name(), frame);
            std::cout << "save!";
        }
    }
}



using DlibImage = dlib::matrix<double>;
using DlibImages = std::vector<DlibImage>;
using DlibFaceParams = std::vector<dlib::full_object_detection>;
using FacesAndParams = std::tuple<DlibImages, DlibFaceParams>;

auto load_faces_db(std::string path) {
    auto result = std::make_tuple(DlibImages(), DlibFaceParams());
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();

    dlib::shape_predictor pose_model;
    dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
    DlibImages& images = std::get<0>(result);
    DlibFaceParams& face_params = std::get<1>(result);
    auto files  = getdir(path);
    for(auto& file: files) {
        DlibImage img;
        dlib::load_image(img, path + file);
        std::vector<dlib::rectangle> faces = detector(img);
        if (faces.size() == 1) {
            auto p = pose_model(img, faces.front());
            face_params.push_back(p);
            images.push_back(std::move(img));
        }
    }
    return result;
}

void train(FacesAndParams&& faces_with_params) {

}

// Here is the sinc function we will be trying to learn with the one-class SVMs
double sinc(double x)
{
    if (x == 0)
        return 2;
    return 2*sin(x)/x;
}

auto GetFace() {
    cv::VideoCapture cap;
    if(!cap.open(0))
        std::cout << "error" << std::endl;
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
    dlib::shape_predictor pose_model;
    dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
    for(;;)
    {
        cv::Mat frame;
        cap >> frame;
        if( frame.empty() ) break;

        cv::imshow("this is you, smile! :)", frame);
        int waitKey = cv::waitKey(1);
        if( waitKey == 27 ) {
            dlib::cv_image<dlib::bgr_pixel> cimg(frame);
            std::vector<dlib::rectangle> faces = detector(cimg);
            if (faces.size() == 1) {
                auto p = pose_model(cimg, faces.front());
                std::cout << "OK!";
                return std::make_tuple(frame, p);
            }
        }
    }
}

static cv::Rect dlibRectangleToOpenCV(dlib::rectangle r)
{
  return cv::Rect(cv::Point2i(r.left(), r.top()), cv::Point2i(r.right() + 1, r.bottom() + 1));
}

void GetFaveAndVectorOfDetails(cv::Mat& face1, std::vector<cv::Point2f>& face_details1)
{
    dlib::full_object_detection detect1;
    std::tie(face1, detect1) = GetFace();
    for (int i = 0; i < detect1.num_parts(); ++i) {
        dlib::point p = detect1.part(i);
        face_details1.push_back(cv::Point2f(p(0), p(1)));
    }
    std::cout << face_details1.size() << std::endl;
}



dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
dlib::shape_predictor pose_model;

auto DetectOneFace(cv::Mat frame) {
    std::vector<cv::Point2f> face_details;
    dlib::cv_image<dlib::bgr_pixel> cimg(frame);
    std::vector<dlib::rectangle> faces;
    faces = detector(cimg);
    if (faces.size() != 1) {
        return std::make_tuple(cv::Rect(), std::vector<cv::Point2f>());
    }
    dlib::rectangle r = faces.front();
    dlib::full_object_detection detection;
        detection = pose_model(cimg, r);
    for (int i = 0; i < detection.num_parts(); ++i) {
        dlib::point p = detection.part(i);
        face_details.push_back(cv::Point2f(p(0), p(1)));
    }
    cv::Rect face_rect(r.left(),r.top(),r.width(),r.height());
    return std::make_tuple(face_rect, face_details);
}


auto FrontalLandmarks() {
    cv::Mat frontal_face = cv::imread("average-woman-face.jpg");
    cv::Rect roi_face;
    std::vector<cv::Point2f> landmarks;
    std::tie(roi_face, landmarks) = DetectOneFace(frontal_face);
    cv::rectangle(frontal_face, roi_face, cv::Scalar(0,255,255));
    for (auto p: landmarks) {
        cv::circle(frontal_face,p, 5,cv::Scalar(0,255,1),4);
    }
    cv::imshow("Hi", frontal_face);
    cv::waitKey(0);
    std::cout << "End" << std::endl;
    return landmarks;
}

int main(int argc, char *argv[]) {
    dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
    cv::Mat frontal_face = cv::imread("average-woman-face.jpg");
    cv::Rect frontal_roi;
    std::vector<cv::Point2f> frontal_landmarks;
    std::tie(frontal_roi, frontal_landmarks) = DetectOneFace(frontal_face);

    cv::VideoCapture cap;
    if(!cap.open(0))
        std::cout << "error" << std::endl;
    for(;;)
    {
        cv::Mat frame;
        cap >> frame;
        int waitKey = cv::waitKey(1);
        if( frame.empty()  || waitKey == 27 ) {
            break;
        }

        cv::Rect roi;
        std::vector<cv::Point2f> landmarks;
        std::tie(roi, landmarks) = DetectOneFace(frame);
        if(landmarks.size() ==0 ) {
            continue;
        }
        cv::Mat homo_matrix = cv::findHomography(frontal_landmarks, landmarks);
        cv::Mat changed_frontal;
        cv::warpPerspective(frontal_face, changed_frontal, homo_matrix,frontal_face.size());

        cv::rectangle(frame, roi, cv::Scalar(0,255,255));
        for (auto p: landmarks) {
            cv::circle(frame,p, 5,cv::Scalar(0,255,1),4);
        }

        cv::imshow("this is you, smile! :)", frame);
        cv::imshow("Changed_frontal", changed_frontal);
    }
//    cv::Mat face1;
//    std::vector<cv::Point2f> face_details1;
//    GetFaveAndVectorOfDetails(face1, face_details1);
////    for(auto p: face_details1) {
////        cv::circle(face1,p, 5,cv::Scalar(0,255,1),4);
////    }
////    cv::imshow("Face1", face1);

//    cv::Mat face2;
//    std::vector<cv::Point2f> face_details2;
//    GetFaveAndVectorOfDetails(face2, face_details2);
////    for(auto p: face_details2) {
////        cv::circle(face2,p, 5,cv::Scalar(0,255,1),4);
////    }
////    cv::imshow("Face2", face2);
//    cv::Mat homo_matrix = cv::findHomography(face_details1, face_details2);
//    std::cout << homo_matrix << std::endl;
////    cv::rectangle(face1, dlibRectangleToOpenCV(detect1.get_rect()), cv::Scalar(100,0,0));
////    cv::imshow("Face1", face1);

////    cv::Mat face2;
////    dlib::full_object_detection detect2;
////    std::tie(face2, detect2) = GetFace();
////    cv::rectangle(face2, dlibRectangleToOpenCV(detect2.get_rect()), cv::Scalar(100,0,0));

////    cv::imshow("Face2", face2);
//    cv::warpPerspective(face1, face1, homo_matrix,face1.size());
//    cv::imshow("Trasnformed", face1);
//    cv::waitKey(0);

////    create_faces_db();
//    DlibImages images;
//    DlibFaceParams faces_params;

//    std::tie(images, faces_params) = std::move(load_faces_db("./img/"));

//    std::cout << images.size() << std::endl;
//    std::transform(images.begin(), images.end(), faces_params.begin(), images.begin(),
//                   [](auto& image, auto& face_params) {
//            auto c_details = dlib::get_face_chip_details(face_params);
//            DlibImage face;
//            dlib::extract_image_chip(image, c_details, face);
////            dlib::image_window my_window(face, "Normal Edge Image");
////            my_window-.wait_until_closed();
//            return std::move(face);
//    });

//    typedef DlibImage SampleType;
//    typedef dlib::radial_basis_kernel<SampleType> KernelType;
//    dlib::svm_one_class_trainer<KernelType> trainer;
//    trainer.set_kernel(KernelType(4.0));
//    std::vector<SampleType> test;
//    std::cout << images.size() << std::endl;
//    for (auto& image: images) {
//        test.push_back(image);
//    }
//    std::cout << test.size() << std::endl;

//    dlib::decision_function<KernelType> df = trainer.train(test);
//    std::cout << "Trained" << std::endl;
    return 0;
}
