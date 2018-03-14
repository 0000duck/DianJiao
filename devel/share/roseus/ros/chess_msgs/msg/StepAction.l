;; Auto-generated. Do not edit!


(when (boundp 'chess_msgs::StepAction)
  (if (not (find-package "CHESS_MSGS"))
    (make-package "CHESS_MSGS"))
  (shadow 'StepAction (find-package "CHESS_MSGS")))
(unless (find-package "CHESS_MSGS::STEPACTION")
  (make-package "CHESS_MSGS::STEPACTION"))

(in-package "ROS")
;;//! \htmlinclude StepAction.msg.html


(defclass chess_msgs::StepAction
  :super ros::object
  :slots (_action_goal _action_result _action_feedback ))

(defmethod chess_msgs::StepAction
  (:init
   (&key
    ((:action_goal __action_goal) (instance chess_msgs::StepActionGoal :init))
    ((:action_result __action_result) (instance chess_msgs::StepActionResult :init))
    ((:action_feedback __action_feedback) (instance chess_msgs::StepActionFeedback :init))
    )
   (send-super :init)
   (setq _action_goal __action_goal)
   (setq _action_result __action_result)
   (setq _action_feedback __action_feedback)
   self)
  (:action_goal
   (&rest __action_goal)
   (if (keywordp (car __action_goal))
       (send* _action_goal __action_goal)
     (progn
       (if __action_goal (setq _action_goal (car __action_goal)))
       _action_goal)))
  (:action_result
   (&rest __action_result)
   (if (keywordp (car __action_result))
       (send* _action_result __action_result)
     (progn
       (if __action_result (setq _action_result (car __action_result)))
       _action_result)))
  (:action_feedback
   (&rest __action_feedback)
   (if (keywordp (car __action_feedback))
       (send* _action_feedback __action_feedback)
     (progn
       (if __action_feedback (setq _action_feedback (car __action_feedback)))
       _action_feedback)))
  (:serialization-length
   ()
   (+
    ;; chess_msgs/StepActionGoal _action_goal
    (send _action_goal :serialization-length)
    ;; chess_msgs/StepActionResult _action_result
    (send _action_result :serialization-length)
    ;; chess_msgs/StepActionFeedback _action_feedback
    (send _action_feedback :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; chess_msgs/StepActionGoal _action_goal
       (send _action_goal :serialize s)
     ;; chess_msgs/StepActionResult _action_result
       (send _action_result :serialize s)
     ;; chess_msgs/StepActionFeedback _action_feedback
       (send _action_feedback :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; chess_msgs/StepActionGoal _action_goal
     (send _action_goal :deserialize buf ptr-) (incf ptr- (send _action_goal :serialization-length))
   ;; chess_msgs/StepActionResult _action_result
     (send _action_result :deserialize buf ptr-) (incf ptr- (send _action_result :serialization-length))
   ;; chess_msgs/StepActionFeedback _action_feedback
     (send _action_feedback :deserialize buf ptr-) (incf ptr- (send _action_feedback :serialization-length))
   ;;
   self)
  )

(setf (get chess_msgs::StepAction :md5sum-) "b914ecebce9cd7345fb74b53a497373e")
(setf (get chess_msgs::StepAction :datatype-) "chess_msgs/StepAction")
(setf (get chess_msgs::StepAction :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

StepActionGoal action_goal
StepActionResult action_result
StepActionFeedback action_feedback

================================================================================
MSG: chess_msgs/StepActionGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalID goal_id
StepGoal goal

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: actionlib_msgs/GoalID
# The stamp should store the time at which this goal was requested.
# It is used by an action server when it tries to preempt all
# goals that were requested before a certain time
time stamp

# The id provides a way to associate feedback and
# result message with specific goal requests. The id
# specified must be unique.
string id


================================================================================
MSG: chess_msgs/StepGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# goal definition
Operation[] ops

================================================================================
MSG: chess_msgs/Operation
# operation type go = 0 ; capture = 1 ; wait = 2
uint32 OPERATION_GO = 0      
uint32 OPERATION_CAPTURE = 1
uint32 OPERATION_WAIT = 2

# position type far = 0; near = 1
uint32 POSITION_FAR = 0
uint32 POSITION_NEAR = 1

uint32 type

uint32  pick_type
float32 pick_x
float32 pick_y

uint32  place_type
float32 place_x
float32 place_y


================================================================================
MSG: chess_msgs/StepActionResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
StepResult result

================================================================================
MSG: actionlib_msgs/GoalStatus
GoalID goal_id
uint8 status
uint8 PENDING         = 0   # The goal has yet to be processed by the action server
uint8 ACTIVE          = 1   # The goal is currently being processed by the action server
uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing
                            #   and has since completed its execution (Terminal State)
uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)
uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due
                            #    to some failure (Terminal State)
uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,
                            #    because the goal was unattainable or invalid (Terminal State)
uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing
                            #    and has not yet completed execution
uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,
                            #    but the action server has not yet confirmed that the goal is canceled
uint8 RECALLED        = 8   # The goal received a cancel request before it started executing
                            #    and was successfully cancelled (Terminal State)
uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be
                            #    sent over the wire by an action server

#Allow for the user to associate a string with GoalStatus for debugging
string text


================================================================================
MSG: chess_msgs/StepResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# result definition
bool res
string msg

================================================================================
MSG: chess_msgs/StepActionFeedback
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
StepFeedback feedback

================================================================================
MSG: chess_msgs/StepFeedback
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# feedback definition
string feedback

")



(provide :chess_msgs/StepAction "b914ecebce9cd7345fb74b53a497373e")

