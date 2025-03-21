//
// Created by Oasis on 2025/3/11.
//

#include "tc_match.h"

// ==进度条=================================
extern int global_progress; // 全局进度变量
extern std::string global_status; // 全局状态变量
// ==进度条=================================

void signal_handler_index(int signum) {
    std::cout << "tcm: out of index time" << std::endl;
    exit(1);
}

void signal_handler_online(int signum) {
    std::cout << "tcm: out of online time" << std::endl;
    exit(1);
}

ResponseResult TCMatch(const RequestParameters& params) {
    // ==进度条=================================
    global_progress = 1;
    global_status = "start";
    // ==进度条=================================

    auto* tc_arg = new Arg();
    auto* tc_io = new IO();
    auto* tc_offline_index = new OfflineIndex();
    auto* tc_order = new MatchOrder();
    auto* tc_global_index = new GlobalIndex();
    auto* tc_search = new Search();
    auto* tc_misc = new Misc();
    auto* tc_g_index = new GIndex();

    ResponseResult response_result;

    tc_arg->path_of_stream = params.stream_path;
    tc_arg->path_of_query = params.query_path;

    tc_arg->path_of_result = params.result_mode.empty() ? R"(./)" : params.result_mode;
    tc_arg->result_mode = params.result_mode.empty() ? "qid" : params.result_mode;
    tc_arg->execute_mode = params.execute_mode.empty() ? "count" : params.execute_mode;
    tc_arg->data_percent = params.data_percent.empty() ? "0.6" : params.data_percent;
    tc_arg->index_time_limit = params.index_time_limit.empty() ? "36000" : params.index_time_limit;
    tc_arg->online_time_limit = params.online_time_limit.empty() ? "3600" : params.online_time_limit;
    tc_arg->is_using_static_merge = params.is_using_static_merge.empty() ? "y" : params.is_using_static_merge;
    tc_arg->is_using_dynamic_merge = params.is_using_dynamic_merge.empty() ? "y" : params.is_using_dynamic_merge;
    tc_arg->is_return_match_result = params.is_return_match_result.empty() ? "y" : params.is_return_match_result;
    tc_arg->max_match_count = params.max_match_count.empty() ? "100" : params.max_match_count;


    //=======================================================
    tc_arg->parse_dataset_name();

    auto now = std::chrono::system_clock::now();

    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&currentTime);

    //============The program starts.====================================

    // ==进度条=================================
    global_progress = 5;
    global_status = "loading";
    // ==进度条=================================

    //Loading data
    tc_io->load_timing_query(tc_arg);
    tc_io->load_stream_2_data_graph_and_update_graph(tc_arg);

    //========================================
    response_result.statistical_info.runtime = std::asctime(localTime);
    response_result.statistical_info.stream_file = tc_arg->path_of_stream;
    response_result.statistical_info.query_file = tc_arg->path_of_query;
    response_result.statistical_info.dataset = tc_arg->streamFileNameWithoutExtension;
    response_result.statistical_info.query_type = tc_arg->queryType;
    response_result.statistical_info.data_percent = tc_arg->data_percent;
    response_result.statistical_info.total_q_edges = std::to_string(tc_io->Q.size());
    response_result.statistical_info.total_s_edges = std::to_string(tc_io->S.size());

    response_result.statistical_info.execution_mode = tc_arg->execute_mode;
    response_result.statistical_info.result_mode = tc_arg->result_mode;

    response_result.statistical_info.update_valid = std::to_string(tc_io->valid_update_edge_num);
    response_result.statistical_info.total_update = std::to_string(tc_io->total_update_edge_num);
    response_result.statistical_info.valid_percentage = std::to_string(((double)tc_io->valid_update_edge_num / (double)tc_io->total_update_edge_num) * 100.0);

    // AllQuery all_query;
    for(auto &it:tc_io->q_id_2_q_edge){
        JsonQEdge jsonQEdge;
        jsonQEdge.q_id = std::to_string(it.first);
        jsonQEdge.src_id = std::to_string(it.second.u_source_id);
        jsonQEdge.tar_id = std::to_string(it.second.u_target_id);
        jsonQEdge.e_lab = std::to_string(it.second.u_edge_label);
        jsonQEdge.src_lab = std::to_string(it.second.u_source_label);
        jsonQEdge.tar_lab = std::to_string(it.second.u_target_label);
        response_result.all_query.all_query.emplace_back(jsonQEdge);
    }

    // AllTimeConstraint all_time_constraint;
    for(auto &it:tc_io->T){
        std::vector<JsonQEdge> jsonQEdgeVec;
        for(auto &it2:it){
            if(it2 == it.back()){
                for(auto &it3:tc_io->q_id_2_q_edge){
                    if(it3.second == it2){
                        JsonQEdge jsonQEdge;
                        jsonQEdge.q_id = std::to_string(it3.first);
                        jsonQEdge.src_id = std::to_string(it2.u_source_id);
                        jsonQEdge.tar_id = std::to_string(it2.u_target_id);
                        jsonQEdge.e_lab = std::to_string(it2.u_edge_label);
                        jsonQEdge.src_lab = std::to_string(it2.u_source_label);
                        jsonQEdge.tar_lab = std::to_string(it2.u_target_label);
                        jsonQEdgeVec.emplace_back(jsonQEdge);
                    }
                }
            } else{
                for(auto &it3:tc_io->q_id_2_q_edge){
                    if(it3.second == it2){
                        JsonQEdge jsonQEdge;
                        jsonQEdge.q_id = std::to_string(it3.first);
                        jsonQEdge.src_id = std::to_string(it2.u_source_id);
                        jsonQEdge.tar_id = std::to_string(it2.u_target_id);
                        jsonQEdge.e_lab = std::to_string(it2.u_edge_label);
                        jsonQEdge.src_lab = std::to_string(it2.u_source_label);
                        jsonQEdge.tar_lab = std::to_string(it2.u_target_label);
                        jsonQEdgeVec.emplace_back(jsonQEdge);
                    }
                }
            }
        }
        response_result.all_time_constraint.all_time_constraint.emplace_back(jsonQEdgeVec);
    }


    //=====Starting the build phase.======
