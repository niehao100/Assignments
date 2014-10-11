vinfo = imaqhwinfo; 
video_obj = videoinput(vinfo.InstalledAdaptors{1}, 1);
preview(video_obj);