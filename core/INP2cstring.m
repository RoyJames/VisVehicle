function [ input_data ] = INP2cstring(INP_path)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

input_data = cell(7, 1);
summary_sheet = cell(15, 1); % there are 15 lines of parameters
summary_sheet{1} = ['C.G.h', char(9), 'mm', char(9), '1.5'];
summary_sheet{2} = ['Vehicle Roll Stiffness (Front)', char(9), 'Nm/deg', char(9),'2.5'];
%summary_sheet{3} = ['Toe Change-d/bump (50mm)', char(9), 'deg', char(9), 1, char(9), 2, char(9), 3, char(9), 4];
input_data{1} = summary_sheet; 

end

