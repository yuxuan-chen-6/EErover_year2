#include <opencv2/opencv.hpp>
#include <iostream>

std::vector<int> detect_road(cv::Mat image) {
    // Convert the image to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Apply Canny edge detection
    cv::Mat edges;
    cv::Canny(gray, edges, 50, 150, 3, false);

    // Apply probabilistic Hough line transform
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edges, lines, 1, CV_PI / 230, 20, 3, 12);

    // Initialize flags for presence of strips on each side
    bool is_strip_left = false;
    bool is_strip_right = false;
    bool is_strip_front = false;
    bool is_double_strip = false;

    for (size_t i = 0; i < lines.size(); i++) {
        cv::Vec4i line = lines[i];
        int x1 = line[0], y1 = line[1], x2 = line[2], y2 = line[3];

        // Calculate slope of the line
        float slope = (float)(y2 - y1) / (x2 - x1);

        // Check if the line starts from the bottom of the image
        if (y1 > image.rows-3 || y2 > image.rows-3){
            // Check if the slope indicates a vertical line
            if (abs(slope) > 1) {
                if (!is_double_strip) {
                    is_double_strip = true;
                }
                else {
                    return {0, 1, 0};
                }
            }
        }
        else {
            if (std::abs(slope) < 1) {
                // Check if the line is on the left
                if (slope < 0 && x1 < image.cols / 2 && x2 < image.cols / 2) {
                    is_strip_left = true;
                }
                // Check if the line is on the right
                else if (slope > 0 && x1 > image.cols / 2 && x2 > image.cols / 2) {
                    is_strip_right = true;
                }
                else if (x1 < image.cols / 2 && x2 > image.cols / 2) {
                    is_strip_right = true;
                    is_strip_left = true;
                }
            }
            else if (std::abs(slope) > 1 && y2 < image.rows / 2){
                is_strip_front = true;
            }
        }
    }

    // Decision-making logic
    std::vector<int> directions(3, 0);
    if (is_strip_front) {
        directions[1] = 1;
    }
    if (is_strip_left) {
        directions[0] = 1;
    }
    if (is_strip_right) {
        directions[2] = 1;
    }

    return directions;
}

int main() {
    cv::Mat image = cv::imread("./test10.jpeg");
    
    if (image.empty()) {
        printf("Failed to load image\n");
        return -1;
    }

    std::vector<int> result = detect_road(image);

    std::cout << "Result: ";
    for (const auto& dir : result) {
        std::cout << dir << " ";
    }
    std::cout << std::endl;

    return 0;
}
