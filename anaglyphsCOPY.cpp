// Use this command to compile
// g++ anaglyphsCOPY.cpp -fopenmp `pkg-config opencv4 --cflags` -c
// g++ anaglyphsCOPY.o  -fopenmp `pkg-config opencv4 --libs` -lstdc++ -o anaglyphsCOPY

// Use this to run the code 
// ./anaglyphsCOPY "True Anaglyph"
// ./anaglyphsCOPY "Gray Anaglyph"
// ./anaglyphsCOPY "Color Anaglyph"
// ./anaglyphsCOPY "Half Anaglyph"
// ./anaglyphsCOPY "Optimized Anaglyph"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

// #define M_PI         3.14159265358979323846

cv::Mat createAnaglyph(double left_matrix[3][3], double right_matrix[3][3], cv::Mat rgb_image) {

    // Split the input image into left and right stereo images
    cv::Mat left_image = rgb_image(cv::Rect(0, 0, rgb_image.cols/2, rgb_image.rows));
    cv::Mat right_image = rgb_image(cv::Rect(rgb_image.cols/2, 0, rgb_image.cols/2, rgb_image.rows));

    cv::Mat anaglyph_image(left_image.size(), left_image.type());

    // Iterate over the pixels of the input image
    auto begin = chrono::high_resolution_clock::now();
    const int iter = 100;
    for (int it=0;it<iter;it++){
        #pragma omp parallel for
        for (int i = 0; i < left_image.rows; i++) {
            for (int j = 0; j < left_image.cols; j++) {
                // Compute the anaglyph pixel values
                cv::Vec3b pixel_left = left_image.at<cv::Vec3b>(i, j);
                cv::Vec3b pixel_right = right_image.at<cv::Vec3b>(i, j);

                double r = pixel_left[2], r2 = pixel_right[2];
                double g = pixel_left[1], g2 = pixel_right[1];
                double b = pixel_left[0], b2 = pixel_right[0];
                double anaglyph_r = left_matrix[0][0]*r + left_matrix[0][1]*g + left_matrix[0][2]*b +
                                    right_matrix[0][0]*r2 + right_matrix[0][1]*g2 + right_matrix[0][2]*b2;
                double anaglyph_g = left_matrix[1][0]*r + left_matrix[1][1]*g + left_matrix[1][2]*b +
                                    right_matrix[1][0]*r2 + right_matrix[1][1]*g2 + right_matrix[1][2]*b2;
                double anaglyph_b = left_matrix[2][0]*r + left_matrix[2][1]*g + left_matrix[2][2]*b +
                                    right_matrix[2][0]*r2 + right_matrix[2][1]*g2 + right_matrix[2][2]*b2;

                cv::Vec3b anaglyph_pixel(
                    cv::saturate_cast<uchar>(anaglyph_b),
                    cv::saturate_cast<uchar>(anaglyph_g),
                    cv::saturate_cast<uchar>(anaglyph_r)
                );

                anaglyph_image.at<cv::Vec3b>(i, j) = anaglyph_pixel;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - begin;

    cout << "Total time: " << diff.count() << " s" << endl;
    cout << "Time for 1 iteration: " << diff.count() / iter << " s" << endl;
    cout << "IPS: " << iter / diff.count() << endl;
    return anaglyph_image;
}

int main(int argc, char* argv[])
{
    // Check if the anaglyph type was provided as a command line argument
   
      if (argc < 2) {
        cout << "Error: Please provide a parameter." << endl;
        cout << argc;
        cout << argv[1];
        return 1;
    }
    // Retrieve the parameter
    string anaglyph_type = argv[1];
    // Load the stereo image
    Mat stereo_image = imread("stereo_image.jpg");

    double left_matrix[3][3] = {0};
    double right_matrix[3][3] = {0};
    
    cout << anaglyph_type;
    if (anaglyph_type == "True Anaglyph") {
        // True Anaglyph
        left_matrix[0][0] = 0.299; left_matrix[0][1] = 0.587; left_matrix[0][2] = 0.114;
        right_matrix[2][0] = 0.299; right_matrix[2][1] = 0.587; right_matrix[2][2] = 0.114;
    } 
    else if (anaglyph_type == "Gray Anaglyph") {
        // Gray Anaglyph
        left_matrix[0][0] = 0.299; left_matrix[0][1] = 0.587; left_matrix[0][2] = 0.114;
        right_matrix[1][0] = 0.299; right_matrix[1][1] = 0.587; right_matrix[1][2] = 0.114;
        right_matrix[2][0] = 0.299; right_matrix[2][1] = 0.587; right_matrix[2][2] = 0.114;
    } 
    else if (anaglyph_type == "Color Anaglyph") {
        // Color Anaglyph
        left_matrix[0][0] = 1; 
        right_matrix[1][1] = 1;
        right_matrix[2][2] = 1;
    } 
    else if (anaglyph_type == "Half Anaglyph") {
        // Half Anaglyph 
        left_matrix[0][0] = 0.299; left_matrix[0][1] = 0.587; left_matrix[0][2] = 0.114;
        right_matrix[1][1] = 1;
        right_matrix[2][2] = 1;
    } 
      else if (anaglyph_type == "Optimized Anaglyph") {
        // Optimized Anaglyph 
        left_matrix[0][1] = 0.7; left_matrix[0][2] = 0.3;
        right_matrix[1][1] = 1;
        right_matrix[2][2] = 1;
    }
    // Create the anaglyph image
    Mat anaglyph_image = createAnaglyph(left_matrix, right_matrix, stereo_image);

    // Display the anaglyph image
    imshow("Anaglyph Image", anaglyph_image);
    waitKey(0);

    return 0;
}
