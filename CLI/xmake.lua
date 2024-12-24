add_requires("opencv", "libharu", "spdlog")

set_languages("c++23")
target("CLI")
set_kind("binary")
add_includedirs("include")
add_files("src/**.cpp")
add_packages("opencv", "libharu", "spdlog")
add_deps("Image", "ImageSplitter", "PdfWriter")