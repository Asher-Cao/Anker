
(cl:in-package :asdf)

(defsystem "anker_ekf_pro-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "AnkerDataType" :depends-on ("_package_AnkerDataType"))
    (:file "_package_AnkerDataType" :depends-on ("_package"))
  ))