% Hyundai Center of Excellence in Vehicle Dynamic Systems & Control
% Interface MATLAB C++ : INPUT file to strings
% Updated: 9/13/2016

% Summary
% Converting all the data inside input sheet (.xlsx) to string format 
% and putting it inside cells

function output = INP2cstring(INP_path,INP_name)

current_path = cd; % storing current directory
cd(INP_path); % Changing current directory to the input directory

%% Initializing cells
summary_sheet = cell(15,1);
vehicle_info_sheet = cell(9,1);
suspension_sheet = cell(9,1);
spring_sheet = cell(4,1);
damper_sheet = cell(4,1);
body_sheet = cell(4,1);
steering_sheet = cell(10,1);


%% Suspension parameters - Weight and Mass
[NUM5,TXT5] = xlsread(INP_name,1,'E8:J12');
    % Unsprung mass, kg
    mus_l1= NUM5(1,1); mus_txt = [TXT5{1,1},char(9),TXT5{1,2}];
    mus_r1= NUM5(1,2);
    mus_l2= NUM5(1,3);
    mus_r2= NUM5(1,4);
    %
    suspension_sheet{3} = [mus_txt,char(9),num2str(mus_l1) ...
        ,char(9),num2str(mus_r1),char(9),num2str(mus_l2),char(9),...
        num2str(mus_r2)];
    
    % Curb weight, N
    % Weight-2UP, N
    Weight_l1= NUM5(2,1); Weight_txt = [TXT5{2,1},char(9),TXT5{2,2}];
    Weight_r1= NUM5(2,2);
    Weight_l2= NUM5(2,3);
    Weight_r2= NUM5(2,4);
    %
    vehicle_info_sheet{4} = [Weight_txt,char(9),num2str(Weight_l1) ...
        ,char(9),num2str(Weight_r1),char(9),num2str(Weight_l2),char(9),...
        num2str(Weight_r2)];
    
    % Unsprung camber moment of inertia, kg-m^2
    Jus_x_l1= NUM5(3,1); Jus_x_txt = [TXT5{3,1},char(9),TXT5{3,2}];
    Jus_x_r1= NUM5(3,2);
    Jus_x_l2= NUM5(3,3);
    Jus_x_r2= NUM5(3,4);
    %
    suspension_sheet{4} = [Jus_x_txt,char(9),num2str(Jus_x_l1) ...
        ,char(9),num2str(Jus_x_r1),char(9),num2str(Jus_x_l2),char(9),...
        num2str(Jus_x_r2)];
    
    % Unsprung rolling moment of inertia, kg-m^2
    Jus_y_l1= NUM5(4,1); Jus_y_txt = [TXT5{4,1},char(9),TXT5{4,2}];
    Jus_y_r1= NUM5(4,2);
    Jus_y_l2= NUM5(4,3);
    Jus_y_r2= NUM5(4,4);
    %
    suspension_sheet{5} = [Jus_y_txt,char(9),num2str(Jus_y_l1) ...
        ,char(9),num2str(Jus_y_r1),char(9),num2str(Jus_y_l2),char(9),...
        num2str(Jus_y_r2)];    
    
    % Unsprung yaw moment of inertia, kg-m^2
    Jus_z_l1= NUM5(5,1); Jus_z_txt = [TXT5{5,1},char(9),TXT5{5,2}];
    Jus_z_r1= NUM5(5,2);
    Jus_z_l2= NUM5(5,3);
    Jus_z_r2= NUM5(5,4);
    %
    suspension_sheet{6} = [Jus_z_txt,char(9),num2str(Jus_z_l1) ...
        ,char(9),num2str(Jus_z_r1),char(9),num2str(Jus_z_l2),char(9),...
        num2str(Jus_z_r2)];


