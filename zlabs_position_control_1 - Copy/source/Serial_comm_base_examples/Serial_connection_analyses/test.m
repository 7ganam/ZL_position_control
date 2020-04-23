delete(instrfindall);
com_name = find_arduino_com_windowsOS();
connection = serial('COM28','BaudRate',115200);
fopen(connection);
D=[];
MT=[];
while (connection.BytesAvailable ==0)

end


new_reading="";

if (connection.BytesAvailable > 0)
    tic
    while str2num(new_reading) ~= -2
        new_reading=(fscanf(connection))
        A =  [A new_reading];
    end
end

