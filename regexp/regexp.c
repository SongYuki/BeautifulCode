/*
	匹配算法：这个程序将读取其标准输入或者一组文件。然后输出包含与正则表达式匹配的文本行
	match:search for regexp anywhere in text
	函数match(regexp,text)用来判断文本中是否出现正则表达式，如果找到了一个匹配的正则表达式则返回1否则返回0.
	如果有多个匹配的正则表达式，那么函数将找到文本中最左边且最短的那个 
*/
int match(char *regexp,char *text)
{
	if(regexp[0]=='^')//如果正则表达式中的第一个字符是^(固定位置的匹配)那么匹配就一定要出现在字符串的开头 
	return matchhere(regexp+1,text);
	do{
		/*must look even if string is empty*/
		if(matchhere(regexp,text))//如果第一个字符不是^，那么正则表达式就可以在字符串中的任意位置上进行匹配 
		return 1;
	}while(*text++!='\0');//由于*运算符允许零长度的匹配，因此我们首先需要判断是否存在一个空的匹配 
	return 0;
}

/*matchhere:search for regexp at beginning of text*/
int matchhere(char *regexp,char *text)
{
	if(regexp[0]=='\0')//当正则表达式推进到末尾时(regexp[0]=='\0'所有前面的判断都成功了，那么这个正则表达式就与文本匹配) 
	return 1;
	if(regexp[1]=='*')//如果正则表达式是一个字符后面跟着一个*，那么将会调用matchstar来判断闭包closure是否匹配 
	return matchstar(regexp[0],regexp+2,text);
	
	if(regexp[0]=='$'&&regexp[1]=='\0')
	return *text=='\0';//如果在正则表达式的末尾包含了一个$，那么仅当text此时位于末尾时才会匹配成功 
	if(*text!='\0'&&(regexp[0]=='.'||regexp[0]==*text))
	return matchhere(regexp+1,text+1);//如果匹配成功，函数将推进到正则表达式的下一个字符和文本的下一个字符继续进行匹配，通过递归的调用matchhere函数来实现的 
	//在递归的每个阶段，如果存在某个字符匹配，那么在随后的递归调用中将执行指针算法(regexp+1&text+1),这样在随后的函数调用中，参数就是正则表达式的下一个字符和text的下一个字符
	//递归的深度不会超过匹配模式的长度。而通常情况下匹配模式的长度都是很短的，因此不会出现耗尽内存空间的危险 
	return 0;//如果匹配失败，那么在这个文本位置上就不存在匹配，因此matchhere将返回0 
}

/*matchstar:search for c*regexp at beginning if text，同时满足最短的匹配和最长的匹配*/
int matchstar(int c,char *regexp,char *text)//尝试匹配重复的文本字符c，从零重复开始并且不断累加，直到匹配text的剩余字符，如果匹配失败，那么函数就认为不存在匹配，这个算法将识别出一个“最短的匹配” 
{
	do{
		/*a*matches zero or more instances*/
		if(matchhere(regexp,text))
		return 1;
	}while(*text!='\0'&&(*text++==c||c=='.'));//无论在什么情况下，我们都必须推进text字符串中的一个或多个字符，因此在text++中的递增运算一定要执行 
	return 0;
}
 
 
 /*
 	改进：matchhere中在处理*之前首先处理$.
	虽然这种安排不会对函数的执行带来影响，但却使函数看上去要自然一些
	在编程中一个良好的规则就是：在处理复杂的情况之前首先处理容易的情况
	
	终止条件1.匹配过程的成功与否，是通过判断正则表达式和text中的字符是不是同时处理完来决定的。
	if(regexp[0]=='$'&&regexp[1]=='\0') return *text=='\0';
*/

/*matchstar:leftmost longest search for c*regexp*/
int matchstar(int c,char *regexp,char *text)
{
	char *t;
	for(t=text;*t!='\0'&&(*t==c||c=='.');t++)//若要识别最左边以及最长的匹配，那么函数将首先识别输入字符c的最大重复序列 
	;
	do{
		//* matches zero or more
		if(matchhere(regexp,t))//调用matchhere尝试把匹配延伸到正则表达式的剩余部分和text的剩余部分。 
		return 1;//每次匹配失败都会将cs的出现次数-1，然后再次开始尝试，包括处理零出现的情况 
	}while(t-->text);
	return 0;
 } 
 
 /*
 	这段代码充分说明了优良算法的重要性。如果在模式中包含了几个.*序列，那么在简单的实现中将需要进行大量的回溯操作，并且在某些情况下将会运行得极慢
	 
	 
	在标准的Unix grep中有同样的回溯操作，例如
	grep 'a.*a.*a.*a.a'
	在普通的机器上处理一个4MB的文本文件要花费20秒的时间
	如果某个实现是基于把非确定有限自动机转换为确定有限自动机，例如egrep，那么在处理恶劣的情况时将会获得比较好的性能；
	它可以在不到十分之一秒的时间内处理同样的模式和同样的输入，并且运行时间通常是独立于模式的
	
*/ 
 
