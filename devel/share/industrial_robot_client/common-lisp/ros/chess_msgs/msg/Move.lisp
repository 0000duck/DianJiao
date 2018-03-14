; Auto-generated. Do not edit!


(cl:in-package chess_msgs-msg)


;//! \htmlinclude Move.msg.html

(cl:defclass <Move> (roslisp-msg-protocol:ros-message)
  ((move_id
    :reader move_id
    :initarg :move_id
    :type cl:integer
    :initform 0)
   (max_x
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
    :type (cl:vector chess_msgs-msg:Operation)
   :initform (cl:make-array 0 :element-type 'chess_msgs-msg:Operation :initial-element (cl:make-instance 'chess_msgs-msg:Operation))))
)

(cl:defclass Move (<Move>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Move>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Move)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name chess_msgs-msg:<Move> is deprecated: use chess_msgs-msg:Move instead.")))

(cl:ensure-generic-function 'move_id-val :lambda-list '(m))
(cl:defmethod move_id-val ((m <Move>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-msg:move_id-val is deprecated.  Use chess_msgs-msg:move_id instead.")
  (move_id m))

(cl:ensure-generic-function 'max_x-val :lambda-list '(m))
(cl:defmethod max_x-val ((m <Move>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-msg:max_x-val is deprecated.  Use chess_msgs-msg:max_x instead.")
  (max_x m))

(cl:ensure-generic-function 'max_y-val :lambda-list '(m))
(cl:defmethod max_y-val ((m <Move>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-msg:max_y-val is deprecated.  Use chess_msgs-msg:max_y instead.")
  (max_y m))

(cl:ensure-generic-function 'ops-val :lambda-list '(m))
(cl:defmethod ops-val ((m <Move>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-msg:ops-val is deprecated.  Use chess_msgs-msg:ops instead.")
  (ops m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Move>) ostream)
  "Serializes a message object of type '<Move>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'move_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'move_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'move_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'move_id)) ostream)
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Move>) istream)
  "Deserializes a message object of type '<Move>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'move_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'move_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'move_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'move_id)) (cl:read-byte istream))
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
    (cl:setf (cl:aref vals i) (cl:make-instance 'chess_msgs-msg:Operation))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Move>)))
  "Returns string type for a message object of type '<Move>"
  "chess_msgs/Move")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Move)))
  "Returns string type for a message object of type 'Move"
  "chess_msgs/Move")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Move>)))
  "Returns md5sum for a message object of type '<Move>"
  "f0fc94b29af0de9be3ec4719172be2d4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Move)))
  "Returns md5sum for a message object of type 'Move"
  "f0fc94b29af0de9be3ec4719172be2d4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Move>)))
  "Returns full string definition for message of type '<Move>"
  (cl:format cl:nil "uint32 move_id~%~%float32 max_x~%float32 max_y~%Operation[] ops~%================================================================================~%MSG: chess_msgs/Operation~%# operation type go = 0 ; capture = 1 ; wait = 2~%uint32 OPERATION_GO = 0      ~%uint32 OPERATION_CAPTURE = 1~%uint32 OPERATION_WAIT = 2~%~%# position type far = 0; near = 1~%uint32 POSITION_FAR = 0~%uint32 POSITION_NEAR = 1~%~%uint32 type~%~%uint32  pick_type~%float32 pick_x~%float32 pick_y~%~%uint32  place_type~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Move)))
  "Returns full string definition for message of type 'Move"
  (cl:format cl:nil "uint32 move_id~%~%float32 max_x~%float32 max_y~%Operation[] ops~%================================================================================~%MSG: chess_msgs/Operation~%# operation type go = 0 ; capture = 1 ; wait = 2~%uint32 OPERATION_GO = 0      ~%uint32 OPERATION_CAPTURE = 1~%uint32 OPERATION_WAIT = 2~%~%# position type far = 0; near = 1~%uint32 POSITION_FAR = 0~%uint32 POSITION_NEAR = 1~%~%uint32 type~%~%uint32  pick_type~%float32 pick_x~%float32 pick_y~%~%uint32  place_type~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Move>))
  (cl:+ 0
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ops) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Move>))
  "Converts a ROS message object to a list"
  (cl:list 'Move
    (cl:cons ':move_id (move_id msg))
    (cl:cons ':max_x (max_x msg))
    (cl:cons ':max_y (max_y msg))
    (cl:cons ':ops (ops msg))
))
