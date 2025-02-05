#include <opencv2/opencv.hpp>
#include <iostream>
#include <string_view>
constexpr std::string_view names[] = {"Genius","Good","average",};//just for fun I know  it's bad though ;)
std::string getName()
{
    return std::string(names[rand() % names->size()]);
};

int main()
{
    srand(time(nullptr));
    cv::CascadeClassifier face_cascade;
    std::vector<std::string>name;
    // Load the Haar cascade file for face detection
    if (!face_cascade.load("./res/haarcascade_frontalface_default.xml"))
    {
        std::cerr << "Error loading face cascade!\n";
        return -1;
    }

    // Open the default camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Error opening webcam!\n";
        return -1;
    }
    cv::namedWindow("Display", cv::WINDOW_NORMAL);

    cv::Mat frame;
    while (cap.read(frame))
    {
        std::vector<cv::Rect> faces;
        cv::Mat gray;

        // Convert to grayscale
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        // Detect faces
        face_cascade.detectMultiScale(gray, faces, 1.1, 4, cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
        if(faces.size()>name.size())
        {
            while(faces.size()>name.size())
            name.push_back(std::string(names[rand()%sizeof(names)/sizeof(names[0])]));
        };
        // Draw rectangles around detected faces
        for (int i = 0; i < faces.size(); ++i)
        {
            cv::rectangle(frame, faces[i], cv::Scalar(255, 0, 0), 2);
            cv::putText(frame,name[i], cv::Point(faces[i].x, faces[i].y - 10),
                        cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 0), 2);
        }

        // Show the output
        cv::imshow("Display", frame);
        if (cv::waitKey(10) == 27)
        { // Exit on pressing 'ESC'
            break;
        }
    }

    return 0;
}
