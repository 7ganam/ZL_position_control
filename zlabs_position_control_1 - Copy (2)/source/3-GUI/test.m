delete(instrfindall);
com_name = find_arduino_com_windowsOS();
connection = serial('COM28','BaudRate',115200);
fopen(connection);
pause(1) % withouth this the serial print dont have enough time to reach arduino

D=[];
AT=[];
MT=[];

fprintf(connection,'%s',"111*");

while (connection.BytesAvailable ==0)

end


new_reading="";

if (connection.BytesAvailable > 0)
    
        new_reading=(fscanf(connection))
        if strtrim(new_reading)=="r"
              ok=1;
        end

end
