state="connection_checking";
while (1)
    %% connection_checking
    if (state=="connection_checking")
        state
        %     1-creat connection to arduino 
        %     2-sends 111.1 chars to the arduino and waits for "RighT" string back
        %     3-if step 2 completed successfully it sets the FSM state to "resetting"
        delete(instrfindall);
        com_name = find_arduino_com_windowsOS();
        connection = serial('COM28','BaudRate',115200);
        fopen(connection);
        pause(1) % withouth this the serial print dont have enough time to reach arduino

        
        %send a message to make sure the arduino connected has the FSM code
        %on it
        fprintf(connection,'%s',"111.1");
        % wait till there is data in the serial input buffer
        while (connection.BytesAvailable ==0)
        end
        
        %read the data
        new_reading="";
        if (connection.BytesAvailable > 0)
            new_reading=(fscanf(connection));
            if strtrim(new_reading)=="RighT"
                state="resetting";
            end
        end

    end
    %% resetting
    if (state=="resetting")
        state
        while (connection.BytesAvailable ==0)
        end
        
        %read the data
        new_reading="";
        if (connection.BytesAvailable > 0)
            new_reading=(fscanf(connection));
            if strtrim(new_reading)=="ReseteD"
                state="waiting_for_go_sig";
            end
        end
    end
    %% waiting_for_go_sig
    if (state=="waiting_for_go_sig")
        state
        state="sending_gains";
    end
    %% sending_gains
    
    kp=10;
    ki=0;
    kd=.4;
    set_point=90;
    if (state=="sending_gains")
        state
        fprintf(connection,'%s',"222.2");
        fprintf(connection,'%s',"*");
        fprintf(connection,'%s',num2str(kp));
        fprintf(connection,'%s',"*");
        fprintf(connection,'%s',num2str(ki));
        fprintf(connection,'%s',"*");
        fprintf(connection,'%s',num2str(kd));
        fprintf(connection,'%s',"*");
        fprintf(connection,'%s',num2str(set_point));
        state="waiting_for_validation";
    end
    %% waiting_for_validation
    if (state=="waiting_for_validation")
        state
        if (connection.BytesAvailable > 0)
           
                new_reading=(fscanf(connection));
                if strtrim(new_reading)=="GainS"
                    kp_tag=strtrim(fscanf(connection));
                    if kp_tag=="kp"
                       recived_kp=str2num(fscanf(connection));
                    end
                    ki_tag=strtrim(fscanf(connection));
                    if ki_tag=="ki"
                       recived_ki=str2num(fscanf(connection));
                    end
                    kd_tag=strtrim(fscanf(connection));
                    if kd_tag=="kd"
                       recived_kd=str2num(fscanf(connection));
                    end
                    sp_tag=strtrim(fscanf(connection));
                    if sp_tag=="sp"
                       recived_set_point=str2num(fscanf(connection));
                    end
                   fprintf(connection,'%s',"444.4");
                   plot(0,0,"*")
                   pause(10/1000000);
                   hold on;
                   state="graphing";
                end
        end


    end
    %% graphing
    if (state=="graphing")
%         state
        Data_Array=[];
        Arduino_Time_Array=[];
        Matlab_Time_Array=[];
        hold on;
 
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
                     data_point=str2num(new_reading);
                     Data_Array =  [Data_Array data_point];
                       %-----------------------%
                     new_reading=(fscanf(connection));
                     arduin_time_point=str2num(new_reading);
                     Arduino_Time_Array =  [Arduino_Time_Array arduin_time_point];
                       %-----------------------%
                     matlab_time_point=toc*1000000;
                     Matlab_Time_Array = [ Matlab_Time_Array matlab_time_point];

%                      plot(arduin_time_point,matlab_time_point,"*");
                     plot(arduin_time_point,data_point,"*");
                     pause(1/1000000);        %line 11

                end

            end
        end
    end
    %% stop_button_clicked
    if (state=="stop_button_clicked")
        state
    end

end