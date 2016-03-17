% real_time_Animation_Text:  Implements "real-time" data acquisition (Note: 
% we are using asynchronous mode) and plotting (called from pull down menu)
% Ascension Technology Corporation 


global SensorNumAttached; % Attached sensors number
global hMainfig;% Main figure
global tracker_run;    % starts and stops I/O
global numBoards;% number of boards
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
        'Callback', 'real_time_plot_text;');
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

% creates a uipanel to display sensor data
hp   = uipanel('parent',hMainfig,...
             'Position',[.0 .0 1 1]);%[.0 .75 1 1]);
           
hbsx = uicontrol('Style', 'text','Parent',hp,'String','x', ...
                 'fontSize', 16,...                 
                 'Position',[132 650 100 26]);
pox = getpixelposition(hbsx);             
             
hbsy = uicontrol('Style', 'text','Parent',hp,'String','y', ...
                 'fontSize', 16,...                 
                 'Position',[110 0 0 0] + pox);
poy = getpixelposition(hbsy);  


hbsz = uicontrol('Style', 'text','Parent',hp,'String','z', ...
                 'fontSize', 16,...                 
                 'Position',[100 0 0 0] + poy);
poz = getpixelposition(hbsz);             

hbsa = uicontrol('Style', 'text','Parent',hp,'String','azimuth', ...
                 'fontSize', 16,...                 
                 'Position',[90 0 0 0] + poz);
poa = getpixelposition(hbsa);             

hbse = uicontrol('Style', 'text','Parent',hp,'String','elevation', ...
                 'fontSize', 16,...                 
                 'Position',[100 0 0 0] + poa);
poe = getpixelposition(hbse);        

hbsr = uicontrol('Style', 'text','Parent',hp,'String','roll', ...
                 'fontSize', 16,...                 
                 'Position',[100 0 0 0] + poe);
por = getpixelposition(hbsr);  

hbsq = uicontrol('Style', 'text','Parent',hp,'String','quality', ...
                 'fontSize', 16,...                 
                 'Position',[120 0 0 0] + por);
poq = getpixelposition(hbsq);             

  
posShift = [18 610 100 26];%evalc(['pos' num2str(kk) ]) - 30;

for kk = 1: 4 * numBoards ,
    tempname = (['sensor '  num2str(kk) ]);
    temp = uicontrol('Style', 'text','Parent',hp,...
    'String',tempname,...
             'fontSize', 16,...
             'Position', posShift );
    evalc(['hbs' num2str(kk) '= temp' ]);  
    temppos = getpixelposition(temp);
    evalc(['pos' num2str(kk)  ' = temppos' ]); 
    posShift = posShift - [0 40 0 0];
             
end


for kk =1:4 * numBoards
    evalc(['s' num2str(kk) '=  num2str(0)']); 
    evalc(['xs' num2str(kk) '=  num2str(0)']); 
    evalc(['ys' num2str(kk) '=  num2str(0)']); 
    evalc(['zs' num2str(kk) '=  num2str(0)']); 
    evalc(['as' num2str(kk) '=  num2str(0)' ]); 
    evalc(['es' num2str(kk) '=  num2str(0)']); 
    evalc(['rs' num2str(kk) '=  num2str(0)']); 
    evalc(['qs' num2str(kk) '=  num2str(0)']); 
end

% x-position
for kk = 1: 4 * numBoards ,
    tempname = (['x'  num2str(kk) ]);
    temppos  =  eval(['[120 0 0 0]  +'  'pos' num2str(kk)]);
    temp = uicontrol('Style', 'text','Parent',hp,...
    'String', tempname,...
             'fontSize', 12,...
             'Position', temppos);%[120 0 0 0]  + ['pos' num2str(kk)] );
    evalc(['hbsx' num2str(kk) '= temp' ]);  
    temppos = getpixelposition(temp);
    evalc(['posx' num2str(kk)  ' = temppos' ]);                
end

% y-position
for kk = 1: 4 * numBoards ,
    tempname = (['y'  num2str(kk) ]);
    temppos  =  eval(['[100 0 0 0]  +'  'posx' num2str(kk)]);
    temp = uicontrol('Style', 'text','Parent',hp,...
    'String', tempname,...
             'fontSize', 12,...
             'Position', temppos);
    evalc(['hbsy' num2str(kk) '= temp' ]);  
    temppos = getpixelposition(temp);
    evalc(['posy' num2str(kk)  ' = temppos' ]);                
end

% z-position
for kk = 1: 4 * numBoards ,
    tempname = (['z'  num2str(kk) ]);
    temppos  =  eval(['[100 0 0 0]  +'  'posy' num2str(kk)]);
    temp = uicontrol('Style', 'text','Parent',hp,...
    'String', tempname,...
             'fontSize', 12,...
             'Position', temppos);
    evalc(['hbsz' num2str(kk) '= temp' ]);  
    temppos = getpixelposition(temp);
    evalc(['posz' num2str(kk)  ' = temppos' ]);                
end

