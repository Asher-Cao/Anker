; Auto-generated. Do not edit!


(cl:in-package anker_data_publish-msg)


;//! \htmlinclude AnkerDataType.msg.html

(cl:defclass <AnkerDataType> (roslisp-msg-protocol:ros-message)
  ((time_s
    :reader time_s
    :initarg :time_s
    :type cl:float
    :initform 0.0)
   (gx
    :reader gx
    :initarg :gx
    :type cl:float
    :initform 0.0)
   (gy
    :reader gy
    :initarg :gy
    :type cl:float
    :initform 0.0)
   (gz
    :reader gz
    :initarg :gz
    :type cl:float
    :initform 0.0)
   (ax
    :reader ax
    :initarg :ax
    :type cl:float
    :initform 0.0)
   (ay
    :reader ay
    :initarg :ay
    :type cl:float
    :initform 0.0)
   (az
    :reader az
    :initarg :az
    :type cl:float
    :initform 0.0)
   (odo_right_pos
    :reader odo_right_pos
    :initarg :odo_right_pos
    :type cl:float
    :initform 0.0)
   (odo_left_pos
    :reader odo_left_pos
    :initarg :odo_left_pos
    :type cl:float
    :initform 0.0)
   (odo_right_vel
    :reader odo_right_vel
    :initarg :odo_right_vel
    :type cl:float
    :initform 0.0)
   (odo_left_vel
    :reader odo_left_vel
    :initarg :odo_left_vel
    :type cl:float
    :initform 0.0)
   (opt_pos_x
    :reader opt_pos_x
    :initarg :opt_pos_x
    :type cl:float
    :initform 0.0)
   (opt_pos_y
    :reader opt_pos_y
    :initarg :opt_pos_y
    :type cl:float
    :initform 0.0)
   (opt_quality
    :reader opt_quality
    :initarg :opt_quality
    :type cl:fixnum
    :initform 0)
   (wall_distance_right
    :reader wall_distance_right
    :initarg :wall_distance_right
    :type cl:fixnum
    :initform 0)
   (wall_distance_left
    :reader wall_distance_left
    :initarg :wall_distance_left
    :type cl:fixnum
    :initform 0))
)

