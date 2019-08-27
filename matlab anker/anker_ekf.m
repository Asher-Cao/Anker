function state = anker_ekf(imu,odom,opt,gyro_bias)
%ANKER_EKF 此处显示有关此函数的摘要
%   此处显示详细说明

wheel_distance = 0.209;
yaw_noise = 0.01;
vx_noise = 0.04;
vy_noise = 0.02;
bias_noise = 0.001;
odom_velx_noise = 0.001;
odom_vely_noise = 0.001;



%% EKF Initialization
len = min(min(length(imu(:,1)),length(opt(:,1))),length(odom(:,1)));
odo_vx = zeros(1,len);
state = zeros(6,len);
state(6,1) = gyro_bias;
P  = eye(6,6)*0.001;
G  = zeros(6,4);
G(3:6,1:4) = eye(4,4);
Q = zeros(4,4);
Q(1,1) = yaw_noise*yaw_noise;
Q(2,2) = vx_noise*vx_noise;
Q(3,3) = vy_noise*vy_noise;
Q(4,4) = bias_noise*bias_noise;
H  = zeros(2,6);
H(1,4) = 1;
H(1,6) = -wheel_distance/2;
H(2,4) = 1;
H(2,6) =  wheel_distance/2;
R = zeros(2,2);
R(1,1) = odom_velx_noise*odom_vely_noise;
R(2,2) = odom_vely_noise*odom_vely_noise;
%% EKF PROCESS%
bad_time_count = 0;
for i=2:len
   if(imu(i,1) ~= odom(i,1) || imu(i,1) ~= opt(i,1))
       bad_time_count = bad_time_count + 1;
   end
   if bad_time_count > 10
       disp('time is not aligned between sensors!');
       break;
   end
% step1-1: predict state
   delta_time = imu(i,1) - imu(i-1,1);
   if(delta_time > 0.0111 || delta_time < 0)
       disp(['delta time is not right in',num2str(i),'!']);
       break;
   end
   odo_vx(1,i) = (odom(i,4) + odom(i,5))/2;
   x = state(1,i-1);
   y = state(2,i-1);
   yaw = state(3,i-1);
   v_x = state(4,i-1);
   v_y = state(5,i-1);
   w_b = state(6,i-1);
   predict_state = zeros(6,1);
   predict_state(1,1) = x + cos(yaw)*v_x*delta_time - sin(yaw)*v_y*delta_time;
   predict_state(2,1) = y + sin(yaw)*v_x*delta_time + cos(yaw)*v_y*delta_time;
   predict_state(3,1) = yaw + (imu(i,7) - w_b)*delta_time;
   predict_state(4,1) = v_x;
   predict_state(5,1) = v_y;
   predict_state(6,1) = w_b;
% step1-2: predict covariance   
        f =  zeros(6,6);
   f(1,3) = -sin(yaw)*v_x*delta_time - cos(yaw)*v_y*delta_time;
   f(1,4) =  cos(yaw)*delta_time;
   f(1,5) = -sin(yaw)*delta_time;
   f(2,3) =  cos(yaw)*v_x*delta_time - sin(yaw)*v_y*delta_time;
   f(2,4) =  sin(yaw)*delta_time;
   f(2,5) =  cos(yaw)*delta_time;
   f(3,6) = -delta_time;
   F = eye(6,6) + f;
   predict_p = F*P*F' + G*Q*G';
% step2: calculate gain matrix
   Tmp = H*predict_p*H' + R;
   K = predict_p*H'*pinv(Tmp);
% step3: fix state and update covariance   
   predict_measurment = H*predict_state + [wheel_distance/2;-wheel_distance/2]*imu(i,7);
   error = [odom(i,4);odom(i,5)] - predict_measurment;
   state(:,i) = predict_state + K*error;
   P = (eye(6,6) - K*H)*predict_p; 
end
figure;
title('ekf path')
plot(state(1,:),state(2,:));
grid on;
figure;
subplot(3,1,1)
title('gyro bias');
plot(imu(1:len,1),state(6,:)*180/pi);
grid on;
subplot(3,1,2)
title('v_x');
plot(imu(1:len,1),odo_vx,'r',imu(1:len,1),state(4,:),'b');
grid on;
subplot(3,1,3);
title('v_y')
plot(imu(1:len,1),state(5,:));
grid on;
end

