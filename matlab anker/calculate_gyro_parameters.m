function [k,w_b,v_r,v_l] =  calculate_gyro_parameters(imu,odom)
%CALCULATE_GYRO_PARAMETERS 此处显示有关此函数的摘要
%   此处显示详细说明
len = length(odom(:,1));
wheel_distance = 0.209;
sum_odom_vel = zeros(len,1);
matrix_length = 12000;
count = 0;
matrix_a = zeros(matrix_length*2,4);
b = zeros(matrix_length*2,1);
imu(:,7) = imu(:,7)*pi/180;
k = 1;
w_b = 0;
v_r = 0;
v_l = 0;
for i=1:len
    sum_odom_vel(i) = odom(i,4) + odom(i,5);
    if abs(sum_odom_vel(i)) < 0.005 && abs(odom(i,4)) > 0.05 && count < matrix_length && imu(i,1) == odom(i,1)
         count = count + 1;
         matrix_a(count*2-1,:) = [0.5*wheel_distance*imu(i,7) -0.5*wheel_distance 1 0];
         matrix_a(count*2,:)   = [-0.5*wheel_distance*imu(i,7) 0.5*wheel_distance 0 1];
         b(count*2-1) = odom(i,4);
         b(count*2)   = odom(i,5);
    end
end
if count == matrix_length
    state = pinv(matrix_a)*b;
    k = state(1);
    w_b = state(2)/k;
    v_r = state(3);
    v_l = state(4);
    disp(['k:',num2str(k),' w_b:',num2str(w_b),' v_r:',num2str(v_r),' v_l:',num2str(v_l)]);
end

subplot(2,1,1)
plot(odom(:,1),odom(:,4),'r',odom(:,1),odom(:,5),'b');
subplot(2,1,2)
plot(odom(:,1),sum_odom_vel);
    


end

