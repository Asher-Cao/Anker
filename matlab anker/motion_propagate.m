function [pos_from_imu,pos_from_odometry,scalar] = motion_propagate(imu,odometry,gz_bias)
%MOTION_PROPAGATE 此处显示有关此函数的摘要
%   此处显示详细说明
wheel_distance = 0.209;
gz_gain = 1.0;

len = length(imu(:,1));
scalar = zeros(len,1);
pos_from_imu = zeros(len,3);
pos_from_odometry = zeros(len,3) ;

for i=2:len

   %% yaw and postion from odometry 
   delta_pose_right = odometry(i,2) - odometry(i-1,2);
   delta_pose_left = odometry(i,3) - odometry(i-1,3);
   delta_yaw = (delta_pose_right - delta_pose_left)/wheel_distance;
   delta_pose = (delta_pose_left + delta_pose_right)*0.5;
   pos_from_odometry(i,3) = pos_from_odometry(i-1,3) + delta_yaw;
   pos_from_odometry(i,1) = pos_from_odometry(i-1,1) + delta_pose*cos(pos_from_odometry(i,3));
   pos_from_odometry(i,2) = pos_from_odometry(i-1,2) + delta_pose*sin(pos_from_odometry(i,3));
   %% yaw and postion from imu 
   delta_time = imu(i,1) - imu(i-1,1);  
   pos_from_imu(i,3) = pos_from_imu(i-1,3) + (imu(i,7)-gz_bias)*gz_gain*delta_time;
   pos_from_imu(i,1) = pos_from_imu(i-1,1) + delta_pose*cos(pos_from_imu(i,3));
   pos_from_imu(i,2) = pos_from_imu(i-1,2) + delta_pose*sin(pos_from_imu(i,3));

   
   scalar(i) = pos_from_odometry(i,3)/pos_from_imu(i,3);
end

% disp(['yaw from imu: ',num2str(pos_from_imu(len,3)*180/pi),'deg; yaw from odometry: ',num2str(pos_from_odometry(len,3)*180/pi),'deg.']);
% figure(1);
% subplot(3,1,1);
% plot(imu(:,1),scalar);
% title('scalar:yaw_odo/yaw_imu');
% legend('ratio');
% subplot(3,1,2);
% plot(imu(:,1),pos_from_imu(:,3)*180/pi)%,imu(:,1),pos_from_odometry(:,3)*180/pi);
% % title('calculate yaw from odometry and imu');
% % legend('imu yaw','odometry yaw');
% subplot(3,1,3);
% plot(odometry(:,1),odometry(:,4),odometry(:,1),odometry(:,5));
% title('odometry speed');
% legend('right speed','left speed');

figure;

plot(pos_from_odometry(:,1),pos_from_odometry(:,2),'g',pos_from_imu(:,1),pos_from_imu(:,2),'r');
title('path from odometry and imu');
legend('odometry path','imu path');
grid on;


end

