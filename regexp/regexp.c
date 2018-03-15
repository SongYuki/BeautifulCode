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
	}while(*text!='\0'&&(*text++==c||c=='.'));
	return 0;
}
 
