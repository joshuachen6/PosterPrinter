#include "ImageSplitter.h"
#include "opencv2/core.hpp"
#include "opencv2/core/base.hpp"
#include <opencv2/imgcodecs.hpp>
#include <spdlog/spdlog.h>

SplitterOutput ImageSplitter::splitImage(const std::filesystem::path &path,
                                         const SplitterOptions &options) const {
  // Check to see if the file exists
  if (std::filesystem::exists(path)) {
    // Open the image
    cv::Mat image = cv::imread(path);

    spdlog::debug("[Image] Input Width: {}, Height: {}", image.cols,
                  image.rows);

    // Check to see if the image sizes are set to (-1)
    int width = options.maxWidth < 0 ? image.cols : options.maxWidth;
    int height = options.maxHeight < 0 ? image.rows : options.maxHeight;

    spdlog::debug("[Image] Output Width: {}, Height: {}", width, height);

    // Calculate the number of rows and columns needed
    int rows = std::ceil(static_cast<float>(image.rows) / height);
    int columns = std::ceil(static_cast<float>(image.cols) / width);

    // Pad the image
    cv::copyMakeBorder(image, image, 0, rows * height - image.rows, 0,
                       columns * width - image.cols, cv::BORDER_CONSTANT,
                       {255, 255, 255});

    spdlog::debug("[Image] Resized to (cols: {}, rows: {})", image.cols,
                  image.rows);
    spdlog::debug("[Image] Columns: {}, Rows: {}", columns, rows);

    // Create the output
    SplitterOutput output{std::vector<ImageData>(rows * columns), rows,
                          columns};

    // Loop and create the sub-images
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < columns; col++) {
        // Calculates the region of interest
        int left = col * width;
        int bottom = row * height;
        cv::Rect roi = {left, bottom, width, height};

        // Create the sub-region
        spdlog::debug(
            "[Image] Extracting (x: {}, y: {}, width: {}, height: {})", left,
            bottom, width, height);
        cv::Mat region{image, roi};

        // Encode and store the data
        cv::imencode(".png", region, output.images[row * columns + col]);
        region.data = nullptr;
      }
    }

    return output;
  }
  throw std::runtime_error("Failed to open file");
}
