function state = ankerEkfProcess(filepath)
%ANKEREKFPROCESS 此处显示有关此函数的摘要
%   此处显示详细说明
 [imu_data,odo_data,opt_data] = read_anker_data(filepath);
 gyro_bias = calculate_gyro_bias(imu_data,odo_data);
 disp(['gyro bias: ',num2str(gyro_bias*180/pi),'deg/s!']);
 [pos_from_imu,pos_from_odometry,scalar] = motion_propagate(imu_data,odo_data,gyro_bias);
 state =  anker_ekf(imu_data,odo_data,opt_data,gyro_bias);
 
end

