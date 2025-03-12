#include "httplib.h"

void handleMatch(const httplib::Request& req, httplib::Response& res);

void handleGetProgress(const httplib::Request& req, httplib::Response& res);

void logRequest(const httplib::Request& req, const httplib::Response& res);

int startServer();