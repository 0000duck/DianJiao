;; Auto-generated. Do not edit!


(when (boundp 'chess_msgs::Move)
  (if (not (find-package "CHESS_MSGS"))
    (make-package "CHESS_MSGS"))
  (shadow 'Move (find-package "CHESS_MSGS")))
(unless (find-package "CHESS_MSGS::MOVE")
  (make-package "CHESS_MSGS::MOVE"))

(in-package "ROS")
;;//! \htmlinclude Move.msg.html


(defclass chess_msgs::Move
  :super ros::object
  :slots (_move_id _max_x _max_y _ops ))

(defmethod chess_msgs::Move
  (:init
   (&key
    ((:move_id __move_id) 0)
    ((:max_x __max_x) 0.0)
    ((:max_y __max_y) 0.0)
    ((:ops __ops) (let (r) (dotimes (i 0) (push (instance chess_msgs::Operation :init) r)) r))
    )
   (send-super :init)
   (setq _move_id (round __move_id))
   (setq _max_x (float __max_x))
   (setq _max_y (float __max_y))
   (setq _ops __ops)
   self)
  (:move_id
   (&optional __move_id)
   (if __move_id (setq _move_id __move_id)) _move_id)
  (:max_x
   (&optional __max_x)
   (if __max_x (setq _max_x __max_x)) _max_x)
  (:max_y
   (&optional __max_y)
   (if __max_y (setq _max_y __max_y)) _max_y)
  (:ops
   (&rest __ops)
   (if (keywordp (car __ops))
       (send* _ops __ops)
     (progn
       (if __ops (setq _ops (car __ops)))
       _ops)))
  (:serialization-length
   ()
   (+
    ;; uint32 _move_id
    4
    ;; float32 _max_x
    4
    ;; float32 _max_y
    4
    ;; chess_msgs/Operation[] _ops
    (apply #'+ (send-all _ops :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _move_id
       (write-long _move_id s)
     ;; float32 _max_x
       (sys::poke _max_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _max_y
       (sys::poke _max_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; chess_msgs/Operation[] _ops
     (write-long (length _ops) s)
     (dolist (elem _ops)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _move_id
     (setq _move_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _max_x
     (setq _max_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _max_y
     (setq _max_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; chess_msgs/Operation[] _ops
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ops (let (r) (dotimes (i n) (push (instance chess_msgs::Operation :init) r)) r))
     (dolist (elem- _ops)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get chess_msgs::Move :md5sum-) "f0fc94b29af0de9be3ec4719172be2d4")
(setf (get chess_msgs::Move :datatype-) "chess_msgs/Move")
(setf (get chess_msgs::Move :definition-)
      "uint32 move_id

float32 max_x
float32 max_y
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


")



(provide :chess_msgs/Move "f0fc94b29af0de9be3ec4719172be2d4")


