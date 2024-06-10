

-- Start ==== rules 规则
add_rules("plugin.compile_commands.autoupdate", {outputdir = "./"})
-- End ==== rules 规则


-- Start ==== target
target("keys")
    set_kind("binary")
    add_files("src/keys.cpp")
    add_includedirs("inc/")
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

