; Auto-generated. Do not edit!


(cl:in-package chess_msgs-srv)


;//! \htmlinclude Play-request.msg.html

(cl:defclass <Play-request> (roslisp-msg-protocol:ros-message)
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
    :type (cl:vector chess_msgs-msg:Operation)
   :initform (cl:make-array 0 :element-type 'chess_msgs-msg:Operation :initial-element (cl:make-instance 'chess_msgs-msg:Operation))))
)

(cl:defclass Play-request (<Play-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Play-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Play-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name chess_msgs-srv:<Play-request> is deprecated: use chess_msgs-srv:Play-request instead.")))

(cl:ensure-generic-function 'max_x-val :lambda-list '(m))
(cl:defmethod max_x-val ((m <Play-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-srv:max_x-val is deprecated.  Use chess_msgs-srv:max_x instead.")
  (max_x m))

(cl:ensure-generic-function 'max_y-val :lambda-list '(m))
(cl:defmethod max_y-val ((m <Play-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-srv:max_y-val is deprecated.  Use chess_msgs-srv:max_y instead.")
  (max_y m))

(cl:ensure-generic-function 'ops-val :lambda-list '(m))
(cl:defmethod ops-val ((m <Play-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-srv:ops-val is deprecated.  Use chess_msgs-srv:ops instead.")
  (ops m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Play-request>) ostream)
  "Serializes a message object of type '<Play-request>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Play-request>) istream)
  "Deserializes a message object of type '<Play-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Play-request>)))
  "Returns string type for a service object of type '<Play-request>"
  "chess_msgs/PlayRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Play-request)))
  "Returns string type for a service object of type 'Play-request"
  "chess_msgs/PlayRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Play-request>)))
  "Returns md5sum for a message object of type '<Play-request>"
  "9ca8bd096976365b8f806f82ceddea70")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Play-request)))
  "Returns md5sum for a message object of type 'Play-request"
  "9ca8bd096976365b8f806f82ceddea70")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Play-request>)))
  "Returns full string definition for message of type '<Play-request>"
  (cl:format cl:nil "~%float32 max_x~%float32 max_y~%Operation[] ops~%~%================================================================================~%MSG: chess_msgs/Operation~%# operation type go = 0 ; capture = 1 ; wait = 2~%uint32 OPERATION_GO = 0      ~%uint32 OPERATION_CAPTURE = 1~%uint32 OPERATION_WAIT = 2~%~%# position type far = 0; near = 1~%uint32 POSITION_FAR = 0~%uint32 POSITION_NEAR = 1~%~%uint32 type~%~%uint32  pick_type~%float32 pick_x~%float32 pick_y~%~%uint32  place_type~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Play-request)))
  "Returns full string definition for message of type 'Play-request"
  (cl:format cl:nil "~%float32 max_x~%float32 max_y~%Operation[] ops~%~%================================================================================~%MSG: chess_msgs/Operation~%# operation type go = 0 ; capture = 1 ; wait = 2~%uint32 OPERATION_GO = 0      ~%uint32 OPERATION_CAPTURE = 1~%uint32 OPERATION_WAIT = 2~%~%# position type far = 0; near = 1~%uint32 POSITION_FAR = 0~%uint32 POSITION_NEAR = 1~%~%uint32 type~%~%uint32  pick_type~%float32 pick_x~%float32 pick_y~%~%uint32  place_type~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Play-request>))
  (cl:+ 0
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ops) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Play-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Play-request
    (cl:cons ':max_x (max_x msg))
    (cl:cons ':max_y (max_y msg))
    (cl:cons ':ops (ops msg))
))
;//! \htmlinclude Play-response.msg.html

(cl:defclass <Play-response> (roslisp-msg-protocol:ros-message)
  ((res
    :reader res
    :initarg :res
    :type cl:boolean
    :initform cl:nil)
   (msg
    :reader msg
    :initarg :msg
    :type cl:string
    :initform ""))
)

(cl:defclass Play-response (<Play-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Play-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Play-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name chess_msgs-srv:<Play-response> is deprecated: use chess_msgs-srv:Play-response instead.")))

(cl:ensure-generic-function 'res-val :lambda-list '(m))
(cl:defmethod res-val ((m <Play-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-srv:res-val is deprecated.  Use chess_msgs-srv:res instead.")
  (res m))

(cl:ensure-generic-function 'msg-val :lambda-list '(m))
(cl:defmethod msg-val ((m <Play-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-srv:msg-val is deprecated.  Use chess_msgs-srv:msg instead.")
  (msg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Play-response>) ostream)
  "Serializes a message object of type '<Play-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'res) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'msg))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'msg))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Play-response>) istream)
  "Deserializes a message object of type '<Play-response>"
    (cl:setf (cl:slot-value msg 'res) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'msg) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'msg) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Play-response>)))
  "Returns string type for a service object of type '<Play-response>"
  "chess_msgs/PlayResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Play-response)))
  "Returns string type for a service object of type 'Play-response"
  "chess_msgs/PlayResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Play-response>)))
  "Returns md5sum for a message object of type '<Play-response>"
  "9ca8bd096976365b8f806f82ceddea70")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Play-response)))
  "Returns md5sum for a message object of type 'Play-response"
  "9ca8bd096976365b8f806f82ceddea70")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Play-response>)))
  "Returns full string definition for message of type '<Play-response>"
  (cl:format cl:nil "~%bool res~%string msg~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Play-response)))
  "Returns full string definition for message of type 'Play-response"
  (cl:format cl:nil "~%bool res~%string msg~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Play-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'msg))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Play-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Play-response
    (cl:cons ':res (res msg))
    (cl:cons ':msg (msg msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Play)))
  'Play-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Play)))
  'Play-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Play)))
  "Returns string type for a service object of type '<Play>"
  "chess_msgs/Play")