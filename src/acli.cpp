#include <CLI/CLI.hpp>
#include <iostream>
#include <vector>
#include <filesystem>

void ThInit(std::string package_name){
    /*初始化项目 init project*/
    std::ofstream file("ThlangProject.json");
    if(!file.is_open()){
        std::cerr << "文件 ThlangProject.json 写入失败！\n";
    }
    file << "{\n" \
        "    \"package_name\": \"" + package_name +"\",\n" \
        "}\n";
    file.close();

}

int main(int argc, char** argv) {
    CLI::App app{"THlang"};
    argv = app.ensure_utf8(argv);
    auto *init = app.add_subcommand("init", "创建一个包");
    std::string package_name;
    init->add_option("package_name", package_name, "包名")->required();
    auto *build = app.add_subcommand("build", "对当前目录进行打包");
    CLI11_PARSE(app, argc, argv);
    if(*init){
        std::cout << package_name << "\n";
        ThInit(package_name);
    }
    return 0;
}