% azimuth data
for kk = 1: 4 * numBoards ,
    tempname = (['a'  num2str(kk) ]);
    temppos  =  eval(['[100 0 0 0]  +'  'posz' num2str(kk)]);
    temp = uicontrol('Style', 'text','Parent',hp,...
    'String', tempname,...
             'fontSize', 12,...
             'Position', temppos);
    evalc(['hbsa' num2str(kk) '= temp' ]);  
    temppos = getpixelposition(temp);
    evalc(['posa' num2str(kk)  ' = temppos' ]);                
end

% elevation data
for kk = 1: 4 * numBoards ,
    tempname = (['e'  num2str(kk) ]);
    temppos  =  eval(['[100 0 0 0]  +'  'posa' num2str(kk)]);
    temp = uicontrol('Style', 'text','Parent',hp,...
    'String', tempname,...
             'fontSize', 12,...
             'Position', temppos);
    evalc(['hbse' num2str(kk) '= temp' ]);  
    temppos = getpixelposition(temp);
    evalc(['pose' num2str(kk)  ' = temppos' ]);                
end

% roll data
for kk = 1: 4 * numBoards ,
    tempname = (['r'  num2str(kk) ]);
    temppos  =  eval(['[100 0 0 0]  +'  'pose' num2str(kk)]);
    temp = uicontrol('Style', 'text','Parent',hp,...
    'String', tempname,...
             'fontSize', 12,...
             'Position', temppos);
    evalc(['hbsr' num2str(kk) '= temp' ]);  
    temppos = getpixelposition(temp);
    evalc(['posr' num2str(kk)  ' = temppos' ]);                
end

% quality data
for kk = 1: 4 * numBoards ,
    tempname = (['q'  num2str(kk) ]);
    temppos  =  eval(['[100 0 0 0]  +'  'posr' num2str(kk)]);
    temp = uicontrol('Style', 'text','Parent',hp,...
    'String', tempname,...
             'fontSize', 12,...
             'Position', temppos);
    evalc(['hbsq' num2str(kk) '= temp' ]);  
    temppos = getpixelposition(temp);
    evalc(['posq' num2str(kk)  ' = temppos' ]);                
end

% Initialize sensors data to zero
for kk = 1: 4 * numBoards ,
    set(eval(['hbsx' num2str(kk)]), 'String', num2str(eval(['xs' num2str(kk)])) );
    set(eval(['hbsy' num2str(kk)]), 'String', num2str(eval(['ys' num2str(kk)])) );
    set(eval(['hbsz' num2str(kk)]), 'String', num2str(eval(['zs' num2str(kk)])) );
    set(eval(['hbsa' num2str(kk)]), 'String', num2str(eval(['as' num2str(kk)])) );
    set(eval(['hbse' num2str(kk)]), 'String', num2str(eval(['es' num2str(kk)])) );
    set(eval(['hbsr' num2str(kk)]), 'String', num2str(eval(['es' num2str(kk)])) );
    set(eval(['hbsq' num2str(kk)]), 'String', num2str(eval(['qs' num2str(kk)])) );    
end


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
    evalc(['Pos(1, count) ='  'Record.x' num2str(count - 1)]);
    evalc(['Pos(2, count) ='  'Record.y' num2str(count - 1)]);
    evalc(['Pos(3, count) ='  'Record.z' num2str(count - 1)]);
    evalc(['Ang(1, count) ='  'Record.a' num2str(count - 1)]);
    evalc(['Ang(2, count) ='  'Record.e' num2str(count - 1)]);
    evalc(['Ang(3, count) ='  'Record.r' num2str(count - 1)]);
    evalc(['time( count) ='  'Record.time' num2str(count - 1)]);        
    evalc(['Quality( count) ='  'Record.Quality' num2str(count - 1)]); 
end

for count = 1:4*numBoards
    if SensorNumAttached(count)
        set(eval(['hbsx' num2str(count)]), 'String', num2str(eval(['Record.x' num2str(count - 1)]), '%2.2f') );
        set(eval(['hbsy' num2str(count)]), 'String', num2str(eval(['Record.y' num2str(count - 1)]), '%2.2f') );
        set(eval(['hbsz' num2str(count)]), 'String', num2str(eval(['Record.z' num2str(count - 1)]), '%2.2f') );
        set(eval(['hbsa' num2str(count)]), 'String', num2str(eval(['Record.a' num2str(count - 1)]), '%2.2f') );
        set(eval(['hbse' num2str(count)]), 'String', num2str(eval(['Record.e' num2str(count - 1)]), '%2.2f') );
        set(eval(['hbsr' num2str(count)]), 'String', num2str(eval(['Record.r' num2str(count - 1)]), '%2.2f') );
        set(eval(['hbsq' num2str(count)]), 'String', num2str(eval(['Record.Quality' num2str(count - 1)]), '%2.2f') );
        drawnow  % forces Matlab to evaluate Callback in figure
    else
            senSorPre(count) = 0;                      
    end
end
indsenSorPre =  find(senSorPre == 1);

% Free memory
clear Record ;  
clear  pRecord;


