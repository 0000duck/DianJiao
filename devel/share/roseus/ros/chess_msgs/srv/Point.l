;; Auto-generated. Do not edit!


(when (boundp 'chess_msgs::Point)
  (if (not (find-package "CHESS_MSGS"))
    (make-package "CHESS_MSGS"))
  (shadow 'Point (find-package "CHESS_MSGS")))
(unless (find-package "CHESS_MSGS::POINT")
  (make-package "CHESS_MSGS::POINT"))
(unless (find-package "CHESS_MSGS::POINTREQUEST")
  (make-package "CHESS_MSGS::POINTREQUEST"))
(unless (find-package "CHESS_MSGS::POINTRESPONSE")
  (make-package "CHESS_MSGS::POINTRESPONSE"))

(in-package "ROS")





(defclass chess_msgs::PointRequest
  :super ros::object
  :slots ())

(defmethod chess_msgs::PointRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass chess_msgs::PointResponse
  :super ros::object
  :slots (_x _y ))

(defmethod chess_msgs::PointResponse
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass chess_msgs::Point
  :super ros::object
  :slots ())

(setf (get chess_msgs::Point :md5sum-) "ff8d7d66dd3e4b731ef14a45d38888b6")
(setf (get chess_msgs::Point :datatype-) "chess_msgs/Point")
(setf (get chess_msgs::Point :request) chess_msgs::PointRequest)
(setf (get chess_msgs::Point :response) chess_msgs::PointResponse)

(defmethod chess_msgs::PointRequest
  (:response () (instance chess_msgs::PointResponse :init)))

(setf (get chess_msgs::PointRequest :md5sum-) "ff8d7d66dd3e4b731ef14a45d38888b6")
(setf (get chess_msgs::PointRequest :datatype-) "chess_msgs/PointRequest")
(setf (get chess_msgs::PointRequest :definition-)
      "

---

float32 x
float32 y
")

(setf (get chess_msgs::PointResponse :md5sum-) "ff8d7d66dd3e4b731ef14a45d38888b6")
(setf (get chess_msgs::PointResponse :datatype-) "chess_msgs/PointResponse")
(setf (get chess_msgs::PointResponse :definition-)
      "

---

float32 x
float32 y
")



(provide :chess_msgs/Point "ff8d7d66dd3e4b731ef14a45d38888b6")


