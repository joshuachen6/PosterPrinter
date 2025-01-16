#include "PdfWriter.h"
#include <hpdf.h>
#include <hpdf_consts.h>
#include <hpdf_types.h>
#include <spdlog/spdlog.h>

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no,
                   void *user_data) {
  spdlog::error("[PDF] error_no={:4x}, detail_no={}", (unsigned int)error_no,
                (int)detail_no);
}

HPDF_Page PdfWriter::createPage() {
  HPDF_Page page = HPDF_AddPage(document);
  HPDF_Page_SetWidth(page, getWidth());
  HPDF_Page_SetHeight(page, getHeight());
  return page;
}

double PdfWriter::getWidth() const { return width; }

double PdfWriter::getHeight() const { return height; }

PdfWriter::PdfWriter(double width, double height, double outline) {
  document = HPDF_New(error_handler, nullptr);
  font = HPDF_GetFont(document, "Times-Roman", nullptr);
  this->outline = outline;
  this->width = width;
  this->height = height;
}

PdfWriter::~PdfWriter() { HPDF_Free(document); }

void PdfWriter::addImage(const ImageData &data) {
  HPDF_Page page = createPage();
  // The width of the dash

  HPDF_Image image =
      HPDF_LoadPngImageFromMem(document, data.data(), data.size());
  HPDF_Page_DrawImage(page, image, outline / 2, outline / 2,
                      HPDF_Image_GetWidth(image), HPDF_Image_GetHeight(image));

  // Define the dash
  HPDF_UINT16 dash[]{3};

  // Fold line
  HPDF_Page_SetLineWidth(page, outline);
  HPDF_Page_SetDash(page, dash, 1, 1);
  HPDF_Page_Rectangle(page, 0, 0, getWidth(), getHeight());
  HPDF_Page_Stroke(page);
}

void PdfWriter::writeText(const std::string &text) {
  HPDF_Page page = createPage();

  HPDF_Page_SetFontAndSize(page, font, 42);
  HPDF_Page_BeginText(page);
  HPDF_Page_TextOut(page, getWidth() / 4, getHeight() / 4, text.c_str());
  HPDF_Page_EndText(page);
}

void PdfWriter::save(const std::filesystem::path &path) const {
  HPDF_SaveToFile(document, path.c_str());
}
