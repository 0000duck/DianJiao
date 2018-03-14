#!/usr/bin/env python

import rospy
import actionlib
import chess_msgs.msg

def chess_action_client():
    client = actionlib.SimpleActionClient('chess_action', chess_msgs.msg.StepAction)
    client.wait_for_server()
    
    # goal
    goal = chess_msgs.msg.StepGoal()
    goal.max_x = 0.27
    goal.max_y = 0.27
    op = chess_msgs.msg.Operation()
    op.type = 0
    op.pick_x = 0.2
    op.pick_y = 0.2
    op.place_x = 0.3
    op.place_y = 0.3
    goal.ops.append(op)
    
    # send
    client.send_goal(goal)

    client.wait_for_result()

    return client.get_result()

if __name__ == '__main__':
    rospy.init_node('chess_action_client_py')
    result = chess_action_client()
    print("Result:", result.res, result.msg)