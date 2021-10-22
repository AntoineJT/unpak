set_xmakever("2.5.6")

set_project("xtractpak")
set_version("0.0.0")

add_rules("mode.debug", "mode.release", "mode.asan")

if is_plat("linux") or is_plat("mingw") then
    add_links("stdc++fs")
end

if is_mode("release") then
    set_optimize("fastest")
end

target("common")
    set_kind("static")
    set_languages("c89", "cxx17")

    add_files("common/**.c", "common/**.cpp")
    add_headerfiles("common/**.h")
    add_includedirs("common/include/", {public = true})

target("cpak")
    set_kind("static")
    set_languages("c89")

    add_files("cpak/**.c")
    add_headerfiles("cpak/**.h")
    add_includedirs("cpak/include/", {public = true})

    add_deps("common")

target("unpak")
    set_kind("binary")
    set_languages("cxx17")

    add_files("unpak/**.cpp")
    add_headerfiles("unpak/**.hpp")

    add_deps("common", "cpak")