%% Sprung Mass Parameters - Weight and Mass
[NUM1,TXT1] = xlsread(INP_name,1,'A8:C13');
Veh_I = 'Vehicle inertia (Sprung)';
    ms = NUM1(1,1); ms_txt = [Veh_I,char(9),TXT1{1,1},char(9),TXT1{1,2}];% Sprung mass, kg
    body_sheet{1} = [ms_txt,char(9),num2str(ms)];
    
    Js_x = NUM1(2,1); Js_x_txt = [Veh_I,char(9),TXT1{2,1},char(9),TXT1{2,2}];% Sprung roll moment of inertia, kg-m^2
    body_sheet{2} = [Js_x_txt,char(9),num2str(Js_x)];    
        
    Js_y = NUM1(3,1); Js_y_txt = [Veh_I,char(9),TXT1{3,1},char(9),TXT1{3,2}];% Sprung pitch moment of inertia, kg-m^2
    body_sheet{3} = [Js_y_txt,char(9),num2str(Js_y)];    
        
    Js_z = NUM1(4,1); Js_z_txt = [Veh_I,char(9),TXT1{4,1},char(9),TXT1{4,2}];% Sprung yaw moment of inertia, kg-m^2
    body_sheet{4} = [Js_z_txt,char(9),num2str(Js_z)];    

%% Sprung Mass Parameters - Length
[NUM2,TXT2] = xlsread(INP_name,1,'A16:C19');
    % (Info: Wheel Base (mm))
    L0= NUM2(1,1); L0_txt = [TXT2{1,1},char(9),TXT2{1,2}];
    vehicle_info_sheet{1} = [L0_txt,char(9),num2str(L0)]; 
    
    % (Summary: C.G.H 1UP [mm])
    h= NUM2(2,1); h_txt = [TXT2{2,1}(1:5),char(9),TXT2{2,2}];
    summary_sheet{1} = [h_txt,char(9),num2str(h)]; 
    
    % (Info: Track (mm))
    T0_1= NUM2(3,1); T0_1_txt = [TXT2{3,1},char(9),TXT2{3,2}];
    vehicle_info_sheet{2} = [T0_1_txt,char(9),num2str(T0_1)];
    T0_2= NUM2(4,1); T0_2_txt = [TXT2{4,1},char(9),TXT2{4,2}];
    vehicle_info_sheet{3} = [T0_2_txt,char(9),num2str(T0_2)];
    
%% Sprung Mass Parameters - Compliance and Stiffness
[NUM3,TXT3] = xlsread(INP_name,1,'A22:C23');
    % Vehicle roll stiffness
    RS_1= NUM3(1,1); RS_1_txt = [TXT3{1,1},char(9),TXT3{1,2}];
    summary_sheet{2} = [RS_1_txt,char(9),num2str(RS_1)];
    RS_2= NUM3(2,1); RS_2_txt = [TXT3{2,1},char(9),TXT3{2,2}];
    summary_sheet{3} = [RS_2_txt,char(9),num2str(RS_2)];    


%% Steering System Parameters
[NUM4,TXT4] = xlsread(INP_name,1,'A27:C39');

    SWA_ratio = NUM4(1,1); SWA_ratio_txt = [TXT4{1,1},char(9),TXT4{1,2}];% Steering ratio
    summary_sheet{4} = [SWA_ratio_txt,char(9),num2str(SWA_ratio)];
    
    Jm = NUM4(2,1); Jm_txt = [TXT4{2,1},char(9),TXT4{2,2}];% Motor moment of inertia, kg-m^2
    steering_sheet{1} = [Jm_txt,char(9),num2str(Jm)];
    
    l = NUM4(3,1); l_txt = [TXT4{3,1},char(9),TXT4{3,2}];% Effective arm length, m
    suspension_sheet{1} = [l_txt,char(9),num2str(l)];
    
    gG = NUM4(4,1); gG_txt = [TXT4{4,1},char(9),TXT4{4,2}]; % Motor gear ratio
    steering_sheet{2} = [gG_txt,char(9),num2str(gG)];
     
    bL = NUM4(5,1); bL_txt = [TXT4{5,1},char(9),TXT4{5,2}];% Lower column damping - linear, Nm-s/rad
    steering_sheet{3} = [bL_txt,char(9),num2str(bL)];
    
    bU = NUM4(6,1); bU_txt = [TXT4{6,1},char(9),TXT4{6,2}];% Upper column damping - linear, Nm-s/rad
    steering_sheet{4} = [bU_txt,char(9),num2str(bU)];
    
    kL = NUM4(7,1); kL_txt = [TXT4{7,1},char(9),TXT4{7,2}];% Lower column stiffness, Nm/rad
    steering_sheet{5} = [kL_txt,char(9),num2str(kL)];
    
    kU = NUM4(8,1); kU_txt = [TXT4{8,1},char(9),TXT4{8,2}];% Upper column stiffness, Nm/rad
    steering_sheet{6} = [kU_txt,char(9),num2str(kU)];
    
    Tm = NUM4(9,1); Tm_txt = [TXT4{9,1},char(9),TXT4{9,2}]; % Transduction coefficient, N-m/A
    steering_sheet{7} = [Tm_txt,char(9),num2str(Tm)];
    
    Tfg_damping = NUM4(10,1); Tfg_txt = [TXT4{10,1},char(9),TXT4{10,2}];% Column absolute velocity damping, Nm-s/rad
    steering_sheet{8} = [Tfg_txt,char(9),num2str(Tfg_damping)];
    
    Ffr_damping = NUM4(11,1); Ffr_txt = [TXT4{11,1},char(9),TXT4{11,2}];% Rack damping, N-s/m
    steering_sheet{9} = [Ffr_txt,char(9),num2str(Ffr_damping)]; 
    
    mrack = NUM4(12,1); mrack_txt = [TXT4{12,1},char(9),TXT4{12,2}]; % Rack mass, kg
    steering_sheet{10} = [mrack_txt,char(9),num2str(mrack)];
    
    pt = NUM4(13,1); pt_txt = [TXT4{13,1},char(9),TXT4{13,2}]; % Pneumatic trail, m
    suspension_sheet{2} = [pt_txt,char(9),num2str(pt)];
    
    
