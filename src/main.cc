#include<opencv2/opencv.hpp>
#include<opencv2/core/cuda.hpp>
int main() {
    cv::VideoCapture cap(0); // Open the default camera (ID 0)
    
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera!" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame; // Capture a new frame

        if (frame.empty()) break; // Stop if no frame is captured

        cv::imshow("Webcam", frame); // Display the frame

        if (cv::waitKey(1) == 27) break; // Press 'ESC' to exit
    }

    cap.release(); // Release the camera
    cv::destroyAllWindows(); // Close all OpenCV windows
    return 0;
}