(cl:defclass AnkerDataType (<AnkerDataType>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AnkerDataType>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AnkerDataType)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name anker_data_publish-msg:<AnkerDataType> is deprecated: use anker_data_publish-msg:AnkerDataType instead.")))

(cl:ensure-generic-function 'time_s-val :lambda-list '(m))
(cl:defmethod time_s-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:time_s-val is deprecated.  Use anker_data_publish-msg:time_s instead.")
  (time_s m))

(cl:ensure-generic-function 'gx-val :lambda-list '(m))
(cl:defmethod gx-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:gx-val is deprecated.  Use anker_data_publish-msg:gx instead.")
  (gx m))

(cl:ensure-generic-function 'gy-val :lambda-list '(m))
(cl:defmethod gy-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:gy-val is deprecated.  Use anker_data_publish-msg:gy instead.")
  (gy m))

(cl:ensure-generic-function 'gz-val :lambda-list '(m))
(cl:defmethod gz-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:gz-val is deprecated.  Use anker_data_publish-msg:gz instead.")
  (gz m))

(cl:ensure-generic-function 'ax-val :lambda-list '(m))
(cl:defmethod ax-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:ax-val is deprecated.  Use anker_data_publish-msg:ax instead.")
  (ax m))

(cl:ensure-generic-function 'ay-val :lambda-list '(m))
(cl:defmethod ay-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:ay-val is deprecated.  Use anker_data_publish-msg:ay instead.")
  (ay m))

(cl:ensure-generic-function 'az-val :lambda-list '(m))
(cl:defmethod az-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:az-val is deprecated.  Use anker_data_publish-msg:az instead.")
  (az m))

(cl:ensure-generic-function 'odo_right_pos-val :lambda-list '(m))
(cl:defmethod odo_right_pos-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:odo_right_pos-val is deprecated.  Use anker_data_publish-msg:odo_right_pos instead.")
  (odo_right_pos m))

(cl:ensure-generic-function 'odo_left_pos-val :lambda-list '(m))
(cl:defmethod odo_left_pos-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:odo_left_pos-val is deprecated.  Use anker_data_publish-msg:odo_left_pos instead.")
  (odo_left_pos m))

(cl:ensure-generic-function 'odo_right_vel-val :lambda-list '(m))
(cl:defmethod odo_right_vel-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:odo_right_vel-val is deprecated.  Use anker_data_publish-msg:odo_right_vel instead.")
  (odo_right_vel m))

(cl:ensure-generic-function 'odo_left_vel-val :lambda-list '(m))
(cl:defmethod odo_left_vel-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:odo_left_vel-val is deprecated.  Use anker_data_publish-msg:odo_left_vel instead.")
  (odo_left_vel m))

(cl:ensure-generic-function 'opt_pos_x-val :lambda-list '(m))
(cl:defmethod opt_pos_x-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:opt_pos_x-val is deprecated.  Use anker_data_publish-msg:opt_pos_x instead.")
  (opt_pos_x m))

(cl:ensure-generic-function 'opt_pos_y-val :lambda-list '(m))
(cl:defmethod opt_pos_y-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:opt_pos_y-val is deprecated.  Use anker_data_publish-msg:opt_pos_y instead.")
  (opt_pos_y m))

(cl:ensure-generic-function 'opt_quality-val :lambda-list '(m))
(cl:defmethod opt_quality-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:opt_quality-val is deprecated.  Use anker_data_publish-msg:opt_quality instead.")
  (opt_quality m))

(cl:ensure-generic-function 'wall_distance_right-val :lambda-list '(m))
(cl:defmethod wall_distance_right-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:wall_distance_right-val is deprecated.  Use anker_data_publish-msg:wall_distance_right instead.")
  (wall_distance_right m))

(cl:ensure-generic-function 'wall_distance_left-val :lambda-list '(m))
(cl:defmethod wall_distance_left-val ((m <AnkerDataType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader anker_data_publish-msg:wall_distance_left-val is deprecated.  Use anker_data_publish-msg:wall_distance_left instead.")
  (wall_distance_left m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AnkerDataType>) ostream)
  "Serializes a message object of type '<AnkerDataType>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'time_s))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'gx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'gy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'gz))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ax))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ay))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'az))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'odo_right_pos))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'odo_left_pos))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'odo_right_vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'odo_left_vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'opt_pos_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'opt_pos_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'opt_quality)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'opt_quality)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'wall_distance_right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'wall_distance_right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'wall_distance_left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'wall_distance_left)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AnkerDataType>) istream)
  "Deserializes a message object of type '<AnkerDataType>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'time_s) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gx) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gy) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gz) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ax) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ay) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'az) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'odo_right_pos) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'odo_left_pos) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'odo_right_vel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'odo_left_vel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'opt_pos_x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'opt_pos_y) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'opt_quality)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'opt_quality)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'wall_distance_right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'wall_distance_right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'wall_distance_left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'wall_distance_left)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AnkerDataType>)))
  "Returns string type for a message object of type '<AnkerDataType>"
  "anker_data_publish/AnkerDataType")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AnkerDataType)))
  "Returns string type for a message object of type 'AnkerDataType"
  "anker_data_publish/AnkerDataType")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AnkerDataType>)))
  "Returns md5sum for a message object of type '<AnkerDataType>"
  "1a718d0c383faab3290a892f624d74ab")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AnkerDataType)))
  "Returns md5sum for a message object of type 'AnkerDataType"
  "1a718d0c383faab3290a892f624d74ab")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AnkerDataType>)))
  "Returns full string definition for message of type '<AnkerDataType>"
  (cl:format cl:nil "float64 time_s~%float64 gx~%float64 gy~%float64 gz~%float64 ax~%float64 ay~%float64 az~%float64 odo_right_pos~%float64 odo_left_pos~%float64 odo_right_vel~%float64 odo_left_vel~%float64 opt_pos_x~%float64 opt_pos_y~%uint16 opt_quality~%uint16 wall_distance_right~%uint16 wall_distance_left~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AnkerDataType)))
  "Returns full string definition for message of type 'AnkerDataType"
  (cl:format cl:nil "float64 time_s~%float64 gx~%float64 gy~%float64 gz~%float64 ax~%float64 ay~%float64 az~%float64 odo_right_pos~%float64 odo_left_pos~%float64 odo_right_vel~%float64 odo_left_vel~%float64 opt_pos_x~%float64 opt_pos_y~%uint16 opt_quality~%uint16 wall_distance_right~%uint16 wall_distance_left~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AnkerDataType>))
  (cl:+ 0
     8
     8
     8
     8
     8
     8
     8
     8
     8
     8
     8
     8
     8
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AnkerDataType>))
  "Converts a ROS message object to a list"
  (cl:list 'AnkerDataType
    (cl:cons ':time_s (time_s msg))
    (cl:cons ':gx (gx msg))
    (cl:cons ':gy (gy msg))
    (cl:cons ':gz (gz msg))
    (cl:cons ':ax (ax msg))
    (cl:cons ':ay (ay msg))
    (cl:cons ':az (az msg))
    (cl:cons ':odo_right_pos (odo_right_pos msg))
    (cl:cons ':odo_left_pos (odo_left_pos msg))
    (cl:cons ':odo_right_vel (odo_right_vel msg))
    (cl:cons ':odo_left_vel (odo_left_vel msg))
    (cl:cons ':opt_pos_x (opt_pos_x msg))
    (cl:cons ':opt_pos_y (opt_pos_y msg))
    (cl:cons ':opt_quality (opt_quality msg))
    (cl:cons ':wall_distance_right (wall_distance_right msg))
    (cl:cons ':wall_distance_left (wall_distance_left msg))
))
