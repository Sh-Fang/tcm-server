#include "httpHandle.h"
#include "tc_match.h"

// ==进度条=================================
int global_progress = 0; // 全局进度变量
std::string global_status; // 全局状态变量
// ==进度条=================================

// 处理 HTTP 请求
void handleMatch(const httplib::Request& req, httplib::Response& res) {
    try {
        json request_json = json::parse(req.body);
        RequestParameters input = parseInput(request_json);

        ResponseResult output = TCMatch(input);

        json response_json = output;

        global_progress = 100;

        res.set_content(response_json.dump(), "application/json");
    } catch (const std::exception&) {
        res.status = 400;
        res.set_content(R"({"error": "Invalid request"})", "application/json");
    }

    global_progress = 0;
}

void handleGetProgress(const httplib::Request& req, httplib::Response& res) {
    res.set_header("Content-Type", "text/event-stream");
    res.set_header("Cache-Control", "no-cache");
    res.set_header("Connection", "keep-alive");

    res.status = 200;
    res.set_content(std::to_string(global_progress), "text/plain");
}



void logRequest(const httplib::Request& req, const httplib::Response& res) {
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    
    // 使用 std::localtime (非线程安全)
    std::tm* tm_info = std::localtime(&in_time_t);  

    // 打印日志
    std::cout << "[" << std::put_time(tm_info, "%Y-%m-%d %H:%M:%S") << "] "
              << "Client: " << req.remote_addr << " | "
              << "Method: " << req.method << " | "
              << "Path: " << req.path << " | "
              << "Status: " << res.status << " | "
              << "Body: " << res.body << std::endl;
}

int startServer() {
    httplib::Server server;

    // 设置日志记录（只打印到控制台）
    server.set_logger(logRequest);

    server.Post("/match", handleMatch);
    server.Get("/progress", handleGetProgress);
    std::cout << "Server started on http://localhost:8081" << std::endl;

    server.listen("0.0.0.0", 8081);
    return 0;
}