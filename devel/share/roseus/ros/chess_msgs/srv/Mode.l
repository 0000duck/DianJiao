;; Auto-generated. Do not edit!


(when (boundp 'chess_msgs::Mode)
  (if (not (find-package "CHESS_MSGS"))
    (make-package "CHESS_MSGS"))
  (shadow 'Mode (find-package "CHESS_MSGS")))
(unless (find-package "CHESS_MSGS::MODE")
  (make-package "CHESS_MSGS::MODE"))
(unless (find-package "CHESS_MSGS::MODEREQUEST")
  (make-package "CHESS_MSGS::MODEREQUEST"))
(unless (find-package "CHESS_MSGS::MODERESPONSE")
  (make-package "CHESS_MSGS::MODERESPONSE"))

(in-package "ROS")





(defclass chess_msgs::ModeRequest
  :super ros::object
  :slots (_manual ))

(defmethod chess_msgs::ModeRequest
  (:init
   (&key
    ((:manual __manual) nil)
    )
   (send-super :init)
   (setq _manual __manual)
   self)
  (:manual
   (&optional __manual)
   (if __manual (setq _manual __manual)) _manual)
  (:serialization-length
   ()
   (+
    ;; bool _manual
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _manual
       (if _manual (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _manual
     (setq _manual (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass chess_msgs::ModeResponse
  :super ros::object
  :slots (_result ))

(defmethod chess_msgs::ModeResponse
  (:init
   (&key
    ((:result __result) 0)
    )
   (send-super :init)
   (setq _result (round __result))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; uint32 _result
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _result
       (write-long _result s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _result
     (setq _result (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass chess_msgs::Mode
  :super ros::object
  :slots ())

(setf (get chess_msgs::Mode :md5sum-) "4d287144922458715666bf59b49316da")
(setf (get chess_msgs::Mode :datatype-) "chess_msgs/Mode")
(setf (get chess_msgs::Mode :request) chess_msgs::ModeRequest)
(setf (get chess_msgs::Mode :response) chess_msgs::ModeResponse)

(defmethod chess_msgs::ModeRequest
  (:response () (instance chess_msgs::ModeResponse :init)))

(setf (get chess_msgs::ModeRequest :md5sum-) "4d287144922458715666bf59b49316da")
(setf (get chess_msgs::ModeRequest :datatype-) "chess_msgs/ModeRequest")
(setf (get chess_msgs::ModeRequest :definition-)
      "
bool manual
---

uint32 result
")

(setf (get chess_msgs::ModeResponse :md5sum-) "4d287144922458715666bf59b49316da")
(setf (get chess_msgs::ModeResponse :datatype-) "chess_msgs/ModeResponse")
(setf (get chess_msgs::ModeResponse :definition-)
      "
bool manual
---

uint32 result
")



(provide :chess_msgs/Mode "4d287144922458715666bf59b49316da")


