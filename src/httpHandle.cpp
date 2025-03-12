#include "httpHandle.h"
#include "tc_match.h"

// 处理 HTTP 请求
void handleMatch(const httplib::Request& req, httplib::Response& res) {
    try {
        json request_json = json::parse(req.body);
        RequestParameters input = parseInput(request_json);

        ResponseResult output = TCMatch(input);

        json response_json = output;

        res.set_content(response_json.dump(), "application/json");
    } catch (const std::exception&) {
        res.status = 400;
        res.set_content(R"({"error": "Invalid request"})", "application/json");
    }
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
    std::cout << "Server started on http://localhost:8081" << std::endl;

    server.listen("0.0.0.0", 8081);
    return 0;
}