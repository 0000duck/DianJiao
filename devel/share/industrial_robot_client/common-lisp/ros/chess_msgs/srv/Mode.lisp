; Auto-generated. Do not edit!


(cl:in-package chess_msgs-srv)


;//! \htmlinclude Mode-request.msg.html

(cl:defclass <Mode-request> (roslisp-msg-protocol:ros-message)
  ((manual
    :reader manual
    :initarg :manual
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Mode-request (<Mode-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Mode-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Mode-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name chess_msgs-srv:<Mode-request> is deprecated: use chess_msgs-srv:Mode-request instead.")))

(cl:ensure-generic-function 'manual-val :lambda-list '(m))
(cl:defmethod manual-val ((m <Mode-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-srv:manual-val is deprecated.  Use chess_msgs-srv:manual instead.")
  (manual m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Mode-request>) ostream)
  "Serializes a message object of type '<Mode-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'manual) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Mode-request>) istream)
  "Deserializes a message object of type '<Mode-request>"
    (cl:setf (cl:slot-value msg 'manual) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Mode-request>)))
  "Returns string type for a service object of type '<Mode-request>"
  "chess_msgs/ModeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Mode-request)))
  "Returns string type for a service object of type 'Mode-request"
  "chess_msgs/ModeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Mode-request>)))
  "Returns md5sum for a message object of type '<Mode-request>"
  "4d287144922458715666bf59b49316da")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Mode-request)))
  "Returns md5sum for a message object of type 'Mode-request"
  "4d287144922458715666bf59b49316da")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Mode-request>)))
  "Returns full string definition for message of type '<Mode-request>"
  (cl:format cl:nil "~%bool manual~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Mode-request)))
  "Returns full string definition for message of type 'Mode-request"
  (cl:format cl:nil "~%bool manual~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Mode-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Mode-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Mode-request
    (cl:cons ':manual (manual msg))
))
;//! \htmlinclude Mode-response.msg.html

(cl:defclass <Mode-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:integer
    :initform 0))
)

(cl:defclass Mode-response (<Mode-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Mode-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Mode-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name chess_msgs-srv:<Mode-response> is deprecated: use chess_msgs-srv:Mode-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <Mode-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader chess_msgs-srv:result-val is deprecated.  Use chess_msgs-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Mode-response>) ostream)
  "Serializes a message object of type '<Mode-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'result)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'result)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'result)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Mode-response>) istream)
  "Deserializes a message object of type '<Mode-response>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'result)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'result)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'result)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Mode-response>)))
  "Returns string type for a service object of type '<Mode-response>"
  "chess_msgs/ModeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Mode-response)))
  "Returns string type for a service object of type 'Mode-response"
  "chess_msgs/ModeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Mode-response>)))
  "Returns md5sum for a message object of type '<Mode-response>"
  "4d287144922458715666bf59b49316da")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Mode-response)))
  "Returns md5sum for a message object of type 'Mode-response"
  "4d287144922458715666bf59b49316da")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Mode-response>)))
  "Returns full string definition for message of type '<Mode-response>"
  (cl:format cl:nil "~%uint32 result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Mode-response)))
  "Returns full string definition for message of type 'Mode-response"
  (cl:format cl:nil "~%uint32 result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Mode-response>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Mode-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Mode-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Mode)))
  'Mode-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Mode)))
  'Mode-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Mode)))
  "Returns string type for a service object of type '<Mode>"
  "chess_msgs/Mode")