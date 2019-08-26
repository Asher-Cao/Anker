;; Auto-generated. Do not edit!


(when (boundp 'anker_ekf_pro::AnkerDataType)
  (if (not (find-package "ANKER_EKF_PRO"))
    (make-package "ANKER_EKF_PRO"))
  (shadow 'AnkerDataType (find-package "ANKER_EKF_PRO")))
(unless (find-package "ANKER_EKF_PRO::ANKERDATATYPE")
  (make-package "ANKER_EKF_PRO::ANKERDATATYPE"))

(in-package "ROS")
;;//! \htmlinclude AnkerDataType.msg.html


(defclass anker_ekf_pro::AnkerDataType
  :super ros::object
  :slots (_time_s _gx _gy _gz _ax _ay _az _odo_right_pos _odo_left_pos _odo_right_vel _odo_left_vel _opt_pos_x _opt_pos_y _opt_quality _wall_distance_right _wall_distance_left ))

(defmethod anker_ekf_pro::AnkerDataType
  (:init
   (&key
    ((:time_s __time_s) 0.0)
    ((:gx __gx) 0.0)
    ((:gy __gy) 0.0)
    ((:gz __gz) 0.0)
    ((:ax __ax) 0.0)
    ((:ay __ay) 0.0)
    ((:az __az) 0.0)
    ((:odo_right_pos __odo_right_pos) 0.0)
    ((:odo_left_pos __odo_left_pos) 0.0)
    ((:odo_right_vel __odo_right_vel) 0.0)
    ((:odo_left_vel __odo_left_vel) 0.0)
    ((:opt_pos_x __opt_pos_x) 0.0)
    ((:opt_pos_y __opt_pos_y) 0.0)
    ((:opt_quality __opt_quality) 0)
    ((:wall_distance_right __wall_distance_right) 0)
    ((:wall_distance_left __wall_distance_left) 0)
    )
   (send-super :init)
   (setq _time_s (float __time_s))
   (setq _gx (float __gx))
   (setq _gy (float __gy))
   (setq _gz (float __gz))
   (setq _ax (float __ax))
   (setq _ay (float __ay))
   (setq _az (float __az))
   (setq _odo_right_pos (float __odo_right_pos))
   (setq _odo_left_pos (float __odo_left_pos))
   (setq _odo_right_vel (float __odo_right_vel))
   (setq _odo_left_vel (float __odo_left_vel))
   (setq _opt_pos_x (float __opt_pos_x))
   (setq _opt_pos_y (float __opt_pos_y))
   (setq _opt_quality (round __opt_quality))
   (setq _wall_distance_right (round __wall_distance_right))
   (setq _wall_distance_left (round __wall_distance_left))
   self)
  (:time_s
   (&optional __time_s)
   (if __time_s (setq _time_s __time_s)) _time_s)
  (:gx
   (&optional __gx)
   (if __gx (setq _gx __gx)) _gx)
  (:gy
   (&optional __gy)
   (if __gy (setq _gy __gy)) _gy)
  (:gz
   (&optional __gz)
   (if __gz (setq _gz __gz)) _gz)
  (:ax
   (&optional __ax)
   (if __ax (setq _ax __ax)) _ax)
  (:ay
   (&optional __ay)
   (if __ay (setq _ay __ay)) _ay)
  (:az
   (&optional __az)
   (if __az (setq _az __az)) _az)
  (:odo_right_pos
   (&optional __odo_right_pos)
   (if __odo_right_pos (setq _odo_right_pos __odo_right_pos)) _odo_right_pos)
  (:odo_left_pos
   (&optional __odo_left_pos)
   (if __odo_left_pos (setq _odo_left_pos __odo_left_pos)) _odo_left_pos)
  (:odo_right_vel
   (&optional __odo_right_vel)
   (if __odo_right_vel (setq _odo_right_vel __odo_right_vel)) _odo_right_vel)
  (:odo_left_vel
   (&optional __odo_left_vel)
   (if __odo_left_vel (setq _odo_left_vel __odo_left_vel)) _odo_left_vel)
  (:opt_pos_x
   (&optional __opt_pos_x)
   (if __opt_pos_x (setq _opt_pos_x __opt_pos_x)) _opt_pos_x)
  (:opt_pos_y
   (&optional __opt_pos_y)
   (if __opt_pos_y (setq _opt_pos_y __opt_pos_y)) _opt_pos_y)
  (:opt_quality
   (&optional __opt_quality)
   (if __opt_quality (setq _opt_quality __opt_quality)) _opt_quality)
  (:wall_distance_right
   (&optional __wall_distance_right)
   (if __wall_distance_right (setq _wall_distance_right __wall_distance_right)) _wall_distance_right)
  (:wall_distance_left
   (&optional __wall_distance_left)
   (if __wall_distance_left (setq _wall_distance_left __wall_distance_left)) _wall_distance_left)
  (:serialization-length
   ()
   (+
    ;; float32 _time_s
    4
    ;; float32 _gx
    4
    ;; float32 _gy
    4
    ;; float32 _gz
    4
    ;; float32 _ax
    4
    ;; float32 _ay
    4
    ;; float32 _az
    4
    ;; float32 _odo_right_pos
    4
    ;; float32 _odo_left_pos
    4
    ;; float32 _odo_right_vel
    4
    ;; float32 _odo_left_vel
    4
    ;; float32 _opt_pos_x
    4
    ;; float32 _opt_pos_y
    4
    ;; uint16 _opt_quality
    2
    ;; uint16 _wall_distance_right
    2
    ;; uint16 _wall_distance_left
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _time_s
       (sys::poke _time_s (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _gx
       (sys::poke _gx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _gy
       (sys::poke _gy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _gz
       (sys::poke _gz (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ax
       (sys::poke _ax (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ay
       (sys::poke _ay (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _az
       (sys::poke _az (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _odo_right_pos
       (sys::poke _odo_right_pos (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _odo_left_pos
       (sys::poke _odo_left_pos (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _odo_right_vel
       (sys::poke _odo_right_vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _odo_left_vel
       (sys::poke _odo_left_vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _opt_pos_x
       (sys::poke _opt_pos_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _opt_pos_y
       (sys::poke _opt_pos_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint16 _opt_quality
       (write-word _opt_quality s)
     ;; uint16 _wall_distance_right
       (write-word _wall_distance_right s)
     ;; uint16 _wall_distance_left
       (write-word _wall_distance_left s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _time_s
     (setq _time_s (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _gx
     (setq _gx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _gy
     (setq _gy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _gz
     (setq _gz (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ax
     (setq _ax (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ay
     (setq _ay (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _az
     (setq _az (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _odo_right_pos
     (setq _odo_right_pos (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _odo_left_pos
     (setq _odo_left_pos (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _odo_right_vel
     (setq _odo_right_vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _odo_left_vel
     (setq _odo_left_vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _opt_pos_x
     (setq _opt_pos_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _opt_pos_y
     (setq _opt_pos_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint16 _opt_quality
     (setq _opt_quality (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _wall_distance_right
     (setq _wall_distance_right (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _wall_distance_left
     (setq _wall_distance_left (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get anker_ekf_pro::AnkerDataType :md5sum-) "de6762e996fc903aa001bbb12ea9d4dd")
(setf (get anker_ekf_pro::AnkerDataType :datatype-) "anker_ekf_pro/AnkerDataType")
(setf (get anker_ekf_pro::AnkerDataType :definition-)
      "float32 time_s
float32 gx
float32 gy
float32 gz
float32 ax
float32 ay
float32 az
float32 odo_right_pos
float32 odo_left_pos
float32 odo_right_vel
float32 odo_left_vel
float32 opt_pos_x
float32 opt_pos_y
uint16 opt_quality
uint16 wall_distance_right
uint16 wall_distance_left

")



(provide :anker_ekf_pro/AnkerDataType "de6762e996fc903aa001bbb12ea9d4dd")

