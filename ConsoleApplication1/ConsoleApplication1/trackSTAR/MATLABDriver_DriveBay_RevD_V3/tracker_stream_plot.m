function tracker_stream_plot(OptDispl)
% tracker_stream_plot:  designed to place the tracker in a stream mode. 
% input: OptDispl
%        (OptDispl = 1) => sensor position is displayed on the MATLAB
%        command window
%        (OptDispl = 0) => sensor position is not displayed
% Ascension Technology Corporation 

global SensorNumAttached; % number of attached sensors
global measurementRate;  % measurement rate
global hMainfig; % figure handler
global gui;
global numBoards;

clf;% clear figure
setup_views    % load pull downmenu for pre defined views

gui.start_proc = 0;
gui.stop_proc  = 0;

if length(findobj(gcf,'Label','Run tracker'))==1
    hMainfig('Run tracker', 'off');
end
hfig = figure('Position',[408 327 360 244],...
                'MenuBar','none', ...
                'Name','Procedure Menu',...
                'NumberTitle','off');
% Start button
hpush_start = uicontrol(hfig,'Style','pushbutton');
set(hpush_start,'Position',[20 200 150 20]); %[left bottom width height]
set(hpush_start,'String','Start STREAM I/O');
set(hpush_start,'Callback','gui.start_proc=1;');

% stop button
hpush_stop = uicontrol(hfig,'Style','pushbutton');
set(hpush_stop,'Position',[20 150 150 20]); %[left bottom width height]
set(hpush_stop,'String','Stop STREAM I/O');
set(hpush_stop,'Callback','gui.stop_proc=1;');
set(hpush_stop,'Enable','off');



while (gui.start_proc == 0)
    drawnow
    disp('waiting to start');
    clc;
end
set(hpush_start,'Enable','off');
set(hpush_stop,'Enable','on');

% Get synchronous Record
% Initialize structure
for kk = 0:(4 * numBoards - 1),
   evalc(['sm.x' num2str(kk) '=0']);
   evalc(['sm.y' num2str(kk) '=0']);
   evalc(['sm.z' num2str(kk) '=0']);
   evalc(['sm.a' num2str(kk) '=0']);
   evalc(['sm.e' num2str(kk) '=0']);
   evalc(['sm.r' num2str(kk) '=0']);
   evalc(['sm.time' num2str(kk) '=0']);
   evalc(['sm.quality' num2str(kk) '=0']);  
end

if numBoards == 1
    Record  = libstruct('tagDOUBLE_POSITION_ANGLES_TIME_Q_RECORD_AllSensors_Four', sm);  
    pRecord = libpointer('tagDOUBLE_POSITION_ANGLES_TIME_Q_RECORD_AllSensors_Four', Record);
elseif numBoards == 2
    Record  = libstruct('tagDOUBLE_POSITION_ANGLES_TIME_Q_RECORD_AllSensors_Eight', sm);  
    pRecord = libpointer('tagDOUBLE_POSITION_ANGLES_TIME_Q_RECORD_AllSensors_Eight', Record);
elseif numBoards == 3
    Record  = libstruct('tagDOUBLE_POSITION_ANGLES_TIME_Q_RECORD_AllSensors_Twelve', sm);  
    pRecord = libpointer('tagDOUBLE_POSITION_ANGLES_TIME_Q_RECORD_AllSensors_Twelve', Record);
else 
    Record  = libstruct('tagDOUBLE_POSITION_ANGLES_TIME_Q_RECORD_AllSensors_Sixting', sm);  
    pRecord = libpointer('tagDOUBLE_POSITION_ANGLES_TIME_Q_RECORD_AllSensors_Sixting', Record);
end


Counter    = 0;% number of samples
senSorPre  = ones(1,4*numBoards);% Index sensors present 
NumSenPres = sum(SensorNumAttached);% number of sensors present

while (gui.stop_proc == 0 )
    clc
    % Get synchronous Record
    Error   = calllib('ATC3DG', 'GetSynchronousRecord',  hex2dec('ffff'), Record, 4*numBoards*64);
    errorHandler(Error);
    Counter = Counter + 1;
    for count = 1:4*numBoards
        evalc(['Pos(Counter, 1, count) ='  'Record.x' num2str(count - 1)]);
        evalc(['Pos(Counter, 2, count) ='  'Record.y' num2str(count - 1)]);
        evalc(['Pos(Counter, 3, count) ='  'Record.z' num2str(count - 1)]);
        evalc(['Ang(Counter, 1, count) ='  'Record.a' num2str(count - 1)]);
        evalc(['Ang(Counter, 2, count) ='  'Record.e' num2str(count - 1)]);
        evalc(['Ang(Counter, 3, count) ='  'Record.r' num2str(count - 1)]);
        evalc(['time(Counter, 1, count) ='  'Record.time' num2str(count - 1)]);        
        evalc(['Quality(Counter, 1, count) ='  'Record.Quality' num2str(count - 1)]);    

        if (OptDispl==1)
            display(sprintf('\nSensor number %g position in inches: ',...
                    count))
            disp([Pos(Counter, 1, count) Pos(Counter, 2, count)...
                  Pos(Counter, 3, count)])
        end
        drawnow  % forces Matlab to evaluate Callback in figure
    end
    TimStam(Counter)  = Record.time0;        
end
indsenSorPre =  find(SensorNumAttached == 1);

set(hpush_stop,'Enable','off'); % show that button has been pressed
close(hfig)


% Define an array of colors for each sensor
colorstr_ar = [{'r'} {'b'} {'g'} {'m'} {'k'} {'c'}];
while length(colorstr_ar)<NumSenPres  
    colorstr_ar = [colorstr_ar colorstr_ar]; % repeat colors if array is not long enough
end

% plot trajectory of each 
for count=1:NumSenPres
    colorstr = char(colorstr_ar(count));
    plot3(Pos(indsenSorPre(count):4:Counter - 1, 1,indsenSorPre(count)),...
          Pos(indsenSorPre(count):4:Counter - 1, 2,indsenSorPre(count)), ...
          Pos(indsenSorPre(count):4:Counter - 1, 3,indsenSorPre(count)),colorstr);
    drawnow;
    hold on;
end    

% define labels and titles
xlabel('X'); ylabel('Y'); zlabel('Z');
title_str = ['Position of Sensor: ' int2str(Counter) ' points, sampled at approx. ' ...
              num2str(measurementRate) ' hz'];
title(title_str);

% setup legend
for count=1:NumSenPres
    legend_str(count) = {['Sensor ' int2str(indsenSorPre(count))]};    
end        
legend(legend_str);

% Force the tracker system to come out of STREAM mode by issuing the 
% command GetSensorStatus
for count = 1:4*numBoards
    if SensorNumAttached(count)
        Error1 = calllib('ATC3DG', 'GetSensorStatus', count - 1);
        errorHandler(Error1);
    end
end





