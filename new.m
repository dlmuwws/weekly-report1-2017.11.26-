clc  
clear  
close all   
img_original = imread('E:\Desktop\timg.jpg');%读入图像  
figure,imshow(img_original);    %显示原图
Img=rgb2gray(img_original);  
figure,imshow(Img);  
Img=double(Img);  
%% 各个参数  
c1=zeros(1,15);c2=zeros(1,15);c3=zeros(1,15); %c存放每次迭代的聚类中心值  
% 初始聚类中心  
c1(1)=8;    
c2(1)=20;    
c3(1)=80;  
%分为三类  
k=3;     
[m,n]=size(Img);  
%记录迭代次数  
times=0;  
%存储分类标识  取值为1 2 3  
class=zeros(m,n);   
%存储聚类结果  
result=zeros(m,n);  
%存放每类的像素个数和元素总和  
num1=0;num2=0;num3=0;  
sum1=0;sum2=0;sum3=0;  
%先任意给定可以使循环开始的大于1的聚类中心间距值  
d1=2;d2=2;d3=2;  
%% 迭代部分  
tic  
while((d1>0.1||d2>0.1||d3>0.1)&times<15)   %限制迭代次数  
       times=times+1  
%%%%%%%%%%%%%%%%%归类%%%%%%%%%%%%%%%%%%%%%%%%%  
       for i=1:m  
           for j=1:n  
               dis1=(Img(i,j)-c1(times))^2;  %欧式距离   
               dis2=(Img(i,j)-c2(times))^2;  
               dis3=(Img(i,j)-c3(times))^2;  
               min_dis=min([dis1,dis2,dis3]);  
               switch(min_dis)  
                   case dis1  
                       class(i,j)=1;  
                       num1=num1+1;  
                       sum1=sum1+Img(i,j);  
                   case dis2  
                       class(i,j)=2;  
                        num2=num2+1;  
                        sum2=sum2+Img(i,j);  
                   case dis3  
                       class(i,j)=3;  
                        num3=num3+1;  
                        sum3=sum3+Img(i,j);  
               end     
           end  
       end  
       %e_new=sqrt(min_dis);  
%调整新的聚类中心  
c1(times+1)=sum1/num1;  
c2(times+1)=sum2/num2;  
c3(times+1)=sum3/num3;  
%两次之间的聚类中心变化大小 以此做为终止迭代的标准  
d1=abs(c1(times)-c1(times+1));  
d2=abs(c1(times)-c1(times+1));  
d3=abs(c1(times)-c1(times+1));  
%在下一次迭代前将每类的加和置0  
sum1=0;  
sum2=0;  
sum3=0;  
num1=0;  
num2=0;  
num3=0;  
end  
toc  
%%%%%%%%%%%%将聚类后的功率灰度图赋值%%%%%%%%%%%%%%%%%%%  
%利用矩阵  
result(class==1)=0;  
result(class==2)=130;  
result(class==3)=255;  
%显示图像  
result=uint8(result);  %谨记图像的两种显示格式  uint8和[0,1]  
figure,imshow(result);title('k=3');  
%%%%%%%%%%%%%当k=2时%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
c1=zeros(1,15);c2=zeros(1,15); %c存放每次迭代的聚类中心 
% 初始聚类中心  
c1(1)=8;    
c2(1)=80;    
%分为三类  
k=2;     
[m,n]=size(Img);  
%记录迭代次数  
times=0;  
%存储分类标识  存储分类标识  取值为1 2 3    
class=zeros(m,n);   
%存储聚类结果  
result=zeros(m,n);  
%存放每类的像素个数和元素总和  
num1=0;num2=0;  
sum1=0;sum2=0; 
%先任意给定可以使循环开始的大于1的聚类中心间距值   
d1=2;d2=2; 
%% 迭代部分  
tic  
while((d1>0.1||d2>0.1)&times<15)   %限制迭代次数  
   times=times+1  
%%%%%%%%%%%%%%%%%归类%%%%%%%%%%%%%%%%%%%%%%%%%  
   for i=1:m  
	   for j=1:n  
		   dis1=(Img(i,j)-c1(times))^2;  %欧式距离   
		   dis2=(Img(i,j)-c2(times))^2;  
		  %dis3=(Img(i,j)-c3(times))^2;  
		   min_dis=min([dis1,dis2]);  
		   switch(min_dis)  
			   case dis1  
				   class(i,j)=1;  
				   num1=num1+1;  
				   sum1=sum1+Img(i,j);  
			   case dis2  
				   class(i,j)=2;  
					num2=num2+1;  
					sum2=sum2+Img(i,j);  
		   end     
	   end  
   end  
   e_new=sqrt(min_dis);  
%调整新的聚类中心  
c1(times+1)=sum1/num1;  
c2(times+1)=sum2/num2;  
%c3(times+1)=sum3/num3;  
%两次之间的聚类中心变化大小 以此做为终止迭代的标准  
d1=abs(c1(times)-c1(times+1));  
d2=abs(c1(times)-c1(times+1));  
%d3=abs(c1(times)-c1(times+1));  
%在下一次迭代前将每类的加和置0
sum1=0;  
sum2=0;    
num1=0;  
num2=0;    
end  
toc  
%%%%%%%%%%%%将聚类后的功率灰度图赋值%%%%%%%%%%%%%%%%%%%  
%利用矩阵  
result(class==1)=0;  
result(class==2)=255;   

%显示图像  
result=uint8(result);   
figure,imshow(result);title('k=2'); 

