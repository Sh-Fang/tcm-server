#include "httplib.h"
#include "json.hpp"
#include "handler.h"

#include <chrono>
#include <iomanip>
#include <iostream>


int main() {
    httplib::Server server;

    // 设置日志记录（只打印到控制台）
    server.set_logger(logRequest);

    server.Post("/match", handleRequest);
    std::cout << "Server started on http://localhost:8081" << std::endl;

    server.listen("0.0.0.0", 8081);
}