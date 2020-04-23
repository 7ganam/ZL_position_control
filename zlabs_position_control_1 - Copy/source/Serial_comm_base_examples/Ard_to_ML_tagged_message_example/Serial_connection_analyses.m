delete(instrfindall);
com_name = find_arduino_com_windowsOS();
connection = serial('COM28','BaudRate',115200);
fopen(connection);

D=[];
AT=[];
MT=[];
while (connection.BytesAvailable ==0)

end


new_reading="";

if (connection.BytesAvailable > 0)
    tic
    while strtrim(new_reading) ~= "e"
        new_reading=(fscanf(connection));
        if strtrim(new_reading)=="s"
               %-----------------------%
             new_reading=(fscanf(connection));
             d=str2num(new_reading);
             D =  [D d];
               %-----------------------%
             new_reading=(fscanf(connection));
             at=str2num(new_reading);
             AT =  [AT at];
               %-----------------------%
             MT = [ MT toc];
        end

    end
end
MT=MT*1000000;
plot(AT,MT,"*");
toc
