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
 	函数的两个参数分别是将要进行排序的子数组的下标：l是较低的下标，而u是较高的下标
	函数调用swap(i,j)将会交换x[i]与x[j]这两个元素。第一次交换操作将会按照均匀分布的方式在l和u之间随机地选择一个划分元素
*/

void quicksort1(int l,int u)
{
	int i,m;
	if(l>=u)return;
	swap(l,randint(l,u));
	m=l;
	for(i=l+1;i<=u;i++)//由于内部循环总是会执行u-l次比较，因此我们可以通过在循环外部增加一个简单的操作来统计比较次数 
	{ 
		comps++;//如果用一个值n来运行程序，我们将会看到在程序的运行过程中总共进行了多少次比较 
		if(x[i]<x[l])
			swap(++m,i);
	} 
	swap(l,m);
	quicksort(l,m-l);
	quicksort(m+l,u);
 } 
 
/*
 	Quicksort的内部循环，将递增操作移到循环的外部
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
 	将Quicksort算法的框架缩减为只进行统计
 	因为Quicksort在选择划分元素时采用的是"随机"方式，并且我们假设所有的元素都是不相等的。现在，这个新程序的运行时间与n成正比。
	并且相对quicksort2需要的存储空间与n成正比来说，现在所需的存储空间缩减为递归堆栈的大小，即存储空间的平均大小与lgn成正比。 
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
 	虽然实际程序中，数组的下标(l&u)是非常重要的，但是在这个框架版本中并不重要，因此。可以用一个表示子数组大小的整数(n)来替代这两个下标
	在Quicksort代码框架中使用一个表示子数组大小的参数
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
 	一个统计比较次数的函数，这个函数将返回在随机Quicksort算法中的比较次数
*/
int cc(int n)
{
	int m;
	if(n<=l)return 0;
	m=randint(l,n);
	return n-1+cc(m-l)+cc(n-m);
 } 
 
/*
	fakecode:Quicksort的平均比较次数
	这个代码需要一定的时间开销，因为它重复计算了中间结果。
	当在程序中出现这种情况时，通常会使用动态编程来存储中间结果，从而避免重复计算。
	定义一个表t[N+1]，其中在t[n]中存储c[n]，并且按照升序来计算它的值。
	我们将用N来表示n的最大值，也就是进行排序的数组的大小。 
*/
float c(int n)
	if(n<=l)return 0
	sum = 0
	for(m=l;m<=n;m++)
		sum += n-l + c(m-l) + c(n-m)
	return sum/n 
	
/*
	在Quicksort中使用动态编程来计算
	它的运行时间正比与N2，并且所需的存储空间正比于N
	这个程序的优点之一就是：在程序执行结束时，数组t中将包含数组中从元素0到元素N的真实平均值(而不是样本均值的估计)
	可以对这些值进行分析，从而生成在Quicksort算法中统计比较次数的计算公式 
*/
t[0]=0
for(n=1;n<=N;n++)
	sum=0
	for(i=l;i<=n;i++)
		sum+=n-l +t[i-l]+t[n-i]
	t[n]=sum/n
	 
/*
	在Quicksort中把代码移到循环外面来计算
	第一步就是把n-l移到循环的外面
*/
t[0]=0
for(n=1;n<=N;n++)
	sum=0
	for(i=1;i<=n;i++)
		sum+=t[i-1]+t[n-i]
	t[n]= n-1 + sum/n
	
/*
	在Quicksort中利用了对称性来计算
	在这段代码的运行时间中同样存在着浪费，因为它重复地计算了相同的总和 
*/
t[0]=0
for(n=1;n<=N;n++)
	sum=0
	for(i=0;i<n;i++)
		sum+= 2*t[i]
	t[n]= n-1 + sum/n
	
/*
	在quicksort中删除了内部循环来计算
	不是把前面所有的元素加在一起，而是在循环外部初始化总和并且加上下一个元素
	程序的运行时间与N成正比，对于每个从1到N的整数，程序将生成一张Quicksort的估计运行时间表 
*/
sum=0;t[0]=0
for(n=1;n<=N;n++)
	sum+=2*t[n-1]
	t[n]=n-1 + sum/n
 
/*
	quicksoft计算--最终版本
	用变量t的定长空间来替代table t[]的线性空间
*/
sum=0;t=0
for(n=1;n<=N;n++)
	sum+=2*t
	t=n-1+sum/n
 
 
