function [rate,Error_correct,data_bug]=data_check(data)
%�����жϷ�������������Χ��0��3060�����ٶȷ�Χ��0��80*1.4����ռ���ʷ�Χ��0��95��
logic=zeros(size(data,1),3);
logic(:,1)=(data{:,4}>17);
logic(:,2)=(data{:,5}>112);
logic(:,3)=(data{:,6}>95);
Index=(sum(logic,2)>0);
Error1=data(Index,:);  %��ȡ��������
%����Сʱ��Ч��
%%
%�����жϷ�,����������ٶȡ�ռ�����г���0ֵ��������Ϊ0ֵ���������
logic=zeros(size(data,1),3);
logic(:,1)=(data{:,4}>0);
logic(:,2)=(data{:,5}>0);
logic(:,3)=(data{:,6}>0);
logic=sum(logic,2);
Index=(((logic==3)+(logic==0))+(data{:,6}>95))==0;
Error2=data(Index,:);  %��ȡ��������
%����Сʱ��Ч��
%%
%��Ч�����ж� 
aveL=10*data{:,5}.*data{:,6}./data{:,4}/180;
Index=((aveL>12)+(aveL<3))==1;
Error3=data(Index,:);  %��ȡ��������
%%
%�������
Error=[Error1;Error2;Error3];
Error=unique(Error);
rate=1-size(Error,1)/size(data,1);
%%
%����
[temp,bug_Index]=ismember(Error,data);
data_bug=data;
for i=1:length(bug_Index)
    if(bug_Index(i)>1&&bug_Index(i)<4320)
    data_bug{bug_Index(i),4:6}=1/2*((data{bug_Index(i)-1,4:6}+data{bug_Index(i)+1,4:6}));
    else
       if(bug_Index(i)==1)
           data_bug{bug_Index(i),4:6}=data{bug_Index(i)+1,4:6};
       else 
           if(bug_Index(i)==4320)
            data_bug{bug_Index(i),4:6}=data{bug_Index(i)-1,4:6};
           end
       end
    end    
end
Error_correct=data_bug{bug_Index,4:6};
