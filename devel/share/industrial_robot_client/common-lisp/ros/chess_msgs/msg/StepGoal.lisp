; Auto-generated. Do not edit!


(cl:in-package chess_msgs-msg)


;//! \htmlinclude StepGoal.msg.html

(cl:defclass <StepGoal> (roslisp-msg-protocol:ros-message)
  ((ops
    :reader ops
    :initarg :ops
    :type (cl:vector chess_msgs-msg:Operation)
   :initform (cl:make-array 0 :element-type 'chess_msgs-msg:Operation :initial-element (cl:make-instance 'chess_msgs-msg:Operation))))
)

(cl:defclass StepGoal (<StepGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StepGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StepGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name chess_msgs-msg:<StepGoal> is deprecated: use chess_msgs-msg:StepGoal instead.")))

(cl:ensure-generic-function 'ops-val :lambda-list '(m))
(cl:defmethod ops-val ((m <StepGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-msg:ops-val is deprecated.  Use chess_msgs-msg:ops instead.")
  (ops m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StepGoal>) ostream)
  "Serializes a message object of type '<StepGoal>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'ops))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'ops))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StepGoal>) istream)
  "Deserializes a message object of type '<StepGoal>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'ops) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'ops)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'chess_msgs-msg:Operation))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StepGoal>)))
  "Returns string type for a message object of type '<StepGoal>"
  "chess_msgs/StepGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StepGoal)))
  "Returns string type for a message object of type 'StepGoal"
  "chess_msgs/StepGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StepGoal>)))
  "Returns md5sum for a message object of type '<StepGoal>"
  "3be9cbb635e0b30a073919d65ae3caf2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StepGoal)))
  "Returns md5sum for a message object of type 'StepGoal"
  "3be9cbb635e0b30a073919d65ae3caf2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StepGoal>)))
  "Returns full string definition for message of type '<StepGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# goal definition~%Operation[] ops~%~%================================================================================~%MSG: chess_msgs/Operation~%# operation type go = 0 ; capture = 1 ; wait = 2~%uint32 OPERATION_GO = 0      ~%uint32 OPERATION_CAPTURE = 1~%uint32 OPERATION_WAIT = 2~%~%# position type far = 0; near = 1~%uint32 POSITION_FAR = 0~%uint32 POSITION_NEAR = 1~%~%uint32 type~%~%uint32  pick_type~%float32 pick_x~%float32 pick_y~%~%uint32  place_type~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StepGoal)))
  "Returns full string definition for message of type 'StepGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# goal definition~%Operation[] ops~%~%================================================================================~%MSG: chess_msgs/Operation~%# operation type go = 0 ; capture = 1 ; wait = 2~%uint32 OPERATION_GO = 0      ~%uint32 OPERATION_CAPTURE = 1~%uint32 OPERATION_WAIT = 2~%~%# position type far = 0; near = 1~%uint32 POSITION_FAR = 0~%uint32 POSITION_NEAR = 1~%~%uint32 type~%~%uint32  pick_type~%float32 pick_x~%float32 pick_y~%~%uint32  place_type~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StepGoal>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ops) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StepGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'StepGoal
    (cl:cons ':ops (ops msg))
))
