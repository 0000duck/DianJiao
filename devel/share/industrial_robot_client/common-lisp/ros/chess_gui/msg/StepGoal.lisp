; Auto-generated. Do not edit!


(cl:in-package chess_gui-msg)


;//! \htmlinclude StepGoal.msg.html

(cl:defclass <StepGoal> (roslisp-msg-protocol:ros-message)
  ((max_x
    :reader max_x
    :initarg :max_x
    :type cl:float
    :initform 0.0)
   (max_y
    :reader max_y
    :initarg :max_y
    :type cl:float
    :initform 0.0)
   (ops
    :reader ops
    :initarg :ops
    :type (cl:vector chess_gui-msg:Operation)
   :initform (cl:make-array 0 :element-type 'chess_gui-msg:Operation :initial-element (cl:make-instance 'chess_gui-msg:Operation))))
)

(cl:defclass StepGoal (<StepGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StepGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StepGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name chess_gui-msg:<StepGoal> is deprecated: use chess_gui-msg:StepGoal instead.")))

(cl:ensure-generic-function 'max_x-val :lambda-list '(m))
(cl:defmethod max_x-val ((m <StepGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_gui-msg:max_x-val is deprecated.  Use chess_gui-msg:max_x instead.")
  (max_x m))

(cl:ensure-generic-function 'max_y-val :lambda-list '(m))
(cl:defmethod max_y-val ((m <StepGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_gui-msg:max_y-val is deprecated.  Use chess_gui-msg:max_y instead.")
  (max_y m))

(cl:ensure-generic-function 'ops-val :lambda-list '(m))
(cl:defmethod ops-val ((m <StepGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_gui-msg:ops-val is deprecated.  Use chess_gui-msg:ops instead.")
  (ops m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StepGoal>) ostream)
  "Serializes a message object of type '<StepGoal>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'max_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'max_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
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
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_y) (roslisp-utils:decode-single-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'ops) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'ops)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'chess_gui-msg:Operation))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StepGoal>)))
  "Returns string type for a message object of type '<StepGoal>"
  "chess_gui/StepGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StepGoal)))
  "Returns string type for a message object of type 'StepGoal"
  "chess_gui/StepGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StepGoal>)))
  "Returns md5sum for a message object of type '<StepGoal>"
  "8659c0f3910f1e3a2a4f3f1f180fafca")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StepGoal)))
  "Returns md5sum for a message object of type 'StepGoal"
  "8659c0f3910f1e3a2a4f3f1f180fafca")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StepGoal>)))
  "Returns full string definition for message of type '<StepGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# goal definition~%float32 max_x~%float32 max_y~%Operation[] ops~%~%================================================================================~%MSG: chess_gui/Operation~%# operation type go = 0 ; capture = 1~%uint32 OPERATION_GO = 0      ~%uint32 OPREATION_CAPTURE = 1~%~%uint32 type~%~%float32 pick_x~%float32 pick_y~%~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StepGoal)))
  "Returns full string definition for message of type 'StepGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# goal definition~%float32 max_x~%float32 max_y~%Operation[] ops~%~%================================================================================~%MSG: chess_gui/Operation~%# operation type go = 0 ; capture = 1~%uint32 OPERATION_GO = 0      ~%uint32 OPREATION_CAPTURE = 1~%~%uint32 type~%~%float32 pick_x~%float32 pick_y~%~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StepGoal>))
  (cl:+ 0
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ops) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StepGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'StepGoal
    (cl:cons ':max_x (max_x msg))
    (cl:cons ':max_y (max_y msg))
    (cl:cons ':ops (ops msg))
))
