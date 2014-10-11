function realcapture = user_camera()
% 使用imaqhwinfo可返回各视频适配器的信息。
% 例如：
% InstalledAdaptors: {'matrox'  'winvideo'}
%         MATLABVersion: '7.4 (R2007a)'
%           ToolboxName: 'Image Acquisition Toolbox'
%        ToolboxVersion: '2.1 (R2007a)'

% 使用 info = imaqhwinfo(adaptor)可返回适配器信息 
% 例如：
% info = imaqhwinfo('winvideo') 返回
%        AdaptorDllName: [1x73 char]
%     AdaptorDllVersion: '2.1 (R2007a)'
%           AdaptorName: 'winvideo'
%             DeviceIDs: {[1]}
%            DeviceInfo: [1x1 struct]

% 使用 info = imaqhwinfo(adaptor, device_id) 可返回对应设备信息
% 例如：
% dev_info = imaqhwinfo('winvideo', 1)返回
%           DefaultFormat: 'RGB555_128x96'
%     DeviceFileSupported: 0
%              DeviceName: 'IBM PC Camera'
%                DeviceID: 1
%   VideoInputConstructor: 'videoinput('winvideo', 1)'
%  VideoDeviceConstructor: 'imaq.VideoDevice('winvideo', 1)'       
%        SupportedFormats: {1x34 cell}

% 用 obj = videoinput(adaptor, device_id)可获得设备对象
% 如：obj = videoinput('winvideo', 1);
% 然后 imaqhwinfo(obj)可返回对象信息
% 例如：
% obj_info = imaqhwinfo(obj)返回
%                 AdaptorName: 'winvideo'
%                  DeviceName: 'IBM PC Camera'
%                   MaxHeight: 96
%                    MaxWidth: 128
%              NativeDataType: 'uint8'
%                TotalSources: 1
%     VendorDriverDescription: 'Windows WDM Compatible Driver'
%         VendorDriverVersion: 'DirectX 9.0'

% 用img = getsnapshot(obj);可获得摄像头截图，得到的是
% RGB图像还是YCbCr图像与摄像头有关，可通过上面的例子用imaqhwinfo查看

%% 请在下面修改你的代码
    % 嗯我用的是IP摄像头
    realcapture = imread('http://10.148.186.195:8080/shot.jpg');
    [M,~,~] = size(realcapture);
    realcapture = realcapture(1:M,1:M/3*4,:);
%     figure(3);
%     imshow(realcapture);
end