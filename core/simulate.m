function [ output_data ] = simulate( )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

output_data = cell(3,1);
n1 = 10;
graph1 = cell(n1+3,1);
graph1{1} = ''; %title
graph1{2} = 'Lateral g [g]'; %x-axis
graph1{3} = 'Understeer Gradient [deg/g]'; %y-axis
for i=1:n1    
    graph1{3+i} = [num2str(i),char(9),num2str(2*i)];
end
output_data{1} = graph1;

n2 = 15;
graph2 = cell(n2+3,1);
graph2{1} = ''; %title
graph2{2} = 'Lateral g [g]'; %x-axis
graph2{3} = 'Slip angle [deg]'; %y-axis
for i=1:n2    
    graph2{3+i} = [num2str(i),char(9),num2str(i^2)];
end
output_data{2} = graph2;

table1 = cell(4,1);
table1{1} = ['Steady State Cornering (R = 52.5 m)',char(9),'LF',char(9),'Passat'];
table1{2} = ['US Gradient (deg/g)', char(9),'2.39',char(9),'1.79'];
table1{3} = ['MAX. LATAC (g)', char(9), '0.87', char(9), '0.89'];
table1{4} = ['MAX. LATAC @ Linear region (g)', char(9), '0.58', char(9), '0.67'];

output_data{3} = table1;
end