#ifdef __linux__
    signal(SIGALRM, signal_handler_index);
    alarm(std::stoi(tc_arg->index_time_limit));
#endif

    // ==进度条=================================
    global_progress = 10;
    global_status = "building";
    // ==进度条=================================

    //build offline index
    tc_offline_index->build_offline_index(tc_io);

    //match order
    tc_order->build_search_order(tc_io, tc_offline_index);

    // AllSearchOrder all_search_order;
    for(auto &map_it:tc_order->search_order){
        SearchOrder searchOrder;
        for(auto &id2edge_it:tc_io->q_id_2_q_edge){
            auto &q_edge = id2edge_it.second;
            auto &q_id = id2edge_it.first;
            auto &key = map_it.first;
            if(q_edge == key.qe){
                searchOrder.q_id = std::to_string(q_id);
                break;
            }
        }

        for(auto &key_it:map_it.second){
            for(auto &id2edge_it:tc_io->q_id_2_q_edge){
                if(id2edge_it.second == key_it.qe){
                    searchOrder.order.emplace_back(std::to_string(id2edge_it.first));
                }
            }
        }
        response_result.all_search_order.all_search_order.emplace_back(searchOrder);
    }

    //===Starting the indexing phase.======================

    // ==进度条=================================
    global_progress = 15;
    global_status = "indexing";
    // ==进度条=================================

    tc_global_index->index_time_start = T_NOW;

    //==Initializing the global index.=========
    tc_global_index->index_process(tc_io, tc_offline_index, tc_arg, tc_g_index);

    tc_global_index->index_time_end = T_NOW;
    tc_global_index->index_time_span = tc_global_index->index_time_end - tc_global_index->index_time_start;

#ifdef __linux__
    alarm(0);
#endif

    response_result.statistical_info.index_time = std::to_string(tc_global_index->index_time_span.count());

    //=====Starting the online phase.======

    // ==进度条=================================
    global_progress = 20;
    global_status = "searching";
    // ==进度条=================================


    tc_global_index->online_time_start = T_NOW;

#ifdef __linux__
    signal(SIGALRM, signal_handler_online);
    alarm(std::stoi(tc_arg->online_time_limit));
#endif

    tc_global_index->online_process(tc_offline_index, tc_search, tc_order, tc_arg, tc_g_index, tc_io);

#ifdef __linux__
    alarm(0);
