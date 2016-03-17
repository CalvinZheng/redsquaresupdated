clc
[notfound, warnings] = loadlibrary( '/Users/jhaughey/Desktop/libATC3DGDLL','/Users/jhaughey/Desktop/ATC3DG.h')
libfunctions libATC3DGDLL -full

% Init
rc = calllib( 'libATC3DGDLL', 'InitializeBIRDSystem')
if rc == 0
    disp('Init success')
else
    unloadlibrary libATC3DGDLL
    disp('Init failure')
    break
end

% Start 1st transmitter
tx = 0
rc = calllib( 'libATC3DGDLL', 'SetSystemParameter', 0, tx, 2)
if rc == 0
    disp('Start TX success')
else
    disp('Start TX failure')
    calllib( 'libATC3DGDLL', 'CloseBIRDSystem')
    unloadlibrary libATC3DGDLL
    break
end

% Get a data record from sensor #1
mpa = [ 0, 0, 0, 0, 0, 0]
cpa = libpointer('doublePtr', mpa)
rc = calllib( 'libATC3DGDLL', 'GetAsynchronousRecord', 0, cpa, 48)
if rc == 0
    disp('Get record success')
    get(cpa)
else
    disp('Get record failure')
end

% cleanup
clear cpa
calllib( 'libATC3DGDLL', 'CloseBIRDSystem')
unloadlibrary libATC3DGDLL
