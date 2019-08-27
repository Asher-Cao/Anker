function gyro_bias = calculate_gyro_bias(imu,odometry)
%CALCULATE_GYRO_BIAS 此处显示有关此函数的摘要
%   此处显示详细说明
len = length(imu(:,1));
gyro_sum = 0;
count = 0;
begin_time = imu(1,1);
for i = 1:len
    count = count+1;
   if(odometry(i,4) ~= 0 || odometry(i,5) ~=0)
        count = 0;
        gyro_sum = 0;
        begin_time = imu(i,1);
       continue;
   end
   gyro_sum = gyro_sum + imu(i,7);
   if imu(i,1) - begin_time > 40
       gyro_bias  = gyro_sum/count;
       return;
   end
end
end

