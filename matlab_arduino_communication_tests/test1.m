delete(instrfindall);
connection = serial('COM28','BaudRate',115200);
fopen(connection);
A=[];
while (connection.BytesAvailable ==0)

end

tic
while connection.BytesAvailable >0
     A =  [A str2num(fscanf(connection))];
end
toc
