delete(instrfindall);
com_name = find_arduino_com_windowsOS();
connection = serial('COM28','BaudRate',115200);
fopen(connection);
D=[];
AT=[];
MT=[];
hold on;
plot(0,0,"*")
             pause(10/1000000); 
while (connection.BytesAvailable ==0)

end


new_reading="";

if (connection.BytesAvailable > 0)
    tic
    while strtrim(new_reading) ~= "e"
        new_reading=(fscanf(connection));
%         erase(new_reading,newline)
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
             mt=toc*1000000;
             MT = [ MT mt];
             
             plot(at,mt,"*");
             pause(1/1000000);        %line 11

        end

    end
end
% MT=MT*1000000;
% plot(AT,MT,"o");
toc
