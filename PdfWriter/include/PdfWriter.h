#pragma once
#include <Image.h>
#include <filesystem>
#include <hpdf.h>

/**
 * @brief Default error handler
 *
 * @param error_no
 * @param detail_no
 * @param user_data
 */
void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no,
                   void *user_data);

/**
 * @class PdfWriter
 * @brief A PDF writer that writes images
 *
 */
class PdfWriter {
private:
  HPDF_Doc document;
  HPDF_Font font;
  double width, height, outline;

  HPDF_Page createPage();

public:
  /**
   * @brief Creates a PDF writer
   *
   * @param width of the page in pixels
   * @param height of the page in pixels
   */
  PdfWriter(double width, double height, double outline);
  ~PdfWriter();

  /**
   * @brief Gets the width of a page
   *
   * @return The width
   */
  double getWidth() const;
  /**
   * @brief Gets the height of a page
   *
   * @return The height
   */
  double getHeight() const;
  /**
   * @brief Writes an image to a new page
   *
   * @param image The raw image data
   */
  void addImage(const ImageData &image);
  /**
   * @brief Writes text to a new page
   *
   * @param text The text to write
   */
  void writeText(const std::string &text);
  /**
   * @brief Saves the PDF
   *
   * @param path The path to save to
   */
  void save(const std::filesystem::path &path) const;
};
