;; Auto-generated. Do not edit!


(when (boundp 'chess_msgs::Operation)
  (if (not (find-package "CHESS_MSGS"))
    (make-package "CHESS_MSGS"))
  (shadow 'Operation (find-package "CHESS_MSGS")))
(unless (find-package "CHESS_MSGS::OPERATION")
  (make-package "CHESS_MSGS::OPERATION"))

(in-package "ROS")
;;//! \htmlinclude Operation.msg.html


(intern "*OPERATION_GO*" (find-package "CHESS_MSGS::OPERATION"))
(shadow '*OPERATION_GO* (find-package "CHESS_MSGS::OPERATION"))
(defconstant chess_msgs::Operation::*OPERATION_GO* 0)
(intern "*OPERATION_CAPTURE*" (find-package "CHESS_MSGS::OPERATION"))
(shadow '*OPERATION_CAPTURE* (find-package "CHESS_MSGS::OPERATION"))
(defconstant chess_msgs::Operation::*OPERATION_CAPTURE* 1)
(intern "*OPERATION_WAIT*" (find-package "CHESS_MSGS::OPERATION"))
(shadow '*OPERATION_WAIT* (find-package "CHESS_MSGS::OPERATION"))
(defconstant chess_msgs::Operation::*OPERATION_WAIT* 2)
(intern "*POSITION_FAR*" (find-package "CHESS_MSGS::OPERATION"))
(shadow '*POSITION_FAR* (find-package "CHESS_MSGS::OPERATION"))
(defconstant chess_msgs::Operation::*POSITION_FAR* 0)
(intern "*POSITION_NEAR*" (find-package "CHESS_MSGS::OPERATION"))
(shadow '*POSITION_NEAR* (find-package "CHESS_MSGS::OPERATION"))
(defconstant chess_msgs::Operation::*POSITION_NEAR* 1)
(defclass chess_msgs::Operation
  :super ros::object
  :slots (_type _pick_type _pick_x _pick_y _place_type _place_x _place_y ))

(defmethod chess_msgs::Operation
  (:init
   (&key
    ((:type __type) 0)
    ((:pick_type __pick_type) 0)
    ((:pick_x __pick_x) 0.0)
    ((:pick_y __pick_y) 0.0)
    ((:place_type __place_type) 0)
    ((:place_x __place_x) 0.0)
    ((:place_y __place_y) 0.0)
    )
   (send-super :init)
   (setq _type (round __type))
   (setq _pick_type (round __pick_type))
   (setq _pick_x (float __pick_x))
   (setq _pick_y (float __pick_y))
   (setq _place_type (round __place_type))
   (setq _place_x (float __place_x))
   (setq _place_y (float __place_y))
   self)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:pick_type
   (&optional __pick_type)
   (if __pick_type (setq _pick_type __pick_type)) _pick_type)
  (:pick_x
   (&optional __pick_x)
   (if __pick_x (setq _pick_x __pick_x)) _pick_x)
  (:pick_y
   (&optional __pick_y)
   (if __pick_y (setq _pick_y __pick_y)) _pick_y)
  (:place_type
   (&optional __place_type)
   (if __place_type (setq _place_type __place_type)) _place_type)
  (:place_x
   (&optional __place_x)
   (if __place_x (setq _place_x __place_x)) _place_x)
  (:place_y
   (&optional __place_y)
   (if __place_y (setq _place_y __place_y)) _place_y)
  (:serialization-length
   ()
   (+
    ;; uint32 _type
    4
    ;; uint32 _pick_type
    4
    ;; float32 _pick_x
    4
    ;; float32 _pick_y
    4
    ;; uint32 _place_type
    4
    ;; float32 _place_x
    4
    ;; float32 _place_y
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _type
       (write-long _type s)
     ;; uint32 _pick_type
       (write-long _pick_type s)
     ;; float32 _pick_x
       (sys::poke _pick_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pick_y
       (sys::poke _pick_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint32 _place_type
       (write-long _place_type s)
     ;; float32 _place_x
       (sys::poke _place_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _place_y
       (sys::poke _place_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _type
     (setq _type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _pick_type
     (setq _pick_type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _pick_x
     (setq _pick_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pick_y
     (setq _pick_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _place_type
     (setq _place_type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _place_x
     (setq _place_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _place_y
     (setq _place_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get chess_msgs::Operation :md5sum-) "61d4fe1d5f316be10b485597893ba6de")
(setf (get chess_msgs::Operation :datatype-) "chess_msgs/Operation")
(setf (get chess_msgs::Operation :definition-)
      "# operation type go = 0 ; capture = 1 ; wait = 2
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


")



(provide :chess_msgs/Operation "61d4fe1d5f316be10b485597893ba6de")


