#pragma once
#include <Image.h>
#include <filesystem>
#include <opencv2/core/hal/interface.h>

/**
 * @class SplitterOutput
 * @brief Stores the output of the image split
 *
 */
struct SplitterOutput {
  /**
   * @brief The image data in row major
   */
  std::vector<ImageData> images;
  /**
   * @brief The number or rows
   */
  int rows;
  /**
   * @brief The number of columns
   */
  int columns;
};

/**
 * @class SplitterOptions
 * @brief Options for splitting an image
 *
 */
struct SplitterOptions {
  /**
   * @brief The max width in pixels of an image (-1 makes it infinite)
   */
  int maxWidth = -1;
  /**
   * @brief the max height in pixels of an image (-1 makes it inifinite)
   */
  int maxHeight = -1;
};

/**
 * @class ImageSplitter
 * @brief Splits images into multiple Image instances
 *
 */
struct ImageSplitter {
  /**
   * @brief Splits the image
   *
   * @param path The path to the image
   * @param options The options for splitting the image
   */
  SplitterOutput splitImage(const std::filesystem::path &path,
                            const SplitterOptions &options = {}) const;
};
