<?php
	/***
	 * 在这里获取当前的用户信息。
	 */
	session_start();
	if(!empty($_SESSION['User_ID']))
	{
		$userID = $_SESSION['User_ID'];				// 用户的ID，是一个唯一的整数
		$userName = $_SESSION['User_Name'];			// 用户登录用的名称，是唯一的字符串
		$userNickname = $_SESSION['User_Nickname']; // 用户用来显示的名称，字符串
		$userType = $_SESSION['User_Type'];			// 用户类型，一个整数
	}
	
	// 显示用户昵称，链接到更新用户信息页面
	function echoUserNickname()
	{
		global $userNickname;
		echo "<li>";
		echo "<a href='/pages/update.php'>";
		echo $userNickname;
		echo "</a>";
		echo "</li>";
	}
	
	// TODO 判断用户身份，是否显示管理工具
	function echoManagementTools()
	{
		// TODO
	}
	
	// 退出登录的链接
	function echoLogout()
	{
		echo "<li>";
		echo "<a href='/pages/logout.php'>退出</a>";
		echo "</li>";
	}
	
	// 显示未登录状态，链接到登录页面
	function echoLogin()
	{
		echo "<li style='color: gray'>";
		echo "<a href='/pages/account/login.php'>未登录</a>";
		echo "</li>";
	}
?>

<div id="top">
<div id="topLeft">Z实验室2013_个人相册管理</div>
<div id="topRight">
	<ul>
		<?php
			if(isset($userID))
			{
				echoUserNickname();
				echoManagementTools();
				echoLogout();
			}
			else
			{
				echoLogin();
			}
		?>
	</ul>
</div>
</div>
<div id="banner"></div>
<div id="menu">
	<div class="menuBlock">
		<ul>
			<li>
				<a href="/pages/index.php">首页</a>
			</li>
			<li>
				<a href="">查看相册</a>
			</li>
			<li>
				<a href="">上传照片</a>
			</li>
			<li>
				<a href="">照片分类</a>
			</li>
			<li>
				<a href="">人物管理</a>
			</li>
		</ul>
	</div>
</div>
