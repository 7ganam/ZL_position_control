delete(instrfindall);
com_name = find_arduino_com_windowsOS();
connection = serial('COM28','BaudRate',115200);
fopen(connection);
A=[];
B=[];

while (connection.BytesAvailable ==0)

end


new_point=-1;

if (connection.BytesAvailable > 0)
    tic
    while new_point ~= -2
     new_point=str2num(fscanf(connection));
     A =  [A new_point];
     B = [ B toc];
    end
end
B=B*1000000;
plot(A,B,"*");

toc
