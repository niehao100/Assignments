set max=1000
IF %1 lss 1000 set max=%1
FOR /L %%i IN (0,1,%max%)  DO generate.exe > %%i.in