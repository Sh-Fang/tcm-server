//
// Created by Oasis on 2025/3/11.
//

#ifndef TCMSERVER_TC_MATCH_H
#define TCMSERVER_TC_MATCH_H

#include <iostream>
#include <csignal>
#include <unistd.h>

#include "tc_basic_type.h"
#include "tc_arg.h"
#include "tc_io.h"
#include "tc_offline_index.h"
#include "tc_match_order.h"
#include "tc_global_index.h"
#include "tc_search.h"
#include "tc_misc.h"
#include "tc_g_index.h"

#include "jsonHandle.h"

//==Signal processing function==============================
void signal_handler_index(int signum);

void signal_handler_online(int signum);
//================================

ResponseResult TCMatch(const RequestParameters& params);

#endif //TCMSERVER_TC_MATCH_H
