#include "httplib.h"
#include "json.hpp"
#include "GraphMatch.h"

using json = nlohmann::json;

// 解析 JSON 输入
GraphData parseGraphData(const json& j) {
    return { j["nodes"], j["edges"] };
}

void logRequest(const httplib::Request& req, const httplib::Response& res) {
    std::cout << "[" << req.method << "] " << req.path
              << " - Status: " << res.status << std::endl;
}

// 处理 HTTP 请求
void handleRequest(const httplib::Request& req, httplib::Response& res) {
    try {
        json request_json = json::parse(req.body);
        GraphData graphData = parseGraphData(request_json);

        OutputData result = GraphMatch(graphData);

        json response_json;
        response_json["matched_subgraph"] = result.matched_subgraph;

        res.set_content(response_json.dump(), "application/json");
    } catch (const std::exception&) {
        res.status = 400;
        res.set_content("{\"error\": \"Invalid request\"}", "application/json");
    }
}

int main() {
    httplib::Server server;

    // 设置日志记录（只打印到控制台）
    server.set_logger(logRequest);

    server.Post("/match", handleRequest);
    std::cout << "Server started on http://localhost:8081" << std::endl;

    server.listen("0.0.0.0", 8081);
}