#include "follow_fsm.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

FSM_INITIAL_STATE(FollowStage, FollowStage_Idle)

auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("followfsm.log", false);
auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

spdlog::logger logger_fsm("fsmlog", {file_sink, console_sink});

