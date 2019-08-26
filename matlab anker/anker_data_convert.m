function data_out = anker_data_convert(str,data_in)
%ANKER_DATA_CONVERT 此处显示有关此函数的摘要
%   此处显示详细说明
ACC_Resolution = 0.000897825622;
GYRO_Resolution = 0.0076294;
OPT_Resolution = 8.66306e-05;
TIME_Resolution = 0.001;
ODO_Resolution = 0.001;
data_out = data_in;
data_out(:,1) = data_in(:,1)*TIME_Resolution;
if str == 'IMU' 
    data_out(:,2:4) = data_in(:,2:4)*ACC_Resolution;
    data_out(:,5:7) = data_in(:,5:7)*GYRO_Resolution;
end
if str == 'ODO'
    data_out(:,2:5) = data_in(:,2:5)*ODO_Resolution;
end
if str == 'OPT'
    data_out(:,2:3) = data_in(:,2:3)*OPT_Resolution;
end
end

