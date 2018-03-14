;; Auto-generated. Do not edit!


(when (boundp 'chess_msgs::Play)
  (if (not (find-package "CHESS_MSGS"))
    (make-package "CHESS_MSGS"))
  (shadow 'Play (find-package "CHESS_MSGS")))
(unless (find-package "CHESS_MSGS::PLAY")
  (make-package "CHESS_MSGS::PLAY"))
(unless (find-package "CHESS_MSGS::PLAYREQUEST")
  (make-package "CHESS_MSGS::PLAYREQUEST"))
(unless (find-package "CHESS_MSGS::PLAYRESPONSE")
  (make-package "CHESS_MSGS::PLAYRESPONSE"))

(in-package "ROS")





(defclass chess_msgs::PlayRequest
  :super ros::object
  :slots (_max_x _max_y _ops ))

(defmethod chess_msgs::PlayRequest
  (:init
   (&key
    ((:max_x __max_x) 0.0)
    ((:max_y __max_y) 0.0)
    ((:ops __ops) (let (r) (dotimes (i 0) (push (instance chess_msgs::Operation :init) r)) r))
    )
   (send-super :init)
   (setq _max_x (float __max_x))
   (setq _max_y (float __max_y))
   (setq _ops __ops)
   self)
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

(defclass chess_msgs::PlayResponse
  :super ros::object
  :slots (_res _msg ))

(defmethod chess_msgs::PlayResponse
  (:init
   (&key
    ((:res __res) nil)
    ((:msg __msg) "")
    )
   (send-super :init)
   (setq _res __res)
   (setq _msg (string __msg))
   self)
  (:res
   (&optional __res)
   (if __res (setq _res __res)) _res)
  (:msg
   (&optional __msg)
   (if __msg (setq _msg __msg)) _msg)
  (:serialization-length
   ()
   (+
    ;; bool _res
    1
    ;; string _msg
    4 (length _msg)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _res
       (if _res (write-byte -1 s) (write-byte 0 s))
     ;; string _msg
       (write-long (length _msg) s) (princ _msg s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _res
     (setq _res (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _msg
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _msg (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass chess_msgs::Play
  :super ros::object
  :slots ())

(setf (get chess_msgs::Play :md5sum-) "9ca8bd096976365b8f806f82ceddea70")
(setf (get chess_msgs::Play :datatype-) "chess_msgs/Play")
(setf (get chess_msgs::Play :request) chess_msgs::PlayRequest)
(setf (get chess_msgs::Play :response) chess_msgs::PlayResponse)

(defmethod chess_msgs::PlayRequest
  (:response () (instance chess_msgs::PlayResponse :init)))

(setf (get chess_msgs::PlayRequest :md5sum-) "9ca8bd096976365b8f806f82ceddea70")
(setf (get chess_msgs::PlayRequest :datatype-) "chess_msgs/PlayRequest")
(setf (get chess_msgs::PlayRequest :definition-)
      "
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

---

bool res
string msg
")

(setf (get chess_msgs::PlayResponse :md5sum-) "9ca8bd096976365b8f806f82ceddea70")
(setf (get chess_msgs::PlayResponse :datatype-) "chess_msgs/PlayResponse")
(setf (get chess_msgs::PlayResponse :definition-)
      "
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

---

bool res
string msg
")



(provide :chess_msgs/Play "9ca8bd096976365b8f806f82ceddea70")


