% Hyundai Center of Excellence in Vehicle Dynamic Systems & Control
% Ehsan Arasteh
% Interface MATLAB C++ : Input cell to Excel file
% Updated: 9/15/2016

% Summary
% Rearranging cell data from C++ to Input form of excel file

function output = saveINP(input_data,INP_Name,savepath)

spreadsheet = cell(200,18); % Pre allocating spreadsheet


%% Sprung mass parameters
%% Weight and Mass
spreadsheet(1:4,1) = input_data{6}; 
spreadsheet(9,1) = input_data{2}(1); % Wheel Base
spreadsheet(11:12,1) = input_data{2}(2:3); % Track
spreadsheet(10,1) = input_data{1}(1); 

%% Compliance and Stiffnesses
spreadsheet(15:16,1) = input_data{1}(2:3);% Vehicle Roll Stiffness

%% Steering system parameters
spreadsheet(20,1) = input_data{1}(4); % On-center steering ratio -/+ 20 deg
spreadsheet(21,1) = input_data{7}(1); % Steering Motor Moment of Inertia
spreadsheet(22,1) = input_data{3}(1); % Effective arm
spreadsheet(23:31,1) = input_data{7}(2:10); 
spreadsheet(32,1) = input_data{3}(2); % Pneumatic trail

%% Suspension parameters
%% Weight and Mass

for i=1:4
    spreadsheet{1,4+i} = input_data{3}{3}(i); % unsprung mass
end

for i=1:4
    spreadsheet{2,4+i} = input_data{2}{4}(i); % Weight 2-UP
end

for j=1:3 % Camber,Roll, Yaw moment of inertia
    for i=1:4
        spreadsheet{2+j,4+i} = input_data{3}{3+j}(i);
    end
end

%% Length
for i=1:4
    spreadsheet{8,4+i} = input_data{2}{5}(i); % Weight 2-UP
end

%% Compliance and Stiffnesses
for j=1:6 %Wheel Rate-d/bump,Tire Rate-d/bump,Long Stiffness-W/Center,Lat Stiffness-W/Center,Lat Compliance Camber Coefficient,Align.Torq. Compliance Steer Coefficient
    for i=1:4
        spreadsheet{10+j,4+i} = input_data{1}{4+j}(i);
    end
end

%% Damping
for j=1:2 %
    for i=1:4
        spreadsheet{18+j,4+i} = input_data{3}{6+j}(i);
    end
end

%% Kinematics 
for j=1:5 %W/Base Change-d/bump (50mm bump),Track Change-d/bump (50mm bump)
    %Camber Change-d/bump (50mm bump), Spin Change-d/bump (50mm bump),
    %Toe Change-d/bump (50mm)
    for i=1:4
        spreadsheet{22+j,4+i} = input_data{1}{10+j}(i);
    end
end

%% Initial Conditions
for j=1:4 %SAI, Caster, Toe, Camber
    for i=1:4
        spreadsheet{30+j,4+i} = input_data{2}{5+j}(i);
    end
end

%% Shock absorber
[~,absorber_length] = size(input_data{4}{1});
for j=1:absorber_length
    for i=1:4
        spreadsheet{1+j,9+i} = input_data{4}{i}(j);
    end
end

%% spring
[~,spring_length] = size(input_data{5}{1});
for j=1:spring_length
    for i=1:4
        spreadsheet{1+j,14+i} = input_data{5}{i}(j);
    end
end

