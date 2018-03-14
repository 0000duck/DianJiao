; Auto-generated. Do not edit!


(cl:in-package chess_msgs-msg)


;//! \htmlinclude Zpose.msg.html

(cl:defclass <Zpose> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (z
    :reader z
    :initarg :z
    :type cl:float
    :initform 0.0)
   (r
    :reader r
    :initarg :r
    :type cl:float
    :initform 0.0))
)

(cl:defclass Zpose (<Zpose>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Zpose>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Zpose)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name chess_msgs-msg:<Zpose> is deprecated: use chess_msgs-msg:Zpose instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <Zpose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-msg:x-val is deprecated.  Use chess_msgs-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <Zpose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-msg:y-val is deprecated.  Use chess_msgs-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <Zpose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-msg:z-val is deprecated.  Use chess_msgs-msg:z instead.")
  (z m))

(cl:ensure-generic-function 'r-val :lambda-list '(m))
(cl:defmethod r-val ((m <Zpose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-msg:r-val is deprecated.  Use chess_msgs-msg:r instead.")
  (r m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Zpose>) ostream)
  "Serializes a message object of type '<Zpose>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'r))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Zpose>) istream)
  "Deserializes a message object of type '<Zpose>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'r) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Zpose>)))
  "Returns string type for a message object of type '<Zpose>"
  "chess_msgs/Zpose")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Zpose)))
  "Returns string type for a message object of type 'Zpose"
  "chess_msgs/Zpose")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Zpose>)))
  "Returns md5sum for a message object of type '<Zpose>"
  "cc13c46bdf00e218620490fb1dd05090")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Zpose)))
  "Returns md5sum for a message object of type 'Zpose"
  "cc13c46bdf00e218620490fb1dd05090")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Zpose>)))
  "Returns full string definition for message of type '<Zpose>"
  (cl:format cl:nil "float32 x~%float32 y~%float32 z~%float32 r~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Zpose)))
  "Returns full string definition for message of type 'Zpose"
  (cl:format cl:nil "float32 x~%float32 y~%float32 z~%float32 r~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Zpose>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Zpose>))
  "Converts a ROS message object to a list"
  (cl:list 'Zpose
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
    (cl:cons ':r (r msg))
))
