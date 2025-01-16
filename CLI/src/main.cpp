#include <ImageSplitter.h>
#include <PdfWriter.h>
#include <format>
#include <iostream>
#include <print>
#include <spdlog/spdlog.h>

int main() {
  // Set the log level
  spdlog::set_level(spdlog::level::debug);

  // Get the image
  std::string inFile;
  std::print("Input Image: ");
  std::cin >> inFile;

  // Set the margins
  int margin;
  std::print("Margin: ");
  std::cin >> margin;

  // Get the size
  std::map<std::string, std::pair<double, double>> pageSizes{
      {"Letter", {612, 792}},     {"Legal", {612, 1008}},
      {"A3", {841.89, 1199.551}}, {"A4", {595.276, 841.89}},
      {"A5", {419.528, 595.276}}, {"B4", {708.661, 1000.63}},
      {"B5", {498.898, 708.661}}, {"Executive", {522, 756}},
      {"US4x6", {288, 432}},      {"US4x8", {288, 576}},
      {"US5x7", {360, 504}},      {"Comm10", {297, 684}}};

  std::string sizeName;
  std::println("Page Sizes");
  for (const std::pair<std::string, std::pair<double, double>> &size :
       pageSizes) {
    std::println("-{}", size.first);
  }
  std::print("Select a Page Size: ");
  std::cin >> sizeName;
  const std::pair<double, double> &size = pageSizes[sizeName];

  // Set the outline width
  double outlineWidth = 2;

  // Make the writer
  PdfWriter writer(size.first, size.second, outlineWidth);

  // Split the image
  ImageSplitter splitter;
  SplitterOptions options{
      static_cast<int>(writer.getWidth() - margin * 2 - outlineWidth),
      static_cast<int>(writer.getHeight() - margin * 2 - outlineWidth)};

  SplitterOutput output = splitter.splitImage(inFile, options);

  // Write to PDF
  for (int row = 0; row < output.rows; row++) {
    for (int col = 0; col < output.columns; col++) {
      writer.addImage(output.images[row * output.columns + col]);
      writer.writeText(
          std::format("Row: {}, Col: {}", row + 1, output.columns - col));
    }
  }

  // Save the PDF
  std::string outFile;
  std::print("Output PDF: ");
  std::cin >> outFile;
  writer.save(outFile);
}