#endif

    tc_global_index->online_time_end = T_NOW;
    tc_global_index->online_time_span = tc_global_index->online_time_end - tc_global_index->online_time_start;

    response_result.statistical_info.online_time = std::to_string(tc_global_index->online_time_span.count());
    response_result.statistical_info.update_time = std::to_string(tc_global_index->online_time_span.count() - tc_global_index->search_time_span.count());
    response_result.statistical_info.search_time = std::to_string(tc_global_index->search_time_span.count());
    response_result.statistical_info.memory_use = std::to_string(tc_misc->getMemoryUse() / 1024);
    response_result.statistical_info.match_count = std::to_string(tc_search->match_count);

    // ==进度条=================================
    global_progress = 99;
    global_status = "writing";
    // ==进度条=================================


    //===Output the match result.======================
    if (tc_arg->is_return_match_result == "n") {
        delete tc_arg;
        delete tc_io;
        delete tc_offline_index;
        delete tc_order;
        delete tc_global_index;
        delete tc_search;
        delete tc_misc;
        delete tc_g_index;

        // ==进度条=================================
        global_progress = 100;
        global_status = "done";
        // ==进度条=================================

        return response_result;
    }


    uit max_result_number = 0;
    uit limit = std::stoi(tc_arg->max_match_count);

    if(tc_arg->result_mode == "qid"){
        for (const auto &sub_vec : tc_search->match_result) {
            std::vector<JsonSEdge> jsonSEdgeVec;
            for(auto &it:tc_io->q_id_2_q_edge){
                uit q_id = it.first;
                for (const auto &elem : sub_vec) {
                    if(q_id == elem.q_id){
                        JsonSEdge jsonSEdge;
                        jsonSEdge.src_id = std::to_string(elem.source_id);
                        jsonSEdge.tar_id = std::to_string(elem.target_id);
                        jsonSEdge.e_lab = std::to_string(elem.edge_label);
                        jsonSEdge.src_lab = std::to_string(elem.source_label);
                        jsonSEdge.tar_lab = std::to_string(elem.target_label);
                        jsonSEdge.timestamp = std::to_string(elem.timestamp);
                        jsonSEdgeVec.emplace_back(jsonSEdge);
                        break;
                    }
                }
            }
            response_result.all_match_result.all_match_result.emplace_back(jsonSEdgeVec);

            max_result_number += 1;

            if(max_result_number > limit){  //Avoiding excessively large match.result files.
                break;
            }
        }
    } else if (tc_arg->result_mode == "time"){
        std::vector<uit> time_stamp_all;
        for (const auto &sub_vec : tc_search->match_result) {
            std::vector<JsonSEdge> jsonSEdgeVec;
            for(auto &elem:sub_vec){
                time_stamp_all.emplace_back(elem.timestamp);
            }

            std::sort(time_stamp_all.begin(), time_stamp_all.end());

            for(auto &time_it:time_stamp_all){
                for(auto &elem:sub_vec){
                    if(elem.timestamp == time_it){
                        JsonSEdge jsonSEdge;
                        jsonSEdge.src_id = std::to_string(elem.source_id);
                        jsonSEdge.tar_id = std::to_string(elem.target_id);
                        jsonSEdge.e_lab = std::to_string(elem.edge_label);
                        jsonSEdge.src_lab = std::to_string(elem.source_label);
                        jsonSEdge.tar_lab = std::to_string(elem.target_label);
                        jsonSEdge.timestamp = std::to_string(elem.timestamp);
                        jsonSEdgeVec.emplace_back(jsonSEdge);
                        break;
                    }
                }
            }
            response_result.all_match_result.all_match_result.emplace_back(jsonSEdgeVec);

            time_stamp_all.clear();
        }
    } else{
        for (const auto &sub_vec : tc_search->match_result) {
            std::vector<JsonSEdge> jsonSEdgeVec;
            for(auto &elem:sub_vec){
                JsonSEdge jsonSEdge;
                jsonSEdge.src_id = std::to_string(elem.source_id);
                jsonSEdge.tar_id = std::to_string(elem.target_id);
                jsonSEdge.e_lab = std::to_string(elem.edge_label);
                jsonSEdge.src_lab = std::to_string(elem.source_label);
                jsonSEdge.tar_lab = std::to_string(elem.target_label);
                jsonSEdge.timestamp = std::to_string(elem.timestamp);
                jsonSEdgeVec.emplace_back(jsonSEdge);
            }
            response_result.all_match_result.all_match_result.emplace_back(jsonSEdgeVec);
        }
    }

    //============Clearing the memory====================================
    delete tc_arg;
    delete tc_io;
    delete tc_offline_index;
    delete tc_order;
    delete tc_global_index;
    delete tc_search;
    delete tc_misc;

    // ==进度条=================================
    global_progress = 100;
    global_status = "done";
    // ==进度条=================================

    return response_result;
}
