
(cl:in-package :asdf)

(defsystem "chess_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :chess_msgs-msg
)
  :components ((:file "_package")
    (:file "Mode" :depends-on ("_package_Mode"))
    (:file "_package_Mode" :depends-on ("_package"))
    (:file "Play" :depends-on ("_package_Play"))
    (:file "_package_Play" :depends-on ("_package"))
    (:file "Point" :depends-on ("_package_Point"))
    (:file "_package_Point" :depends-on ("_package"))
  ))