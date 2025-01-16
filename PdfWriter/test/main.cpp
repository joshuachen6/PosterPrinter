#include "PdfWriter.h"
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <print>

int main() {
  // Load the image
  std::string filename;
  std::print("Filename: ");
  std::cin >> filename;
  cv::Mat image = cv::imread(filename);

  // Convert the image into the right format
  ImageData data;
  cv::imencode(".png", image, data);

  // Create the writer and write an image and some text
  PdfWriter writer(100, 100, 2);
  writer.addImage(data);
  writer.writeText("Hello");

  // Save the file
  std::print("Save to: ");
  std::cin >> filename;
  writer.save(filename);
}
