#include "httplib.h"

void handleRequest(const httplib::Request& req, httplib::Response& res);

void logRequest(const httplib::Request& req, const httplib::Response& res);