void quicksort0(int l,int u)
{
	int i,m;
	if(l>=u)return;
	swap(l,randint(l,u));
	m=l;
	for(i=l+1;i<=u;i++)
		if(x[i]<x[l])
			swap(++m,i);
	swap(l,m);
	quicksort(l,m-l);
	quicksort(m+l,u);
 } 
 /*
 	���������������ֱ��ǽ�Ҫ�����������������±꣺l�ǽϵ͵��±꣬��u�ǽϸߵ��±�
	��������swap(i,j)���ύ��x[i]��x[j]������Ԫ�ء���һ�ν����������ᰴ�վ��ȷֲ��ķ�ʽ��l��u֮�������ѡ��һ������Ԫ��
*/

void quicksort1(int l,int u)
{
	int i,m;
	if(l>=u)return;
	swap(l,randint(l,u));
	m=l;
	for(i=l+1;i<=u;i++)//�����ڲ�ѭ�����ǻ�ִ��u-l�αȽϣ�������ǿ���ͨ����ѭ���ⲿ����һ���򵥵Ĳ�����ͳ�ƱȽϴ��� 
	{ 
		comps++;//�����һ��ֵn�����г������ǽ��ῴ���ڳ�������й������ܹ������˶��ٴαȽ� 
		if(x[i]<x[l])
			swap(++m,i);
	} 
	swap(l,m);
	quicksort(l,m-l);
	quicksort(m+l,u);
 } 
 
/*
 	Quicksort���ڲ�ѭ���������������Ƶ�ѭ�����ⲿ
*/
void quicksort2(int l,int u)
{
	int i,m;
	if(l>=u)return;
	swap(l,randint(l,u));
	m=l;
	comps += u-l;
	for(i=l+1;i<=u;i++)
		if(x[i]<x[l])
			swap(++m,i);
	swap(l,m);
	quicksort(l,m-l);
	quicksort(m+l,u);
 }  
 
/*
 	��Quicksort�㷨�Ŀ������Ϊֻ����ͳ��
 	��ΪQuicksort��ѡ�񻮷�Ԫ��ʱ���õ���"���"��ʽ���������Ǽ������е�Ԫ�ض��ǲ���ȵġ����ڣ�����³��������ʱ����n�����ȡ�
	�������quicksort2��Ҫ�Ĵ洢�ռ���n��������˵����������Ĵ洢�ռ�����Ϊ�ݹ��ջ�Ĵ�С�����洢�ռ��ƽ����С��lgn�����ȡ� 
*/
void quickcount0(int l,int u)
{
	int m;
	if(l>=u)return;
	m=randint(l,u);
	comps +=u-l;
	quickcount(l,m-l);
	quickcount(m+1,u);
 } 
 /*
 	��Ȼʵ�ʳ����У�������±�(l&u)�Ƿǳ���Ҫ�ģ������������ܰ汾�в�����Ҫ����ˡ�������һ����ʾ�������С������(n)������������±�
	��Quicksort��������ʹ��һ����ʾ�������С�Ĳ���
*/
void quickcount1(int n)
{
	int m;
	if(n<=l)return;
	m=randint(l,n);
	comps+=n-l;
	quickcount1(m-l);
	quickcount1(n-m);
 } 
 
/*
 	һ��ͳ�ƱȽϴ����ĺ�����������������������Quicksort�㷨�еıȽϴ���
*/
int cc(int n)
{
	int m;
	if(n<=l)return 0;
	m=randint(l,n);
	return n-1+cc(m-l)+cc(n-m);
 } 
 
/*
	fakecode:Quicksort��ƽ���Ƚϴ���
	���������Ҫһ����ʱ�俪������Ϊ���ظ��������м�����
	���ڳ����г����������ʱ��ͨ����ʹ�ö�̬������洢�м������Ӷ������ظ����㡣
	����һ����t[N+1]��������t[n]�д洢c[n]�����Ұ�����������������ֵ��
	���ǽ���N����ʾn�����ֵ��Ҳ���ǽ������������Ĵ�С�� 
*/
float c(int n)
	if(n<=l)return 0
	sum = 0
	for(m=l;m<=n;m++)
		sum += n-l + c(m-l) + c(n-m)
	return sum/n 
	
/*
	��Quicksort��ʹ�ö�̬���������
	��������ʱ��������N2����������Ĵ洢�ռ�������N
	���������ŵ�֮һ���ǣ��ڳ���ִ�н���ʱ������t�н����������д�Ԫ��0��Ԫ��N����ʵƽ��ֵ(������������ֵ�Ĺ���)
	���Զ���Щֵ���з������Ӷ�������Quicksort�㷨��ͳ�ƱȽϴ����ļ��㹫ʽ 
*/
t[0]=0
for(n=1;n<=N;n++)
	sum=0
	for(i=l;i<=n;i++)
		sum+=n-l +t[i-l]+t[n-i]
	t[n]=sum/n
	 
/*
	��Quicksort�аѴ����Ƶ�ѭ������������
	��һ�����ǰ�n-l�Ƶ�ѭ��������
*/
t[0]=0
for(n=1;n<=N;n++)
	sum=0
	for(i=1;i<=n;i++)
		sum+=t[i-1]+t[n-i]
	t[n]= n-1 + sum/n
	
/*
	��Quicksort�������˶Գ���������
	����δ��������ʱ����ͬ���������˷ѣ���Ϊ���ظ��ؼ�������ͬ���ܺ� 
*/
t[0]=0
for(n=1;n<=N;n++)
	sum=0
	for(i=0;i<n;i++)
		sum+= 2*t[i]
	t[n]= n-1 + sum/n
	
/*
	��quicksort��ɾ�����ڲ�ѭ��������
	���ǰ�ǰ�����е�Ԫ�ؼ���һ�𣬶�����ѭ���ⲿ��ʼ���ܺͲ��Ҽ�����һ��Ԫ��
	���������ʱ����N�����ȣ�����ÿ����1��N����������������һ��Quicksort�Ĺ�������ʱ��� 
*/
sum=0;t[0]=0
for(n=1;n<=N;n++)
	sum+=2*t[n-1]
	t[n]=n-1 + sum/n
 
/*
	quicksoft����--���հ汾
	�ñ���t�Ķ����ռ������table t[]�����Կռ�
*/
sum=0;t=0
for(n=1;n<=N;n++)
	sum+=2*t
	t=n-1+sum/n
 
 