%% Suspension Parameters - Length
[NUM6,TXT6] = xlsread(INP_name,1,'E15:J15');

    % (Info: Tire Radius (mm))
    Rl_l1= NUM6(1,1); Rl_txt = [TXT6{1,1},char(9),TXT6{1,2}];
    Rl_r1= NUM6(1,2);
    Rl_l2= NUM6(1,3);
    Rl_r2= NUM6(1,4);
    vehicle_info_sheet{5} = [Rl_txt,char(9),num2str(Rl_l1),...
        char(9),num2str(Rl_r1),char(9),num2str(Rl_l2),...
        char(9),num2str(Rl_r2)];
    
%% Suspension Parameters - Compliance and Stiffness
    % Read parameters
[NUM7,TXT7] = xlsread(INP_name,1,'E18:J23');

    % (Summary: Wheel Rate-d/bump [N/mm])
    ks_l1= NUM7(1,1); ks_txt = [TXT7{1,1},char(9),TXT7{1,2}];
    ks_r1= NUM7(1,2);
    ks_l2= NUM7(1,3);
    ks_r2= NUM7(1,3);
    summary_sheet{5} = [ks_txt,char(9),num2str(ks_l1),...
        char(9),num2str(ks_r1),char(9),num2str(ks_l2),...
        char(9),num2str(ks_r2)];
    
    % (Summary: Tire Rate-d/bump [N/mm])
    kt_l1= NUM7(2,1); kt_txt = [TXT7{2,1},char(9),TXT7{2,2}];
    kt_r1= NUM7(2,2);
    kt_l2= NUM7(2,3);
    kt_r2= NUM7(2,4);
    summary_sheet{6} = [kt_txt,char(9),num2str(kt_l1),...
        char(9),num2str(kt_r1),char(9),num2str(kt_l2),...
        char(9),num2str(kt_r2)];
    
    % (Summary: Long Stiffness-W/Center [N/mm])
    kus_x_l1= NUM7(3,1); kus_x_txt = [TXT7{3,1},char(9),TXT7{3,2}];
    kus_x_r1= NUM7(3,2);
    kus_x_l2= NUM7(3,3);
    kus_x_r2= NUM7(3,4);
    summary_sheet{7} = [kus_x_txt,char(9),num2str(kus_x_l1),...
        char(9),num2str(kus_x_r1),char(9),num2str(kus_x_l2),...
        char(9),num2str(kus_x_r2)];
    
    % (Summary: Lat Stiffness-W/Center [N/mm])
    kus_y_l1= NUM7(4,1); kus_y_txt = [TXT7{4,1},char(9),TXT7{4,2}];
    kus_y_r1= NUM7(4,2);
    kus_y_l2= NUM7(4,3);
    kus_y_r2= NUM7(4,4);
    summary_sheet{8} = [kus_y_txt,char(9),num2str(kus_y_l1),...
        char(9),num2str(kus_y_r1),char(9),num2str(kus_y_l2),...
        char(9),num2str(kus_y_r2)];
    
    % (Summary: Lat Compliance Camber Coefficient [deg/KN])
    cus_t_x_l1= NUM7(5,1); cus_t_x_txt = [TXT7{5,1},char(9),TXT7{5,2}];
    cus_t_x_r1= NUM7(5,2);
    cus_t_x_l2= NUM7(5,3);
    cus_t_x_r2= NUM7(5,4);
    summary_sheet{9} = [cus_t_x_txt,char(9),num2str(cus_t_x_l1),...
        char(9),num2str(cus_t_x_r1),char(9),num2str(cus_t_x_l2),...
        char(9),num2str(cus_t_x_r2)];
    

    % (Summary: Align.Torq. Compliance Steer Coefficient [deg/100Nm])
    cus_t_z_l1= NUM7(6,1); cus_t_z_txt = [TXT7{6,1},char(9),TXT7{6,2}];
    cus_t_z_r1= NUM7(6,2);
    cus_t_z_l2= NUM7(6,3);
    cus_t_z_r2= NUM7(6,4);
    summary_sheet{10} = [cus_t_z_txt,char(9),num2str(cus_t_z_l1),...
        char(9),num2str(cus_t_z_r1),char(9),num2str(cus_t_z_l2),...
        char(9),num2str(cus_t_z_r2)];
    

 
 %% Suspension Parameters - Damping
    % Read parameters
