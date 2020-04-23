state="connection_checking";
while(1)
    
if (state=="connection_checking")
        state
        %     1-creat connection to arduino 
        %     2-sends 111.1 chars to the arduino and waits for "RighT" string back
        %     3-if step 2 completed successfully it sets the FSM state to "resetting"
        delete(instrfindall);
        com_name = find_arduino_com_windowsOS();
        connection = serial(com_name,'BaudRate',115200);
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
        
    end



end