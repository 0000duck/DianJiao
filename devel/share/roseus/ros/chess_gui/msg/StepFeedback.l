;; Auto-generated. Do not edit!


(when (boundp 'chess_gui::StepFeedback)
  (if (not (find-package "CHESS_GUI"))
    (make-package "CHESS_GUI"))
  (shadow 'StepFeedback (find-package "CHESS_GUI")))
(unless (find-package "CHESS_GUI::STEPFEEDBACK")
  (make-package "CHESS_GUI::STEPFEEDBACK"))

(in-package "ROS")
;;//! \htmlinclude StepFeedback.msg.html


(defclass chess_gui::StepFeedback
  :super ros::object
  :slots (_feedback ))

(defmethod chess_gui::StepFeedback
  (:init
   (&key
    ((:feedback __feedback) "")
    )
   (send-super :init)
   (setq _feedback (string __feedback))
   self)
  (:feedback
   (&optional __feedback)
   (if __feedback (setq _feedback __feedback)) _feedback)
  (:serialization-length
   ()
   (+
    ;; string _feedback
    4 (length _feedback)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _feedback
       (write-long (length _feedback) s) (princ _feedback s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _feedback
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _feedback (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get chess_gui::StepFeedback :md5sum-) "c14cdf907e5c7c7fd47292add15660f0")
(setf (get chess_gui::StepFeedback :datatype-) "chess_gui/StepFeedback")
(setf (get chess_gui::StepFeedback :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# feedback definition
string feedback

")



(provide :chess_gui/StepFeedback "c14cdf907e5c7c7fd47292add15660f0")


