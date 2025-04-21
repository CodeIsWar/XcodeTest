set_languages("cxx23")
add_rules("mode.release")
target("demo")
    set_kind("binary")
    add_files("src/*.cpp")
    if is_plat("windows") then
        add_cxxflags("/MD")
    end