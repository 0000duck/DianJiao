;; Auto-generated. Do not edit!


(when (boundp 'chess_gui::Operation)
  (if (not (find-package "CHESS_GUI"))
    (make-package "CHESS_GUI"))
  (shadow 'Operation (find-package "CHESS_GUI")))
(unless (find-package "CHESS_GUI::OPERATION")
  (make-package "CHESS_GUI::OPERATION"))

(in-package "ROS")
;;//! \htmlinclude Operation.msg.html


(intern "*OPERATION_GO*" (find-package "CHESS_GUI::OPERATION"))
(shadow '*OPERATION_GO* (find-package "CHESS_GUI::OPERATION"))
(defconstant chess_gui::Operation::*OPERATION_GO* 0)
(intern "*OPREATION_CAPTURE*" (find-package "CHESS_GUI::OPERATION"))
(shadow '*OPREATION_CAPTURE* (find-package "CHESS_GUI::OPERATION"))
(defconstant chess_gui::Operation::*OPREATION_CAPTURE* 1)
(defclass chess_gui::Operation
  :super ros::object
  :slots (_type _pick_x _pick_y _place_x _place_y ))

(defmethod chess_gui::Operation
  (:init
   (&key
    ((:type __type) 0)
    ((:pick_x __pick_x) 0.0)
    ((:pick_y __pick_y) 0.0)
    ((:place_x __place_x) 0.0)
    ((:place_y __place_y) 0.0)
    )
   (send-super :init)
   (setq _type (round __type))
   (setq _pick_x (float __pick_x))
   (setq _pick_y (float __pick_y))
   (setq _place_x (float __place_x))
   (setq _place_y (float __place_y))
   self)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:pick_x
   (&optional __pick_x)
   (if __pick_x (setq _pick_x __pick_x)) _pick_x)
  (:pick_y
   (&optional __pick_y)
   (if __pick_y (setq _pick_y __pick_y)) _pick_y)
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
    ;; float32 _pick_x
    4
    ;; float32 _pick_y
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
     ;; float32 _pick_x
       (sys::poke _pick_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pick_y
       (sys::poke _pick_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
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
   ;; float32 _pick_x
     (setq _pick_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pick_y
     (setq _pick_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _place_x
     (setq _place_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _place_y
     (setq _place_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get chess_gui::Operation :md5sum-) "046491d7b82018f3000327296ff1ce9a")
(setf (get chess_gui::Operation :datatype-) "chess_gui/Operation")
(setf (get chess_gui::Operation :definition-)
      "# operation type go = 0 ; capture = 1
uint32 OPERATION_GO = 0      
uint32 OPREATION_CAPTURE = 1

uint32 type

float32 pick_x
float32 pick_y

float32 place_x
float32 place_y


")



(provide :chess_gui/Operation "046491d7b82018f3000327296ff1ce9a")


