;; Auto-generated. Do not edit!


(when (boundp 'chess_msgs::Result)
  (if (not (find-package "CHESS_MSGS"))
    (make-package "CHESS_MSGS"))
  (shadow 'Result (find-package "CHESS_MSGS")))
(unless (find-package "CHESS_MSGS::RESULT")
  (make-package "CHESS_MSGS::RESULT"))

(in-package "ROS")
;;//! \htmlinclude Result.msg.html


(defclass chess_msgs::Result
  :super ros::object
  :slots (_move_id _res _msg ))

(defmethod chess_msgs::Result
  (:init
   (&key
    ((:move_id __move_id) 0)
    ((:res __res) nil)
    ((:msg __msg) "")
    )
   (send-super :init)
   (setq _move_id (round __move_id))
   (setq _res __res)
   (setq _msg (string __msg))
   self)
  (:move_id
   (&optional __move_id)
   (if __move_id (setq _move_id __move_id)) _move_id)
  (:res
   (&optional __res)
   (if __res (setq _res __res)) _res)
  (:msg
   (&optional __msg)
   (if __msg (setq _msg __msg)) _msg)
  (:serialization-length
   ()
   (+
    ;; uint32 _move_id
    4
    ;; bool _res
    1
    ;; string _msg
    4 (length _msg)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _move_id
       (write-long _move_id s)
     ;; bool _res
       (if _res (write-byte -1 s) (write-byte 0 s))
     ;; string _msg
       (write-long (length _msg) s) (princ _msg s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _move_id
     (setq _move_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _res
     (setq _res (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _msg
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _msg (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get chess_msgs::Result :md5sum-) "ae465118b1a9be7edaa0ca21933a04d1")
(setf (get chess_msgs::Result :datatype-) "chess_msgs/Result")
(setf (get chess_msgs::Result :definition-)
      "uint32 move_id

bool res
string msg
")



(provide :chess_msgs/Result "ae465118b1a9be7edaa0ca21933a04d1")


