
	bool isletter(char ch)//判断是否为字母
	{
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
			return true;
		else return false;

	}

	string reverseOnlyLetters(string s) {
		int begin = 0, end = s.size() - 1;//利用双指针法进行操作
		while (begin <= end)//两者相遇那就停止了
		{
			if (isletter(s[begin]) && isletter(s[end]))//yes,前后两个都是字母
			{
				swap(s[begin], s[end]);
				begin++;//
				end--;
			}
			else if (isletter(s[begin]) && (!isletter(s[end])))//前面是，后面不是
			{
				end--;
			}
			else if (!isletter(s[begin]) && isletter(s[end]))//前不是，后是
			{
				begin++;//begin往后走
			}
			else//都不是，begin往后走，end往前走
			{
				begin++;
				end--;
			}

		}
		return s;
	}





