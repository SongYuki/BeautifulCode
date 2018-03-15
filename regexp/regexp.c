/*
	ƥ���㷨��������򽫶�ȡ���׼�������һ���ļ���Ȼ�����������������ʽƥ����ı���
	match:search for regexp anywhere in text
	����match(regexp,text)�����ж��ı����Ƿ����������ʽ������ҵ���һ��ƥ���������ʽ�򷵻�1���򷵻�0.
	����ж��ƥ���������ʽ����ô�������ҵ��ı������������̵��Ǹ� 
*/
int match(char *regexp,char *text)
{
	if(regexp[0]=='^')//���������ʽ�еĵ�һ���ַ���^(�̶�λ�õ�ƥ��)��ôƥ���һ��Ҫ�������ַ����Ŀ�ͷ 
	return matchhere(regexp+1,text);
	do{
		/*must look even if string is empty*/
		if(matchhere(regexp,text))//�����һ���ַ�����^����ô������ʽ�Ϳ������ַ����е�����λ���Ͻ���ƥ�� 
		return 1;
	}while(*text++!='\0');//����*����������㳤�ȵ�ƥ�䣬�������������Ҫ�ж��Ƿ����һ���յ�ƥ�� 
	return 0;
}

/*matchhere:search for regexp at beginning of text*/
int matchhere(char *regexp,char *text)
{
	if(regexp[0]=='\0')//��������ʽ�ƽ���ĩβʱ(regexp[0]=='\0'����ǰ����ж϶��ɹ��ˣ���ô���������ʽ�����ı�ƥ��) 
	return 1;
	if(regexp[1]=='*')//���������ʽ��һ���ַ��������һ��*����ô�������matchstar���жϱհ�closure�Ƿ�ƥ�� 
	return matchstar(regexp[0],regexp+2,text);
	
	if(regexp[0]=='$'&&regexp[1]=='\0')
	return *text=='\0';//�����������ʽ��ĩβ������һ��$����ô����text��ʱλ��ĩβʱ�Ż�ƥ��ɹ� 
	if(*text!='\0'&&(regexp[0]=='.'||regexp[0]==*text))
	return matchhere(regexp+1,text+1);//���ƥ��ɹ����������ƽ���������ʽ����һ���ַ����ı�����һ���ַ���������ƥ�䣬ͨ���ݹ�ĵ���matchhere������ʵ�ֵ� 
	//�ڵݹ��ÿ���׶Σ��������ĳ���ַ�ƥ�䣬��ô�����ĵݹ�����н�ִ��ָ���㷨(regexp+1&text+1),���������ĺ��������У���������������ʽ����һ���ַ���text����һ���ַ�
	//�ݹ����Ȳ��ᳬ��ƥ��ģʽ�ĳ��ȡ���ͨ�������ƥ��ģʽ�ĳ��ȶ��Ǻ̵ܶģ���˲�����ֺľ��ڴ�ռ��Σ�� 
	return 0;//���ƥ��ʧ�ܣ���ô������ı�λ���ϾͲ�����ƥ�䣬���matchhere������0 
}

/*matchstar:search for c*regexp at beginning if text��ͬʱ������̵�ƥ������ƥ��*/
int matchstar(int c,char *regexp,char *text)//����ƥ���ظ����ı��ַ�c�������ظ���ʼ���Ҳ����ۼӣ�ֱ��ƥ��text��ʣ���ַ������ƥ��ʧ�ܣ���ô��������Ϊ������ƥ�䣬����㷨��ʶ���һ������̵�ƥ�䡱 
{
	do{
		/*a*matches zero or more instances*/
		if(matchhere(regexp,text))
		return 1;
	}while(*text!='\0'&&(*text++==c||c=='.'));
	return 0;
}
 
