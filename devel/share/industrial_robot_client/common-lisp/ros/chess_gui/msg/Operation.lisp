; Auto-generated. Do not edit!


(cl:in-package chess_gui-msg)


;//! \htmlinclude Operation.msg.html

(cl:defclass <Operation> (roslisp-msg-protocol:ros-message)
  ((type
    :reader type
    :initarg :type
    :type cl:integer
    :initform 0)
   (pick_x
    :reader pick_x
    :initarg :pick_x
    :type cl:float
    :initform 0.0)
   (pick_y
    :reader pick_y
    :initarg :pick_y
    :type cl:float
    :initform 0.0)
   (place_x
    :reader place_x
    :initarg :place_x
    :type cl:float
    :initform 0.0)
   (place_y
    :reader place_y
    :initarg :place_y
    :type cl:float
    :initform 0.0))
)

(cl:defclass Operation (<Operation>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Operation>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Operation)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name chess_gui-msg:<Operation> is deprecated: use chess_gui-msg:Operation instead.")))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <Operation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_gui-msg:type-val is deprecated.  Use chess_gui-msg:type instead.")
  (type m))

(cl:ensure-generic-function 'pick_x-val :lambda-list '(m))
(cl:defmethod pick_x-val ((m <Operation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_gui-msg:pick_x-val is deprecated.  Use chess_gui-msg:pick_x instead.")
  (pick_x m))

(cl:ensure-generic-function 'pick_y-val :lambda-list '(m))
(cl:defmethod pick_y-val ((m <Operation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_gui-msg:pick_y-val is deprecated.  Use chess_gui-msg:pick_y instead.")
  (pick_y m))

(cl:ensure-generic-function 'place_x-val :lambda-list '(m))
(cl:defmethod place_x-val ((m <Operation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_gui-msg:place_x-val is deprecated.  Use chess_gui-msg:place_x instead.")
  (place_x m))

(cl:ensure-generic-function 'place_y-val :lambda-list '(m))
(cl:defmethod place_y-val ((m <Operation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_gui-msg:place_y-val is deprecated.  Use chess_gui-msg:place_y instead.")
  (place_y m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<Operation>)))
    "Constants for message type '<Operation>"
  '((:OPERATION_GO . 0)
    (:OPREATION_CAPTURE . 1))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'Operation)))
    "Constants for message type 'Operation"
  '((:OPERATION_GO . 0)
    (:OPREATION_CAPTURE . 1))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Operation>) ostream)
  "Serializes a message object of type '<Operation>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'type)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pick_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pick_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'place_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'place_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Operation>) istream)
  "Deserializes a message object of type '<Operation>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'type)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pick_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pick_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'place_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'place_y) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Operation>)))
  "Returns string type for a message object of type '<Operation>"
  "chess_gui/Operation")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Operation)))
  "Returns string type for a message object of type 'Operation"
  "chess_gui/Operation")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Operation>)))
  "Returns md5sum for a message object of type '<Operation>"
  "046491d7b82018f3000327296ff1ce9a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Operation)))
  "Returns md5sum for a message object of type 'Operation"
  "046491d7b82018f3000327296ff1ce9a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Operation>)))
  "Returns full string definition for message of type '<Operation>"
  (cl:format cl:nil "# operation type go = 0 ; capture = 1~%uint32 OPERATION_GO = 0      ~%uint32 OPREATION_CAPTURE = 1~%~%uint32 type~%~%float32 pick_x~%float32 pick_y~%~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Operation)))
  "Returns full string definition for message of type 'Operation"
  (cl:format cl:nil "# operation type go = 0 ; capture = 1~%uint32 OPERATION_GO = 0      ~%uint32 OPREATION_CAPTURE = 1~%~%uint32 type~%~%float32 pick_x~%float32 pick_y~%~%float32 place_x~%float32 place_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Operation>))
  (cl:+ 0
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Operation>))
  "Converts a ROS message object to a list"
  (cl:list 'Operation
    (cl:cons ':type (type msg))
    (cl:cons ':pick_x (pick_x msg))
    (cl:cons ':pick_y (pick_y msg))
    (cl:cons ':place_x (place_x msg))
    (cl:cons ':place_y (place_y msg))
))
