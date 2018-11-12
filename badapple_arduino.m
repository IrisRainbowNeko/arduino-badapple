obj=VideoReader('E:/badapple/badapple_1.mp4');%读取视频
framecount=obj.NumberOfFrames;%获取总帧数
fid=fopen('E:/badapple/arduino.bin','ab');%创建输出文件
for u=0:framecount%循环遍历每一帧
    disp(u);
    frame=imresize(read(obj,u),[64,85]);%读取当前帧图像，并压缩至85x64
    data_bin=frame(:,:,1)>127;%二值化图像
    data_bin=data_bin(:);%转为列向量
    len=length(data_bin);%获取列向量长度
    %一个字节是8位，所以宽度要是8的倍数，这里宽度85，要补3列0
    str=num2str(reshape([reshape(data_bin,64,len/64),zeros(64,3)]',8,(64*3+len)/8)');
     res=bin2dec(str);
     fwrite(fid,res,'uchar');
%      image(frame);%用image函数绘图
%      axis image off%保持宽高比，并隐藏坐标轴
%      getframe;%显示画面到屏幕
end
fclose(fid);