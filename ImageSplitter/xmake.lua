add_requires("opencv", "spdlog")
set_languages("c++23")

target("ImageSplitter")
set_kind("static")
add_files("src/**.cpp")
add_includedirs("include", { public = true })
add_deps("Image")
add_packages("opencv", "spdlog", { public = true })

target("ImageSplitterTest")
set_kind("binary")
add_files("test/**.cpp")
add_deps("Image", "ImageSplitter")
