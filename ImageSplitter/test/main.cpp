#include <ImageSplitter.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <print>
#include <spdlog/spdlog.h>

int main() {
  // Set the log level
  spdlog::set_level(spdlog::level::debug);

  // Get the path from the user
  std::string path;
  std::print("Image Path: ");
  std::cin >> path;

  // Create the splitter options
  SplitterOptions options;

  // Get the dimensions
  std::print("Width (pixels): ");
  std::cin >> options.maxWidth;
  std::print("Height (pixels): ");
  std::cin >> options.maxHeight;

  // Create the image splitter
  ImageSplitter splitter;

  SplitterOutput output = splitter.splitImage(path, options);

  // Create the image buffer
  cv::Mat image;

  // Create the window
  std::string windowName = "Splitter Output";
  cv::namedWindow(windowName);

  for (int row = 0; row < output.rows; row++) {
    for (int col = 0; col < output.columns; col++) {
      // Decode the image into the buffer
      cv::imdecode(output.images[row * output.columns + col],
                   cv::IMREAD_UNCHANGED, &image);

      // Show the image
      cv::imshow(windowName, image);
      cv::waitKey(0);
    }
  }

  return 0;
}
