<?php
	// 判断字符串中是否只包含数字、大小写英文字母和下划线，长度在6到20之间
	function isTextSimple($subject)
	{
		$pattern = "/^[a-z0-9_]{6,20}$/";
		if(preg_match($pattern, $subject))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	// 判断邮箱的格式是否正确
	function isEmail($subject)
	{
		$pattern = "/^([a-z0-9_.-]+)@([da-z.-]+).([a-z.]{2,6})$/";
		if(preg_match($pattern, $subject))
		{
			return 1;
		}
		else 
		{
			return 0;
		}
	}
?>