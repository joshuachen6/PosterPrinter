target("Image")
set_kind("static")
add_includedirs("include", { public = true })
add_files("src/**.cpp")
