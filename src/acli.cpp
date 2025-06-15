#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include <CLI/CLI.hpp>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


void ThInit(const std::string& package_name, const std::string& version, const std::string& description, const std::string& entry_point, const std::string& author, const std::string& git_repository, const std::string& url, const std::string& license) {
    // 创建 JSON 文档
    rapidjson::Document d;
    d.SetObject();

    // 获取分配器
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

    // 设置其他字段
    d.AddMember("package_name", rapidjson::Value(package_name.c_str(), allocator), allocator);
    d.AddMember("version", rapidjson::Value(version.c_str(), allocator), allocator);
    d.AddMember("description", rapidjson::Value(description.c_str(), allocator), allocator);
    d.AddMember("entry_point", rapidjson::Value(entry_point.c_str(), allocator), allocator);
    d.AddMember("author", rapidjson::Value(author.c_str(), allocator), allocator);
    d.AddMember("git_repository", rapidjson::Value(git_repository.c_str(), allocator), allocator);
    d.AddMember("url", rapidjson::Value(url.c_str(), allocator), allocator);
    d.AddMember("license", rapidjson::Value(license.c_str(), allocator), allocator);

    // 将 JSON 文档写入文件
    std::filesystem::create_directory(package_name);
    std::ofstream file(package_name + "/ThlangProject.json");
    if (!file.is_open()) {
        std::cerr << "文件 ThlangProject.json 写入失败！\n";
        return;
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    std::string flag;
    std::cout << "下列文件内容将被写入" << package_name + "/ThlangProject.json:\n" << buffer.GetString() << "\n" ;
    file << buffer.GetString();
    std::cout << "Done...\n";
    file.close();

    // 设置readme
    // TODO
    std::string readme = "# " + package_name +
        "\n## 项目简介" +
        "\n" + description +
        "\n - 作者: " + author +
        "\n - 项目主页: " + url +
        "\n - 版本号: " + version +
        "\n - github地址: " + git_repository +
        "\n - 许可证:" + license +
        "\n\n## 使用方法:" \
        "\n```sh" \
        "\nthlang build main.th -o main" \
        "\n./main" \
        "\n```\n";
    
    std::ofstream readme_f(package_name + "/Readme.md");
    if(!readme_f.is_open()){
        std::cerr << "Readme.md 写入失败!\n";
        return ;
    }
    readme_f << readme;
    readme_f.close();

    // main.th
    std::string main_th = "整数型 入口(){\n    返回 0;\n}\n";
    std::ofstream main_th_f(package_name + "/" + entry_point);
    if(!main_th_f.is_open()){
        std::cerr << entry_point << " 写入失败!\n";
        return ;
    }
    main_th_f << main_th;
    main_th_f.close();


}

void ThInfo() {
    // 检查文件是否存在
    if (std::filesystem::exists("ThlangProject.json")) {
        // 读取文件内容
        std::ifstream file("ThlangProject.json");
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();

        // 使用 rapidjson 解析 JSON
        rapidjson::Document d;
        d.Parse(content.c_str());

        // 检查解析是否成功
        if (d.HasParseError()) {
            std::cerr << "JSON 解析错误！" << "\n";
            return;
        }

        // 读取每个字段
        std::string package_name = d["package_name"].GetString();
        std::string version = d["version"].GetString();
        std::string description = d["description"].GetString();
        std::string entry_point = d["entry_point"].GetString();
        std::string author = d["author"].GetString();
        std::string git_repository = d["git_repository"].GetString();
        std::string url = d["url"].GetString();
        std::string license = d["license"].GetString();

        // 输出字段内容
        std::cout << "包名 package_name: " << package_name << "\n";
        std::cout << "版本号 version: " << version << "\n";
        std::cout << "介绍 description: " << description << "\n";
        std::cout << "入口文件 entry_point: " << entry_point << "\n";
        std::cout << "作者 author: " << author << "\n";
        std::cout << "仓库地址 git_repository: " << git_repository << "\n";
        std::cout << "主页 url: " << url << "\n";
        std::cout << "许可证 license: " << license << "\n";
    } else {
        std::cerr << "文件 ThlangProject.json 不存在！\n请尝试init创建项目\n"; // TODO:修改命令行工具名称
    }
}

int main(int argc, char** argv) {
    CLI::App app{"THlang"};
    argv = app.ensure_utf8(argv);

    auto *init = app.add_subcommand("init", "创建一个包");
    std::string package_name, version, description, entry_point, author, git_repository, url, license;
    init->add_option("package_name", package_name, "包名")->required();
    init->add_option("-v, --version", version, "版本号(1.0.0)");
    init->add_option("-d, --description", description, "介绍");
    init->add_option("-e, --entry-point", entry_point, "入口文件(main.th)");
    init->add_option("-a, --author", author, "作者");
    init->add_option("--git-repository", git_repository, "github仓库地址");
    init->add_option("--url", url, "主页url");
    init->add_option("--license", license, "许可证");


    auto *build = app.add_subcommand("build", "对当前目录进行打包");

    auto *info = app.add_subcommand("info", "获取当前包的信息");

    CLI11_PARSE(app, argc, argv);

    if(*init){
        if(version.empty()){
            std::cout << "版本号version:(1.0.0)";
            std::getline(std::cin, version);
            if(version.empty()){
                version = "1.0.0";
            }
        }
        if(description.empty()){
            std::cout << "介绍description:";
            std::getline(std::cin, description);
        }
        if(entry_point.empty()){
            std::cout << "入口文件entry_point:(main.th)";
            std::getline(std::cin, entry_point);
            if (entry_point.empty()) {
                entry_point = "main.th";
            }
        }
        if(author.empty()){
            std::cout << "作者author:";
            std::getline(std::cin, author);
        }
        if(git_repository.empty()){
            std::cout << "github仓库地址git repository:";
            std::getline(std::cin, git_repository);
        }
        if(url.empty()){
            std::cout << "主页地址url:";
            std::getline(std::cin, url);
        }
        if(license.empty()){
            std::cout << "许可证license:(MIT)";
            std::getline(std::cin, license);
            if(license.empty()){
                license = "MIT";
            }
        }
        ThInit(package_name, version, description, entry_point, author, git_repository, url, license);
    }
    else if(*info){
        ThInfo();
    }

    return 0;
}