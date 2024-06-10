-- Start ==== 全局目标
-- 根域, 影响所有target（demo和test都会加上此宏定义）
add_includedirs("inc/")
-- 在链接阶段添加 -mwindows 选项, 从而隐藏控制台窗口
add_ldflags("-Wl,-subsystem,windows",{force=true})
-- End ==== 全局目标

-- Start ==== rules 规则
add_rules("plugin.compile_commands.autoupdate", {outputdir = "./"})
-- End ==== rules 规则


-- Start ==== target
target("utils")
    set_kind("static")
    add_files("./src/*.cpp")
target_end()

target("mouse")
    set_kind("binary")
    add_files("./src/mouse/*.cpp")
    add_deps("utils")
    add_linkdirs("./lib") -- 添加链接库搜索目录, 一般他是与 add_links 配合使用的
    add_links("interception")
target_end()

target("release_sticky_keys")
    set_kind("binary")
    add_files("src/release_sticky_keys/*.cpp")
    add_deps("utils")
    add_linkdirs("./lib") -- 添加链接库搜索目录, 一般他是与 add_links 配合使用的
    add_links("interception")

    -- 定义复制 interception.dll 到输出目录的规则
    after_build(function (target)
        -- 获取目标输出目录
        local target_dir = path.directory(target:targetfile())

        -- 定义 dll 文件路径
        local dll_file = path.join("lib", "interception.dll")

        -- 复制 dll 文件到目标输出目录
        os.cp(dll_file, target_dir)
    end)
target_end()

target("caps2esc")
    set_kind("binary")
    add_files("src/caps2esc/caps2esc.cpp")
    add_deps("utils")
    
    add_linkdirs("./lib") -- 添加链接库搜索目录, 一般他是与 add_links 配合使用的
    add_links("interception")

    -- 定义复制 interception.dll 到输出目录的规则
    after_build(function (target)
        -- 获取目标输出目录
        local target_dir = path.directory(target:targetfile())

        -- 定义 dll 文件路径
        local dll_file = path.join("lib", "interception.dll")

        -- 复制 dll 文件到目标输出目录
        os.cp(dll_file, target_dir)
    end)
target_end()
-- End ==== target

