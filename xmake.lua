set_project("xtractpak")
set_version("0.0.0")

add_rules("mode.debug", "mode.release", "mode.asan")

if is_mode("release") then
    set_optimize("fastest")
end

target("cpak")
    set_kind("static")
    set_languages("c89")

    add_files("cpak/**.c")
    add_headerfiles("cpak/**.h")

--[[
target("unpak")
    set_kind("binary")

    add_files("unpak/**.cpp")
    add_headerfiles("unpak/**.hpp", "unpak/**.h")
]]