%% LABELS
labels_sus = cell(34,2); % Pre allocating spreadsheet
%% Suspension Labels names
labels_sus{1,1} = 'Unsprung Mass';
labels_sus{2,1} = 'Weight-2UP';
labels_sus{3,1} = 'Camber moment of inertia';
labels_sus{4,1} = 'Roll moment of inertia';
labels_sus{5,1} = 'Yaw moment of inertia';
labels_sus{6,1} = [];
labels_sus{7,1} = 'Length';
labels_sus{8,1} = 'Tire radius';
labels_sus{9,1} = [];
labels_sus{10,1} = 'Compliance and Stiffness';
labels_sus{11,1} = 'Wheel Rate-d/bump';
labels_sus{12,1} = 'Tire Rate-d/bump';
labels_sus{13,1} = 'Long Stiffness-W/Center';
labels_sus{14,1} = 'Lat Stiffness-W/Center';
labels_sus{15,1} = 'Lat Compliance Camber Coefficient';
labels_sus{16,1} = 'Align.Torq. Compliance Steer Coefficient';
labels_sus{17,1} = [];
labels_sus{18,1} = 'Damping';
labels_sus{19,1} = 'Suspension damping coefficient';
labels_sus{20,1} = 'Suspension compliance damping ratio';
labels_sus{21,1} = [];
labels_sus{22,1} = 'Kinematics';
labels_sus{23,1} = 'W/Base Change-d/bump (50mm bump)';
labels_sus{24,1} = 'Track Change-d/bump (50mm bump)';
labels_sus{25,1} = 'Camber Change-d/bump (50mm bump)';
labels_sus{26,1} = 'Spin Change-d/bump (50mm bump)';
labels_sus{27,1} = 'Toe Change-d/bump (50mm)';
labels_sus{28,1} = 'Damper lever ratio';
labels_sus{29,1} = [];
labels_sus{30,1} = 'Initial Conditions';
labels_sus{31,1} = 'SAI';
labels_sus{32,1} = 'Caster';
labels_sus{33,1} = 'Toe';
labels_sus{34,1} = 'Camber';
%% Suspension Labels units
labels_sus{1,2} = 'kg';
labels_sus{2,2} = 'N';
labels_sus{3,2} = 'kg-m^2';
labels_sus{4,2} = 'kg-m^2';
labels_sus{5,2} = 'kg-m^2';
labels_sus{6,2} = [];
labels_sus{7,2} = [];
labels_sus{8,2} = 'mm';
labels_sus{9,2} = [];
labels_sus{10,2} = [];
labels_sus{11,2} = 'N/mm';
labels_sus{12,2} = 'N/mm';
labels_sus{13,2} = 'N/mm';
labels_sus{14,2} = 'N/mm';
labels_sus{15,2} = 'deg/KN';
labels_sus{16,2} = 'deg/100Nm';
labels_sus{17,2} = [];
labels_sus{18,2} = [];
labels_sus{19,2} = 'N-s/m';
labels_sus{20,2} = '[]';
labels_sus{21,2} = [];
labels_sus{22,2} = [];
labels_sus{23,2} = 'mm';
labels_sus{24,2} = 'mm';
labels_sus{25,2} = 'deg';
labels_sus{26,2} = 'deg';
labels_sus{27,2} = 'deg';
labels_sus{28,2} = 'mm/mm';
labels_sus{29,2} = [];
labels_sus{30,2} = [];
labels_sus{31,2} = 'deg';
labels_sus{32,2} = 'deg';
labels_sus{33,2} = 'mm';
labels_sus{34,2} = 'deg';

%% Shock Absorber and Spring units
labels_shock_units = cell(1,9);
labels_shock_units{1,1} = 'm/s';
labels_shock_units{1,2} = 'N';
labels_shock_units{1,3} = 'm/s';
labels_shock_units{1,4} = 'N';
labels_shock_units{1,5} = [];
labels_shock_units{1,6} = 'mm';
labels_shock_units{1,7} = 'N';
labels_shock_units{1,8} = 'mm';
labels_shock_units{1,9} = 'N';


%% Saving to excel
current_path = cd; % storing current directory
cd(savepath); % Changing current directory to the saving directory
xlswrite(INP_Name,spreadsheet,1,'C8:T200') %Writing into the excel file
xlswrite(INP_Name,labels_sus,1,'E8:F41') %Writing into the excel file
xlswrite(INP_Name,labels_shock_units,1,'L8:T8') %Writing into the excel file
cd(current_path); % Back to the current directory 

end