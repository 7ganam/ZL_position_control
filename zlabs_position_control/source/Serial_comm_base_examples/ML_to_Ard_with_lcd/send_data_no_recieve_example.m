delete(instrfindall);
com_name = find_arduino_com_windowsOS();
connection = serial(com_name,'BaudRate',112500);
fopen(connection)
pause(1) % withouth this the serial print dont have enough time to reach arduino
fprintf(connection,'%s',"gains");
