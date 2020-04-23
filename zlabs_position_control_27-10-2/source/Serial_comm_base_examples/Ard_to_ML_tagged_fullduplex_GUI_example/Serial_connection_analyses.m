delete(instrfindall);
com_name = find_arduino_com_windowsOS();
connection = serial(com_name,'BaudRate',115200);
fopen(connection);
D=[];
AT=[];
MT=[];
hold on;
plot(0,0,"*")
pause(1/10000000); 
while (connection.BytesAvailable ==0)

end
        new_reading="";

state="graphing"
            i=0;
while(1)
    %% graphing 
    if state=="graphing"

        if (connection.BytesAvailable > 0)
            tic

                new_reading=(fscanf(connection));
                i=i+1
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
                     MT = [ MT toc*1000000];
                     plot(at,d,'*');
                     pause(1/10000000);
                end
                if i== 50
                    
                   fprintf(connection,'%s',"145"); 
                   state="end";
                   tic
                end

            
        end
    end
    %% end
    if state=="end"
        break
    end
end

toc