[NUM8,TXT8] = xlsread(INP_name,1,'E26:J27');

    % Linear suspension damping coefficient, N-s/m
    bs_l1= NUM8(1,1); bs_txt = [TXT8{1,1},char(9),TXT8{1,2}];
    bs_r1= NUM8(1,2);
    bs_l2= NUM8(1,3);
    bs_r2= NUM8(1,4);
    suspension_sheet{7} = [bs_txt,char(9),num2str(bs_l1),...
        char(9),num2str(bs_r1),char(9),num2str(bs_l2),...
        char(9),num2str(bs_r2)];
    
    % Suspension compliance damping ratio
    zeta_l1= NUM8(2,1); zeta_txt = [TXT8{2,1},char(9),TXT8{2,2}];
    zeta_r1= NUM8(2,2);
    zeta_l2= NUM8(2,3);
    zeta_r2= NUM8(2,4);
    suspension_sheet{8} = [zeta_txt,char(9),num2str(zeta_l1),...
        char(9),num2str(zeta_r1),char(9),num2str(zeta_l2),...
        char(9),num2str(zeta_r2)];
    
    
%% Suspension Parameters - Kinematics (Wheel Stroke)
    % Read parameters
[NUM9,TXT9] = xlsread(INP_name,1,'E30:J35');    
%     % Bump value for measuring kinematics below
%     % - Positive in compression
%     bump = 50/1000;
    
    % Longitudinal change versus wheel stroke, m/m
    % (Summary: W/Base Change-d/bump  (50mm bump) [mm])
    dCPx_dWs_l1= NUM9(1,1); dCPx_dWs_txt = [TXT9{1,1},char(9),TXT9{1,2}];
    dCPx_dWs_r1= NUM9(1,2);
    dCPx_dWs_l2= NUM9(1,3);
    dCPx_dWs_r2= NUM9(1,4);
    summary_sheet{11} = [dCPx_dWs_txt,char(9),num2str(dCPx_dWs_l1),...
        char(9),num2str(dCPx_dWs_r1),char(9),num2str(dCPx_dWs_l2),...
        char(9),num2str(dCPx_dWs_r2)];
    
    % Lateral change versus wheel stroke, m/m
    % (Summary: Track Change-d/bump  (50mm bump) [mm])
    dCPy_dWs_l1= NUM9(2,1); dCPy_dWs_txt = [TXT9{2,1},char(9),TXT9{2,2}];
    dCPy_dWs_r1= NUM9(2,2);
    dCPy_dWs_l2= NUM9(2,3);
    dCPy_dWs_r2= NUM9(2,4);
    summary_sheet{12} = [dCPy_dWs_txt,char(9),num2str(dCPy_dWs_l1),...
        char(9),num2str(dCPy_dWs_r1),char(9),num2str(dCPy_dWs_l2),...
        char(9),num2str(dCPy_dWs_r2)];
    
    % Kingpin inclination change versus wheel stroke, rad/m
    % (Summary: Camber Change-d/bump (50mm bump) [deg])
    % - Assume kingpin inclination and camber changes are equal
    dbeta_dWs_l1= NUM9(3,1); dbeta_dWs_txt = [TXT9{3,1},char(9),TXT9{3,2}];
    dbeta_dWs_r1= NUM9(3,2);
    dbeta_dWs_l2= NUM9(3,3);
    dbeta_dWs_r2= NUM9(3,4);
    summary_sheet{13} = [dbeta_dWs_txt,char(9),num2str(dbeta_dWs_l1),...
        char(9),num2str(dbeta_dWs_r1),char(9),num2str(dbeta_dWs_l2),...
        char(9),num2str(dbeta_dWs_r2)];
    
    % Caster change versus wheel stroke, rad/m
    % - Using spin_change_in_bump
    % (Summary: Spin Change-d/bump (50mm bump) [deg])
    dpsi_dWs_l1= NUM9(4,1); dpsi_dWs_txt = [TXT9{4,1},char(9),TXT9{4,2}];
    dpsi_dWs_r1= NUM9(4,2);
    dpsi_dWs_l2= NUM9(4,3);
    dpsi_dWs_r2= NUM9(4,4);
    summary_sheet{14} = [dpsi_dWs_txt,char(9),num2str(dpsi_dWs_l1),...
        char(9),num2str(dpsi_dWs_r1),char(9),num2str(dpsi_dWs_l2),...
        char(9),num2str(dpsi_dWs_r2)];
    
    % Steer angle change versus wheel stroke, rad/m
    % (Summary: Toe Change-d/bump (50mm bump) [deg])
    ddel_dWs_l1= NUM9(5,1); ddel_dWs_txt = [TXT9{5,1},char(9),TXT9{5,2}];
    ddel_dWs_r1= NUM9(5,2);
    ddel_dWs_l2= NUM9(5,3);
    ddel_dWs_r2= NUM9(5,4);
    summary_sheet{15} = [ddel_dWs_txt,char(9),num2str(ddel_dWs_l1),...
        char(9),num2str(ddel_dWs_r1),char(9),num2str(ddel_dWs_l2),...
        char(9),num2str(ddel_dWs_r2)];
    
    % Lever ratio
    dqs_dWs_l1= NUM9(6,1); dqs_dWs_txt = [TXT9{6,1},char(9),TXT9{6,2}];
    dqs_dWs_r1= NUM9(6,2);
    dqs_dWs_l2= NUM9(6,3);
    dqs_dWs_r2= NUM9(6,4);
    suspension_sheet{9} = [dqs_dWs_txt,char(9),num2str(dqs_dWs_l1),...
        char(9),num2str(dqs_dWs_r1),char(9),num2str(dqs_dWs_l2),...
        char(9),num2str(dqs_dWs_r2)];
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        
%% Shock Absorber
    % Read parameters
