cmake_minimum_required(VERSION 4.1)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} composites core leaf actions conditions helpers)

add_executable(untitled2 main.cpp
        core/i_node.h
        core/composite.h
        composites/selector.h
        composites/sequence.h
        leaf/condition.h
        leaf/action.h
        core/behaviour_tree.h
        core/bt_tracer.h
        core/blackboard.h
        core/bt_types.h
        conditions/IsTargetVisible.h
        conditions/IsTargetInRange.h
        conditions/IsAmmoEmpty.h
        actions/shoot.h
        actions/reload.h
        actions/patrol.h
        helpers/console_colors.h
        helpers/tree_printer.h
)
