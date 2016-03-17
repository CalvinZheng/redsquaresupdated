% real_time_Animation_Graphic:  Implements "real-time" data acquisition (Note: 
% we are using asynchronous mode) and plotting (called from pull down menu)
% Ascension Technology Corporation 


global SensorNumAttached; % Attached sensors number
global hMainfig;% Main figure
global tracker_run;    % starts and stops I/O
global numBoards; % number of boards
global hp;

clf;% clear figure
axes('position',[.1  .1  .8  .6])
view(3)
axis vis3d  % set axis for proper 3D visulization
setup_views    % load pull downmenu for pre defined views

NumSenPres = sum(SensorNumAttached);

% hMainfig;
senSorPre = ones(1, 4*numBoards);
TRUE=1;FALSE=0;ON=1;OFF=0;
X=1;Y=2;Z=3;

tracker_run = OFF;    % set to stop during setup
view(-37.5,30)
axis vis3d  % set axis for proper 3D visulization


% Create Pull Down Menu to Start/Stop I?O if not yet up
if isempty(findobj(gcf,'Label','Run tracker'))
    % Create a new a menu on the menu bar at the top of the figure window
    % with the handle hfig
    h_menu = uimenu(gcf,'Label','Run tracker');
    
    % submenus are added by specfiying the handle to the column menu
    uimenu(h_menu,'Label','Start', ...
        'Callback', 'real_time_plot_graphic;');
    uimenu(h_menu,'Label','Stop', ...
        'Callback', 'tracker_run=0;');
end
% uimenu(hMainfig,'Label','Run tracker','Enable','on');
title('Start Real Time tracker I/O from "Run tracker" Pull Down Menu',...
    'FontWeight','Bold')
% define labels and titles
xlabel('X');
ylabel('Y');
zlabel('Z');

axis([5 25 -12 12 -15 15]);
axis square;


% Setup Handlge Graphics for high speed animation
vec_length = 1;  % length of vector on plot showing tracker axes

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

% Define an array of colors for each tracker
colorstr_ar = [{'r'} {'b'} {'g'} {'m'} {'y'} {'c'} ];
while length(colorstr_ar)<NumSenPres  
    colorstr_ar = [colorstr_ar colorstr_ar]; % repeat colors if array is not long enough
end
hold on

% Get synchronous Record
Error   = calllib('ATC3DG', 'GetSynchronousRecord',  hex2dec('ffff'), Record, 4*numBoards*64);
errorHandler(Error);

for count = 1:4*numBoards
    evalc(['Pos(count, 1) ='  'Record.x' num2str(count - 1)]);
    evalc(['Pos(count, 2) ='  'Record.y' num2str(count - 1)]);
    evalc(['Pos(count, 3) ='  'Record.z' num2str(count - 1)]);
    evalc(['Ang(count, 1) ='  'Record.a' num2str(count - 1)]);
    evalc(['Ang(count, 2) ='  'Record.e' num2str(count - 1)]);
    evalc(['Ang(count, 3) ='  'Record.r' num2str(count - 1)]);
    evalc(['time( count) ='  'Record.time' num2str(count - 1)]);        
    evalc(['Quality( count) ='  'Record.Quality' num2str(count - 1)]); 
end

for count = 1:4*numBoards
    if ~SensorNumAttached(count)
        senSorPre(count) = 0;                      
    end
end
indsenSorPre =  find(senSorPre == 1);
        
for itracker=1:NumSenPres 
    pos = Pos(indsenSorPre(itracker),X:Z);
    ang = Ang(indsenSorPre(itracker),X:Z);
    R = tracker_Rot(ang* 0.017453292519943);            % Calculate Rotation matrix R whose columsn are the unit axes of each tracker coordinate system
    xvec = pos' + R(:,X)*vec_length;  
    yvec = pos' + R(:,Y)*vec_length;
    zvec = pos' + R(:,Z)*vec_length;
    
    colorstr = char(colorstr_ar((itracker)));
    hreal_time_xvec(indsenSorPre(itracker)) = plot3([pos(X);xvec(X)],[pos(Y);xvec(Y)],[pos(Z);xvec(Z)],colorstr,'EraseMode','xor');
    hreal_time_yvec(indsenSorPre(itracker)) = plot3([pos(X);yvec(X)],[pos(Y);yvec(Y)],[pos(Z);yvec(Z)],colorstr,'EraseMode','xor');
    hreal_time_zvec(indsenSorPre(itracker)) = plot3([pos(X);zvec(X)],[pos(Y);zvec(Y)],[pos(Z);zvec(Z)],colorstr,'EraseMode','xor');
    
    
    hreal_time_xtext(indsenSorPre(itracker)) = text(xvec(X),xvec(Y),xvec(Z),['x' int2str(indsenSorPre(itracker))],'Color',colorstr,'EraseMode','xor');
    hreal_time_ytext(indsenSorPre(itracker)) = text(yvec(X),yvec(Y),yvec(Z),['y' int2str(indsenSorPre(itracker))],'Color',colorstr,'EraseMode','xor');
    hreal_time_ztext(indsenSorPre(itracker)) = text(zvec(X),zvec(Y),zvec(Z),['z' int2str(indsenSorPre(itracker))],'Color',colorstr,'EraseMode','xor');
end 

axis vis3d  % set axis for proper 3D visulization

% Free memory
clear Record ;  
clear  pRecord;