[NUM11,TXT11] = xlsread(INP_name,'L7:O200');
    % Damper relative velocity lookup table
    Damper_v_1 = sprintf('%f\t',NUM11(:,1));
    Damper_v_1 = Damper_v_1(1:end-1);
    Damper_v_1_txt = [TXT11{1,1},char(9),TXT11{2,1}];
    damper_sheet{1} = [Damper_v_1_txt,char(9),Damper_v_1];        
    
    Damper_v_2 = sprintf('%f\t',NUM11(:,3));
    Damper_v_2 = Damper_v_2(1:end-1);
    Damper_v_2_txt = [TXT11{1,3},char(9),TXT11{2,3}];
    damper_sheet{3} = [Damper_v_2_txt,char(9),Damper_v_2];    
    
    % Damper force lookup table
    Damper_F_1 = sprintf('%f\t',NUM11(:,2));
    Damper_F_1 = Damper_F_1(1:end-1);
    Damper_F_1_txt = [TXT11{1,2},char(9),TXT11{2,2}];
    damper_sheet{2} = [Damper_F_1_txt,char(9),Damper_F_1];
    
    Damper_F_2 = sprintf('%f\t',NUM11(:,4));
    Damper_F_2 = Damper_F_2(1:end-1);
    Damper_F_2_txt = [TXT11{1,4},char(9),TXT11{2,4}];
    damper_sheet{4} = [Damper_F_2_txt,char(9),Damper_F_2];
 
