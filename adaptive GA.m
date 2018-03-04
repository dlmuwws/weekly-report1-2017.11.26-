
myrand 函数：
function [population] = myrand(P,m,N,min,max)
 population=zeros(N,m);
vec2=zeros(1,m);  %标准化前的染色体
vec3=zeros(1,m);
i=1;
while i<=N
    seq=randperm(m);
    vec1=seq(1:P);
    while i>0
       for j=1:P
           vec2(1,vec1(1,j))=rand(1);
       end
       %标准化
       sum=0;
       for j=1:m
            sum=sum+vec2(1,j);
       end
       for j=1:m
            vec3(1,j)=vec2(1,j)/sum;
       end
   
       %检查是否满足约束条件
       s=0;
       for j=1:m
          if vec3(1,j)>=min&&vec3(1,j)<=max
               s=s+1;
          end
       end
       if s==P
          break;
       end
   end
   population(i,:)=vec3;
   vec2=zeros(1,m);
   i=i+1;
end
end


fitness函数:计算适应度
function [fitness] = fitness(population,prefer,covar,E)
%计算适应度值，这里采用目标函数的相反数作为适应度值，即收益减去风险最大
N=size(population,1);
m=size(population,2);
fitness=zeros(N,1);
 
for i=1:N
    win=0;
    risk=0;
    for j=1:m
        win=win+population(i,j)*E(1,j);
        for k=1:m
            risk=risk+population(i,j)*population(i,k)*covar(j,k);
        end
    end
    fitness(i,1)=(1-prefer)*win-prefer*risk;
end
end
 
choose函数:选择下代种群
function [ newpopulation,newfitness ] = choose( population,fitness)
%轮盘赌选择
N=size(population,1);
m=size(population,2);
newpopulation=zeros(N,m);
newfitness=zeros(N,1);
sum=0;
for i=1:N
 sum=sum+ fitness(i,1);    
end
p=zeros(N,1);
for i=1:N
p(i,1)=fitness(i,1)/sum;    
end
cumu_p=zeros(N,1);
cumu_p(1,1)=p(1,1);
for i=2:N
 cumu_p(i,1)=p(i,1)+cumu_p(i-1,1);   
end
for i=1:N
    for j=1:N
      if j==1&&rand(1)<cumu_p(1,1)
             newpopulation(i,:)=population(1,:);
             newfitness(i,1)=fitness(j,1);
             break;
      else
            if rand(1)<cumu_p(j,1)&&rand(1)>cumu_p(j-1,1)
             newpopulation(i,:)=population(j,:);
             newfitness(i,1)=fitness(j,1);
             break;
            end
      end
    end
end
end

 
交叉 函数
function [ newpopulation ] = crossover( population,fitness,p0,adjst1,adjst2,iter )
%自适应交叉概率
N=size(population,1);
m=size(population,2);
sum=0;
for j=1:N
   sum=sum+fitness(j,1);
end
avgfitness=sum/N;
for i=1:2:N
    %求第i个个体的交叉概率
    if fitness(i,1)<=avgfitness
        p=p0+adjst1*((avgfitness-fitness(i,1))/(max(fitness)-avgfitness));
    else
        p=p0-adjst2*((e^((avgfitness-fitness(i,1))/(max(fitness)-avgfitness)))/(1+e^(-i/iter)));
    end
    %开始交叉,为使交叉后的染色体满足约束条件，这里采用的交叉方式：随机生成两个交叉点，两点之间的部分为交叉区域，但是需满足交叉区域内不为0的基因的个数相同
    pp=rand(1);
    if pp<p
    while i>0    
    s=randi([1,m],1,2);  %交叉点
    num1=0; num2=0;
    for j=s(1,1):s(1,2)
        if population(i,j)~=0
            num1=num1+1;
        end
    end
    for j=s(1,1):s(1,2)
        if population(i+1,j)~=0
            num2=num2+1;
        end
    end
    if num1==num2    %交叉区域不为0的基因个数相同,对交叉区域进行互换，染色体仍然满足约束条件
        break;
    end
    end
    for j=s(1,1):s(1,2)
    c=population(i,j);
    population(i,j)=population(i+1,j);
    population(i+1,j)=c;
    end
    else
        continue;
    end
end
newpopulation=population;
End

 
变异 函数
function [ newpopulation ] = mutate(population,fitness,q0,adjst3,adjst4,iter)
%自适应变异概率
N=size(population,1);
m=size(population,2);
 sum=0;
 for j=1:N
    sum=sum+fitness(j,1);
 end
 avgfitness=sum/N;
for i=1:N
    %求一下第i个个体的交叉概率
    if fitness(i,1)<=avgfitness
       q=q0+adjst3*((avgfitness-fitness(i,1))/(max(fitness)-avgfitness));
    else
       q=q0-adjst4*((e^((avgfitness-fitness(i,1))/(max(fitness)-avgfitness)))/(1+e^(-i/iter)));
    end
    %为了保证满足约束条件，这里通过生成两个逆转算子，进行变异
    pp=rand(1);
    if pp<q
    s=randi([1,m],1,2);  %让该染色体的这两个位置的基因互换 
    x=populatiion(i,s(1,1)); populatiion(i,s(1,1))=population(i,s(1,2)); population(i,s(1,2))=x;
    else
        continue;
    end
end
newpopulation=population;
end



 
主脚本
clear;
clc;
N=50; m=25; P=8; min=0.02; max=0.6;iter=100; prefer=0.2; p0=0.6; q0=0.05; adjst1=0.6;adjst2=0.6; adjst3=0.05;adjst4=0.05;
%输入covar和E
i=1;
[newpopulation]=myrand(P,m,N,min,max);
while i<=iter
    population=newpopulation;
    fitness = fitness(population,prefer,covar,E);
    [newpopulation,newfitness] = choose( population,fitness);
    [newpopulation] = crossover( newpopulation,newfitness,p0,adjst1,adjst2,iter);
    newfitness=fitness( newpopulation,prefer,covar,E);
    [newpopulation]=mutate(newpopulation,newfitness,q0,adjst3,adjst4,iter);
    i=i+1;
end
