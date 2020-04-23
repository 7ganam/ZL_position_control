delete(instrfindall);
com_name = find_arduino_com_windowsOS();
tic
connection = serial(com_name,'BaudRate',112500);
toc
tic
fopen(connection)
toc