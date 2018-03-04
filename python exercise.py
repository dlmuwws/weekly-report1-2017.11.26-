# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
print('1111')
seq='myexercise'
s=slice(1,4)
print(seq[s])

#练习列表，元组，字典和集合的简单操作
a=list()
b=tuple()
c=dict()
d=set()
print(type(a),type(b),type(c),type(d),sep=',') 
 

a=[1,2,3,4]
print(a[2])
a.append(5)
a.append('6')
print(a)
del a[2]
a.remove(1)
print(a)
print(len(a))
m=[7,8,9]
a=a+m
print(a)
print(a[1:3])  

#元组不能插入和删除元素,声明后即是固定的
b=(1,2,3)
print(len(b))
print(b)

#字典,key+value
c={'m':1,'n':2}
print(c['m'])
del c['m']
c['p']=3
print(c)

#集合
d={1,2,3}
d.add(4)
print(d)
print(2 in d)
d.update('234')
s=set()
s.update('123')
print(d&s) 
print(d|s)


#判断循环语句练习
for i in range(1,6):
    print(i)
    if i%2==0:
        print('偶数')
    else:
        print('奇数')
        
mystr_='exercise'
for i in mystr_:
    print(i)


for (i,v) in enumerate(mystr_):
    print(i,v)
else:
    print('循环结束')
            

i==1
sum=0
while i<=100:
    if i%2!=0:
       sum+=i
    i+=1
print(sum)



#函数练习
#def 函数名  内容  return返回值

def exp(x,y):
   result=x**y
   return result

print(exp(2,3))

(lambda:print('匿名函数'))()


#文件读写
f=open('data.csv','r+')   
print(f.readline())
a=tuple()
a=f.readline()
#写文件
file=open('data1.csv','w')   
file.writelines(f.readlines())
f.close()
file.close()

#模块和包的调用练习，如何自定义函数
#import pack
#print(pack.a)

#返回系统当前时间
import time
dtime=time.localtime() 
print(dtime)

