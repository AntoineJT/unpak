set_project("xtractpak")
set_version("0.0.0")

add_rules("mode.debug", "mode.release")
set_languages("cxx17")

if is_mode("release") then
    set_optimize("fastest")
end

target("unpak")
    set_kind("binary")

    add_files("unpak/**.cpp")
    add_headerfiles("unpak/**.hpp", "unpak/**.h")
