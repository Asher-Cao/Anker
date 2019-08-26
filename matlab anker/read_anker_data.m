function [imu_data,odo_data,opt_data] = read_anker_data(path)
%READ_ANKER_DATA 此处显示有关此函数的摘要
%   此处显示详细说明
file_path = ['/home/kdq/Workspace/Anker/cvs_datas/',path];
imu_data = load([file_path,'/imu_file.cvs']);
odo_data = load([file_path,'/odometer_file.cvs']);
opt_data = load([file_path,'/optical_flow_file.cvs']);

if(mod(imu_data(1,1),1) == 0)
    imu_data = anker_data_convert('IMU',imu_data);   
    odo_data = anker_data_convert('ODO',odo_data);
    opt_data = anker_data_convert('OPT',opt_data);
end

end

