#include <opencv2/opencv.hpp>
#include <iostream>
#include <string_view>
#include <ADTconfig.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <filesystem>
namespace fs = std::filesystem;
constexpr std::string_view names[] = {
    "Genius",
    "Good",
    "average",
}; // just for fun I know  it's bad though ;)
fs::path cascadePath()
{
    fs::path _path = getenv("USERPROFILE");
    _path = _path / "face_data" / "res";
    if (fs::exists(_path))
    {
        fmt::print(fmt::emphasis::faint,"{} exists\n", (_path / "haarcascade_frontalface_default.xml").string());
    }
    else
    {
        try
        {

            fmt::print("{} doesn't exist!\n", (_path / "haarcascade_frontalface_default.xml").string());
            if (fs::create_directories(_path))
            {
                fmt::print("{} created\n", _path.string());
                fs::path _source = fs::current_path() / "res" / "haarcascade_frontalface_default.xml";
                fs::path _destination = _path / "haarcascade_frontalface_default.xml";
                if (fs::copy_file(_source, _destination))
                {
                    fmt::print("{} copied to {}\n", "res/haarcascade_frontalface_default.xml", _path.string() + "/haarcascade_frontalface_default.xml");
                }
                else
                {
                    fmt::print("{} doesn't exist! make sure you have {} before running this application\n", "res/haarcascade_frontalface_default.xml", "res/haarcascade_frontalface_default.xml");
                }
            }
            else
                fmt::print("failed to create {}\n", _path.string());
            fmt::print("setup completed rerun the app\n");
        }
        catch (std::exception &e)
        {
            fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::crimson), "Error : {}\n", e.what());
            exit(0);
        };
    };
    _path = _path / "haarcascade_frontalface_default.xml";

    return _path;
}
int main()
{
    fmt::print(fmt::fg(fmt::color::light_green), "OpenCV Static Build\nv{}.{}.{}\n{}\n", ADT_VERSION_MAJOR, ADT_VERSION_MINOR, ADT_VERSION_PATCH, ADT_COPYRIGHT);
    srand(time(nullptr));
    cv::CascadeClassifier face_cascade;
    std::vector<std::string> name;
    // Load the Haar cascade file for face detection
    if (!face_cascade.load(cascadePath().string()))
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
        if (faces.size() > name.size())
        {
            while (faces.size() > name.size())
                name.push_back(std::string(names[rand() % sizeof(names) / sizeof(names[0])]));
        };
        // Draw rectangles around detected faces
        for (int i = 0; i < faces.size(); ++i)
        {
            cv::rectangle(frame, faces[i], cv::Scalar(255, 0, 0), 2);
            cv::putText(frame, name[i], cv::Point(faces[i].x, faces[i].y - 10),
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
