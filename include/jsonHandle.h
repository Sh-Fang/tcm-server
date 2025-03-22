#include "json.hpp"

using json = nlohmann::json;

struct RequestParameters {
  std::string stream_path;
  std::string query_path;
  std::string max_match_count;
  std::string data_percent;
  std::string result_mode;
  std::string execute_mode;

  std::string index_time_limit;
  std::string online_time_limit;
  std::string is_using_static_merge;
  std::string is_using_dynamic_merge;
  std::string is_return_match_result;
};

struct JsonQEdge {
  std::string q_id;
  std::string src_id;
  std::string tar_id;
  std::string e_lab;
  std::string src_lab;
  std::string tar_lab;
};

struct AllTimeConstraint {
  std::vector<std::vector<JsonQEdge>> all_time_constraint;
};

struct AllQuery {
  std::vector<JsonQEdge> all_query;
};

struct SearchOrder {
  std::string q_id;
  std::vector<std::string> order;
};

struct AllSearchOrder {
  std::vector<SearchOrder> all_search_order;
};

struct JsonSEdge {
  std::string src_id;
  std::string tar_id;
  std::string e_lab;
  std::string src_lab;
  std::string tar_lab;
  std::string timestamp;
};

struct AllMatchResult {
  std::vector<std::vector<JsonSEdge>> all_match_result;
};

struct StatisticalInfo {
  std::string runtime;
  std::string stream_file;
  std::string query_file;

  std::string dataset;
  std::string query_type;
  std::string data_percent;

  std::string total_q_edges;
  std::string total_s_edges;

  std::string execution_mode;
  std::string result_mode;

  std::string update_valid;
  std::string total_update;
  std::string valid_percentage;

  std::string index_time;
  std::string online_time;
  std::string update_time;
  std::string search_time;

  std::string memory_use;
  std::string match_count;
};

struct ResponseResult {
  StatisticalInfo statistical_info;

  AllQuery all_query;
  AllTimeConstraint all_time_constraint;
  AllSearchOrder all_search_order;
  AllMatchResult all_match_result;
};

RequestParameters parseInput(const json& j);

// 定义 JSON 转换宏
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JsonQEdge, q_id, src_id, tar_id, e_lab,
                                   src_lab, tar_lab)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AllTimeConstraint, all_time_constraint)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AllQuery, all_query)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SearchOrder, q_id, order)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AllSearchOrder, all_search_order)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JsonSEdge, src_id, tar_id, e_lab, src_lab,
                                   tar_lab, timestamp)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AllMatchResult, all_match_result)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(StatisticalInfo, runtime, stream_file,
                                   query_file, dataset, query_type,
                                   data_percent, total_q_edges, total_s_edges,
                                   execution_mode, result_mode, update_valid,
                                   total_update, valid_percentage, index_time,
                                   online_time, update_time, search_time,
                                   memory_use, match_count)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ResponseResult, statistical_info, all_query,
                                   all_time_constraint, all_search_order,
                                   all_match_result)