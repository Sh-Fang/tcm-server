#include "httplib.h"

struct Input{
    std::string stream_path;
    std::string query_path; 
};

struct Output{
    std::string result;
};

Output Matching(std::string& stream_path, std::string& query_path);

void handleRequest(const httplib::Request& req, httplib::Response& res);

void logRequest(const httplib::Request& req, const httplib::Response& res);