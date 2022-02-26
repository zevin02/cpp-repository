
bool isletter(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c < '10' && c >='0'))
	{
		return true;
	}
	return false;
}

//验证回文
bool isPalindrome(string s) {
	string s1;
	auto it = s.begin();
	while (it != s.end())
	{
		if (isletter(*it))
		{
			if (((*it) >= 'A' && (*it) <= 'Z'))
			{
				(*it) += 32;
			}
			s1 += (*it);
			it++;
		}
		else
		{
			it++;
		}
	}
	cout << s1 << endl;
	string s2 = s1;
	reverse(s1.begin(), s1.end());
	if (s2 == s1)
	{
		return true;
	}
	else
	{
		return false;
	}
}