%% Spring

    % Read parameters
[NUM12,TXT12]= xlsread(INP_name,1,'Q7:T200');    
    % Spring position lookup table, mm
    Spring_x_1 = sprintf('%f\t',NUM12(:,1));
    Spring_x_1 = Spring_x_1(1:end-1);
    Spring_x_1_txt = [TXT12{1,1},'(',TXT12{2,1},')'];
    spring_sheet{1} = [Spring_x_1_txt,char(9),Spring_x_1];

    Spring_x_2 = sprintf('%f\t',NUM12(:,3));
    Spring_x_2 = Spring_x_2(1:end-1);
    Spring_x_2_txt = [TXT12{1,3},'(',TXT12{2,3},')'];
    spring_sheet{3} = [Spring_x_2_txt,char(9),Spring_x_2];
    
    % Spring force lookup table, N
    Spring_F_1 = sprintf('%f\t',NUM12(:,2));
    Spring_F_1 = Spring_F_1(1:end-1);
    Spring_F_1_txt = [TXT12{1,2},'(',TXT12{2,2},')'];
    spring_sheet{2} = [Spring_F_1_txt,char(9),Spring_F_1];
    
    Spring_F_2 = sprintf('%f\t',NUM12(:,2));
    Spring_F_2 = Spring_F_2(1:end-1);
    Spring_F_2_txt = [TXT12{1,4},'(',TXT12{2,4},')'];
    spring_sheet{4} = [Spring_F_2_txt,char(9),Spring_F_2];

%% Initial Kinematics
% Read data from INP 
[NUM10,TXT10] = xlsread(INP_name,1,'E38:J41');

% (Info: SAI (deg))
beta0_l1 = NUM10(1,1); beta0_txt = [TXT10{1,1},char(9),TXT10{1,2}];
beta0_r1 = NUM10(1,2); 
beta0_l2 = NUM10(1,3); 
beta0_r2 = NUM10(1,4); 
vehicle_info_sheet{6} = [beta0_txt,char(9),num2str(beta0_l1),...
        char(9),num2str(beta0_r1),char(9),num2str(beta0_l2),...
        char(9),num2str(beta0_r2)];

% (Info: Caster (deg))
psi0_l1 = NUM10(2,1); psi0_txt = [TXT10{2,1},char(9),TXT10{2,2}];
psi0_r1 = NUM10(2,2); 
psi0_l2 = NUM10(2,3); 
psi0_r2 = NUM10(2,4); 
vehicle_info_sheet{7} = [psi0_txt,char(9),num2str(psi0_l1),...
        char(9),num2str(psi0_r1),char(9),num2str(psi0_l2),...
        char(9),num2str(psi0_r2)];

% (Info: Toe (mm))
del0_l1 = NUM10(3,1); del0_txt = [TXT10{3,1},char(9),TXT10{3,2}];
del0_r1 = NUM10(3,2); 
del0_l2 = NUM10(3,3); 
del0_r2 = NUM10(3,4); 
vehicle_info_sheet{8} = [del0_txt,char(9),num2str(del0_l1),...
        char(9),num2str(del0_r1),char(9),num2str(del0_l2),...
        char(9),num2str(del0_r2)];

% (Info: Camber (deg))
gam0_l1 = NUM10(4,1); gam0_txt = [TXT10{4,1},char(9),TXT10{4,2}]; 
gam0_r1 = NUM10(4,2); 
gam0_l2 = NUM10(4,3); 
gam0_r2 = NUM10(4,4); 
vehicle_info_sheet{9} = [gam0_txt,char(9),num2str(gam0_l1),...
        char(9),num2str(gam0_r1),char(9),num2str(gam0_l2),...
        char(9),num2str(gam0_r2)];
    
%% Assigning each cell to the input_data
input_data{1} = summary_sheet;
input_data{2} = vehicle_info_sheet;
input_data{3} = suspension_sheet;
input_data{4} = spring_sheet;
input_data{5} = damper_sheet;
input_data{6} = body_sheet;
input_data{7} = steering_sheet;

output = input_data;

cd(current_path); % Back to the current directory 
end