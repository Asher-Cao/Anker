function [yaw_from_imu,yaw_from_odometry,scalar] = motion_propagate_yaw(imu,odometry)
%MOTION_PROPAGATE 此处显示有关此函数的摘要
%   此处显示详细说明
wheel_distance = 0.209;
%gz_bias = 0.10511;
gz_gain = 1.005;
gz_bias = calculate_gyro_bias(imu,odometry);

disp(['bias of gz is ',num2str(gz_bias),'deg/s']); 
len = length(imu(:,1));
scalar = zeros(len,1);
yaw_from_imu = zeros(len,1);
yaw_from_odometry = zeros(len,1) ;

for i=2:len
   delta_time = imu(i,1) - imu(i-1,1);
   yaw_from_imu(i) = yaw_from_imu(i-1) + (imu(i,2)-gz_bias)*gz_gain*delta_time;
   
   delta_pose_right = odometry(i,2) - odometry(i-1,2);
   delta_pose_left = odometry(i,3) - odometry(i-1,3);
   delta_yaw = (delta_pose_right - delta_pose_left)/wheel_distance*180/pi;
   yaw_from_odometry(i) = yaw_from_odometry(i-1) + delta_yaw;
   scalar(i) = yaw_from_odometry(i)/yaw_from_imu(i);
end
disp(['yaw from imu: ',num2str(yaw_from_imu(len)),'deg; yaw from odometry: ',num2str(yaw_from_odometry(len)),'deg.']);
subplot(3,1,1)
plot(imu(:,1),scalar);
subplot(3,1,2)
plot(imu(:,1),yaw_from_imu,imu(:,1),yaw_from_odometry);
subplot(3,1,3)
plot(odometry(:,1),odometry(:,4),odometry(:,1),odometry(:,5));
end
