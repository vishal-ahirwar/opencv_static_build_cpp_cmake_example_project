#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::CascadeClassifier face_cascade;

    // Load the Haar cascade file for face detection
    if (!face_cascade.load("./res/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade!\n";
        return -1;
    }

    // Open the default camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening webcam!\n";
        return -1;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        std::vector<cv::Rect> faces;
        cv::Mat gray;

        // Convert to grayscale
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        // Detect faces
        face_cascade.detectMultiScale(gray, faces, 1.1, 4, cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        // Draw rectangles around detected faces
        for (const auto &face : faces) {
            cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
        }

        // Show the output
        cv::imshow("Face Detection", frame);
        if (cv::waitKey(10) == 27) {  // Exit on pressing 'ESC'
            break;
        }
    }

    return 0;
}
