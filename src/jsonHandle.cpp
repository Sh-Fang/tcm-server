#include "jsonHandle.h"
#include <iostream>

// 解析 JSON 输入（C++ server这边不需要判断数据的合法性，只需要接收数据然后处理就行）
RequestParameters parseInput(const json& j) {
    return {
        j.value("stream_path", ""),
        j.value("query_path", ""),
        j.value("max_match_count", ""),
        j.value("data_percent", ""),
        j.value("result_mode", ""),
        j.value("execute_mode", ""),
        j.value("index_time_limit", ""),
        j.value("online_time_limit", ""),
        j.value("is_using_static_merge", ""),
        j.value("is_using_dynamic_merge", ""),
        j.value("is_return_match_result", "")
    };
}